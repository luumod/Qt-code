#include "widget.h"
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
    setQPushButton();
    setQTextEdit();
}

Widget::~Widget()
{
    Py_Finalize();
}

void Widget::init()
{
    resize(640,480);

    Py_Initialize();
    if (!Py_IsInitialized()){
        qInfo()<<"Cant initialized!";
        close();
    }
    Module=PyImport_ImportModule("getMessage");
    if (!Module){
        qInfo()<<"Cant open python file!";
        close();
    }
}

void Widget::setQPushButton()
{
    button1=new QPushButton("获取字符串",this);
    connect(button1,&QPushButton::clicked,this,&Widget::actionOnButtonMess);
    button1->setGeometry(10,10,100,30);

    input=new QLineEdit(this);
    input->setPlaceholderText("请输入起始和终止");
    input->setGeometry(110,10,150,20);
    connect(input,&QLineEdit::editingFinished,this,[=](){
        try{
            QStringList strs = input->text().split("，");
            start=strs[0].toInt();
            end=strs[1].toInt();
        }
        catch(...){
            QMessageBox::warning(this,"警告","输入错误!");
        }
    });

    button2=new QPushButton("获取列表",this);
    connect(button2,&QPushButton::clicked,this,&Widget::actionOnButtonList);
    button2->setGeometry(270,10,100,30);
}

void Widget::setQTextEdit()
{
    edit=new QTextEdit(this);
    edit->setGeometry(50,50,200,200);
}

void Widget::actionOnButtonMess()
{
    PyObject* gMess=PyObject_GetAttrString(Module,"getMess");
    if (!gMess){
        qInfo()<<"Cant call Functional!";
        QMessageBox::warning(this,"警告","无法调用python函数!");
        return;
    }
    //获取一个字符串
    PyObject* mString = PyObject_CallFunction(gMess,NULL);
    if (mString){
        QString str=PyUnicode_AsUTF8(mString);
        edit->append(str);
    }
}

void Widget::actionOnButtonList()
{
    //获取Python列表
    PyObject* gList=PyObject_GetAttrString(Module,"getList");
    if (!gList){
        qInfo()<<"Cant call Functional!";
        QMessageBox::warning(this,"警告","无法调用python函数!");
        return;
    }
    //调用python
    PyObject* args=PyTuple_New(2);  //创建有两个元素的元组
    PyTuple_SetItem(args,0,Py_BuildValue("i",start));
    PyTuple_SetItem(args,1,Py_BuildValue("i",end));
    PyObject* pList=PyObject_CallObject(gList,args);
    auto size = PyList_Size(pList); //返回列表长度
    QList<int> q;
    for (int i=0;i<size;i++){
        int num=0;
        PyObject* item = PyList_GetItem(pList,i);
        PyArg_Parse(item,"i",&num);
        q.append(num);
    }
    QStringList strs;
    for (auto& x:q){
        strs<<QString::number(x);
    }
    QString eStr=strs.join(", ");
    edit->append(eStr);
}

