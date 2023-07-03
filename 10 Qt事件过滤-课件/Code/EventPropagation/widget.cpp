#include "widget.h"
#include <QDebug>
#include <QMouseEvent>
Button::Button(QWidget*parent)
    :QPushButton(parent)
{

}
void Button::mousePressEvent(QMouseEvent*ev)
{
    QPushButton::mousePressEvent(ev);
    qInfo()<<"Button::mousePressEvent";
    //事件默认是接受的，不会传递给父组件
    //ev->accept();
    //忽略事件,会吧这个事件传递给父组件，让父组件去处理
    ev->ignore();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto * btn = new Button(this);
    connect(btn,&Button::clicked,this,[]()
    {
        qInfo()<<"clicked";
    });
}

Widget::~Widget()
{
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    qInfo()<<"Widget::mousePressEvent";
}

