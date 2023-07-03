#include "widget.h"
#include <QTimer>   //定时器类
#include <QDebug>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QApplication>
CustomEvent::CustomEvent(int age, const QString &name)
    :QEvent(QEvent::Type(EventType::ET_CustomEvent))
    ,age(age)
    ,name(name)
{

}

CustomEvent::~CustomEvent()
{
    qInfo()<<__FUNCTION__<<name;
}

void CustomEvent::showInfo()
{
    qInfo()<<age<<name;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlag(Qt::WindowType::FramelessWindowHint);
    setMouseTracking(true);

    //创建一个定时器，每隔500ms超时一次，让变量自增(实现循环效果)
    QTimer *timer = new QTimer(this);
    //链接定时器的超时信号
    //connect(timer,&QTimer::timeout,this,&Widget::onTimeOut);
    timer->callOnTimeout(this,&Widget::onTimeOut);
    timer->callOnTimeout([](){qInfo()<<"hello world";});
    //启动定时器
    //timer->start(500);

    //使用QTmer的静态成员，仅仅可以发射一次信号
   //QTimer::singleShot(2000,this,&Widget::onTimeOut);
   //QTimer::singleShot(1000,[](){qInfo()<<"singleShot";});

   //通过QObject类提供的事件来处理
   //开启一个定时器，超时会调用timerEvent事件处理函数,返回定时器ID，失败返回0
    //timerID = startTimer(1000);

    auto*btn = new QPushButton("发送事件",this);
    connect(btn,&QPushButton::clicked,this,[=]()
    {
        CustomEvent ev(18,"顽石");                 //定义在栈区
        auto *cev = new CustomEvent(35,"金克斯");  //定义在堆区,手动释放
        //发送事件，直接发送给对象，等对象处理完毕，才会返回
        // QApplication::sendEvent(this,&ev);
        // QApplication::sendEvent(this,cev);
        // //事件什么时候释放？
        // //1，栈区自动释放
        // //2，堆区手动释放
        // delete cev;

        //提交栈区的事件，会中断
        //qApp->postEvent(this,&ev);
        //提交堆区的事件没有问题，处理完成之后会自动的释放
        qApp->postEvent(this,cev);

    });
}

Widget::~Widget()
{

}

bool Widget::event(QEvent *ev)
{
    //自己实现对于不同事件的处理
    switch(ev->type())
    {
    case QEvent::Type::MouseButtonPress:
    {
        QMouseEvent* mev = static_cast<QMouseEvent*>(ev);
        pressPos = mev->pos();
        break;
    }
    case QEvent::Type::MouseMove:
    {
        qInfo()<<"mousemove";
        QMouseEvent* mev = static_cast<QMouseEvent*>(ev);
        if(mev->buttons() & Qt::MouseButton::LeftButton)
        {
            this->move(mev->globalPosition().toPoint() - pressPos);
        }
        return true;
        break;
    }
    }
    //调用父类的实现
    return QWidget::event(ev);
}

void Widget::customEvent(QEvent *ev)
{
    if(ev->type() == EventType::ET_CustomEvent)
    {
         auto* cev = static_cast<CustomEvent*>(ev);
         cev->showInfo();
    }
}

void Widget::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == timerID)
    {
        qInfo()<<"timerID"<<timerID;
    }
    else if(1)
    {

    }
}

void Widget::mouseMoveEvent(QMouseEvent *ev)
{
    qInfo()<<__FUNCTION__;
}

void Widget::onTimeOut()
{
    qInfo()<<"timeOut"<<cnt++;
}



