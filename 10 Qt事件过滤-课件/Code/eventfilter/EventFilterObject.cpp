#include "EventFilterObject.h"
#include <QMouseEvent>
#include <QWidget>
#include <QDebug>
EventfilterObject::EventfilterObject(QObject *parent)
    :QObject(parent)
{

}

EventfilterObject::~EventfilterObject()
{
    qInfo()<<"EventfilterObject::~EventfilterObject()";
}

bool EventfilterObject::eventFilter(QObject *obj, QEvent *ev)
{
    if(ev->type() == QEvent::MouseButtonPress)
    {
        auto mev = static_cast<QMouseEvent*>(ev);
        pressPos =mev->pos();
    }
    else if(ev->type() == QEvent::MouseMove)
    {
        auto mev = static_cast<QMouseEvent*>(ev);
        auto w = static_cast<QWidget*>(obj);
        if(w)
            w->move(mev->globalPosition().toPoint() - pressPos);
        //return true;
    }
    return false;
}
