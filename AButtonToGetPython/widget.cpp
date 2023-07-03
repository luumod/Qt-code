#include "widget.h"
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
    setQPushButton();
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
        qInfo()<<"Cant open python file!";
        close();
    }
}

void Widget::setQPushButton()
{
    button=new QPushButton("调用",this);
}

