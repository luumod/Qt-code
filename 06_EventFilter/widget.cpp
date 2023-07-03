#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlag(Qt::WindowType::FramelessWindowHint);
    resize(640,480);
    //安装事件过滤器
    //installEventFilter(this);
    installEventFilter(new EventFilterObject(this));
}

Widget::~Widget()
{
}

//bool Widget::eventFilter(QObject* obj,QEvent* ev){
//    switch (ev->type()) {
//        case QEvent::Type::MouseButtonPress:
//        {
//            auto cev=static_cast<QMouseEvent*>(ev);
//            pressPos=cev->pos();
//            break;
//        }
//        case QEvent::Type::MouseMove:
//        {
//            auto w=static_cast<QMouseEvent*>(ev);
//            this->move(w->globalPosition().toPoint()-pressPos);
//            break;
//        }
//        default:
//            break;
//    }
//    return false;
//}
