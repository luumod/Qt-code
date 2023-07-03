#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(640,480);
    setWindowIcon(QIcon(":/new/prefix1/windowIcon.png"));
    testContextMenu();
}

Widget::~Widget()
{

}

void Widget::testWindowParent()
{
    //点击标签会变色
    for (int i=1;i<=3;i++){
        for (int j=1;j<=3;j++){
            auto btn=new QLabel(QString::number(j+(i-1)*3),this);
            btn->setGeometry(j*(W+5),i*(H+5),W,H);

            btn->setStyleSheet("background-color:blue");
        }
    }

}

void Widget::testCengji()
{
    auto lab1=new QLabel(this);
    auto lab2=new QLabel(this);

    lab1->setGeometry(0,0,50,50);
    lab2->setGeometry(30,30,50,50);

    lab1->setStyleSheet("background-color:red");
    lab2->setStyleSheet("background-color:green");

    lab1->raise();//提升层级
    lab1->lower();//降低层级
    lab1->stackUnder(lab2); //指定 lab1在lab2的后面,即lab2的优先级高
}

void Widget::testJiaohu()
{
    auto btn=new QPushButton("按钮",this);

    //btn->setEnabled(false); //禁用
    qInfo()<<btn->isEnabled(); //是否启用

    this->setEnabled(true); //父控件禁用，子控件也禁用


    btn->setVisible(true); //控件是否可见
    //与上面的setVisible等效
    //btn->hide();
    //btn->setHidden(true);
    //btn->show();

    btn->setToolTip("这是一个简单的按钮"); //控件的提示信息，鼠标放上去
    btn->setToolTipDuration(2000); //2s后提示自动消失

    this->setWhatsThis("这是我的窗口！！！");
    //WhatsThis模式
    auto btn2=new QPushButton("进入模式",this);
    btn2->setGeometry(100,100,50,50);
    connect(btn2,&QPushButton::clicked,this,[=](){
        //进入WhatsThis
        QWhatsThis::enterWhatsThisMode();
    });

}

void Widget::testFocus()
{
    for (int i=0;i<3;i++){
        auto edit=new QLineEdit(this);
        edit->setGeometry(10+i*100,50,80,30);
        if (i==0){
            //设置永远不会有焦点
            edit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        }
        if (i==1){
            //默认焦点为第二个
            edit->setFocus();
        }
    }
    //设置焦点的顺序
    //setTabOrder()
}

void Widget::testContextMenu()
{

    //设置右键弹出菜单的方式
    setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    connect(this,&Widget::customContextMenuRequested,this,&Widget::onContextMenu);

    cxt_menu=new QMenu(this); //右键弹出式菜单体
    auto createMenu=[=](){
        auto menu2=new QMenu("选择",this);
        menu2->addAction("1111");
        menu2->addAction("2222");

        cxt_menu->addAction("新建",[=](){qInfo()<<"新建文件";}); //行为
        cxt_menu->addAction("打开",[=](){qInfo()<<"打开文件";}); //行为
        cxt_menu->addMenu(menu2); //子菜单
        cxt_menu->addSeparator();
        cxt_menu->addAction("退出",[=](){qInfo()<<"退出";});

    };

    createMenu();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qInfo()<<__FUNCTION__;
    auto lab=childAt(mapFromGlobal(QCursor::pos())); //从指定的位置（从全局坐标转化）获取控件
    if (lab){
        lab->setStyleSheet("background-color:red"); //改变颜色
        qInfo()<<lab->parent();
    }
}


void Widget::onContextMenu(const QPoint & pos)
{
    //qInfo()<<__FUNCTION__;
    //pos是窗口的局部坐标,显示在我们的窗口上需要转换为全局坐标 mapToGlobal(pos)
    cxt_menu->popup(QCursor::pos());

}

