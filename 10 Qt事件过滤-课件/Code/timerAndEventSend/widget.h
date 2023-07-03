#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
enum EventType
{
    ET_CustomEvent = QEvent::Type::User
};

//自定义事件类型
class CustomEvent : public QEvent
{
public:
    CustomEvent(int age,const QString& name);
    ~CustomEvent();
    void showInfo();

private:
    int age;
    QString name;
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    //返回值，用来提示事件是否已经处理了，如果返回true表示已经处理，否则未处理
    bool event(QEvent* ev)override;     //事件分发函数，在这个函数里面调用不同的事件处理函数
    void customEvent(QEvent*ev)override;
    void timerEvent(QTimerEvent*ev)override;
    void mouseMoveEvent(QMouseEvent*ev)override;
public slots:
    void onTimeOut();
private:
    int cnt = 0;
    int timerID;
    QPoint pressPos;
};
#endif // WIDGET_H
