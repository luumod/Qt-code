#ifndef _EVENTFILTEROBJECT_H_
#define _EVENTFILTEROBJECT_H_

#include <QObject>
#include <QPoint>
class EventfilterObject : public QObject
{
public:
    EventfilterObject(QObject*parent = nullptr);
    ~EventfilterObject();
    bool eventFilter(QObject*obj,QEvent*ev)override;
private:
    QPoint pressPos;
};

#endif
