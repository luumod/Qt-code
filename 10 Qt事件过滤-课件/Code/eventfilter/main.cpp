#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include "EventFilterObject.h"
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget*parent = nullptr)
        :QWidget(parent)
    {
        resize(640,480);
        setWindowFlag(Qt::FramelessWindowHint);
        //安装事件过滤器
        //installEventFilter(this);
        installEventFilter(new EventfilterObject(this));
    }
    //事件过滤函数
    bool eventFilter(QObject*obj,QEvent*ev)override
    {
        if(ev->type() == QEvent::MouseButtonPress)
        {
            auto *mev = static_cast<QMouseEvent*>(ev);
            pressPos =mev->pos();
        }
        else if(ev->type() == QEvent::MouseMove)
        {
            auto *mev = static_cast<QMouseEvent*>(ev);
            this->move(mev->globalPosition().toPoint() - pressPos);
            //return true;
        }
        return false;
    }
    void mouseMoveEvent(QMouseEvent*ev)override
    {
        qInfo()<<"mouseMoveEvent";
    }
private:
    QPoint pressPos;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QWidget   ww;
    ww.setWindowFlag(Qt::FramelessWindowHint);
    ww.show();
    ww.installEventFilter(new EventfilterObject(&ww));

    return a.exec();
}

#include "main.moc"
