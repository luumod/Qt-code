#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QMimeData>
#include <QTimer>
#include <QEvent>
#include <QApplication>

class Button:public QPushButton{
public:
    using QPushButton::QPushButton;
    void enterEvent(QEnterEvent* ev)override{
        setStyleSheet("background-color:red");
    }
    void leaveEvent(QEvent* ev)override{
        setStyleSheet("background-color:white");
    }
    //测试事件传播
    void mousePressEvent(QMouseEvent* ev)override{
        //默认接受，当前组件接受事件处理，不会传播给父控件了
        //ev->accept();
        qInfo()<<"Button::mousePressEvent";

        //如果忽略，则会传播给父控件处理，当前不处理
        //ev->ignore();
    }
    bool event(QEvent* ev)override{
        if (ev->type()==QEvent::Type::MouseButtonPress){
            qInfo()<<"Button::event::MouseButtonPress";
            //return false; //会传递给父控件
            //return true;  //不会传递给父控件
        }
        return QPushButton::event(ev);
    }
private:

};
class LineEdit:public QLineEdit{
public:
    using QLineEdit::QLineEdit;
    void focusInEvent(QFocusEvent* ev)override{
        this->setStyleSheet("background-color: lightblue");
    }
    void focusOutEvent(QFocusEvent* ev)override{
        this->setStyleSheet("background-color: white");
    }
private:
};

//自定义事件
enum EventType{
    My_Event=QEvent::Type::User+1
};
class CustomEvent:public QEvent{
public:
    CustomEvent(int age,const QString& name)
        :QEvent(QEvent::Type(EventType::My_Event)),age(age),name(name){}
    void show(){
        qInfo()<<name<<age;
    }
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
public:
    //关闭事件，close时调用
    void closeEvent(QCloseEvent* ev)override;
    void showEvent(QShowEvent* ev)override;
    void moveEvent(QMoveEvent* ev)override;
    void resizeEvent(QResizeEvent* ev)override;

    void enterEvent(QEnterEvent* ev)override;
    void leaveEvent(QEvent* ev)override;

    void mousePressEvent(QMouseEvent* ev)override;
    void mouseReleaseEvent(QMouseEvent* ev)override;
    void mouseDoubleClickEvent(QMouseEvent* ev)override;
    void mouseMoveEvent(QMouseEvent* ev)override;
    void wheelEvent(QWheelEvent* ev)override;

    void keyPressEvent(QKeyEvent* ev)override;
    void keyReleaseEvent(QKeyEvent* ev)override;

    void focusInEvent(QFocusEvent* ev)override;
    void focusOutEvent(QFocusEvent* ev)override;

    void changeEvent(QEvent* ev)override;

    void contextMenuEvent(QContextMenuEvent* ev)override;

    void dragEnterEvent(QDragEnterEvent* ev)override;
    void dropEvent(QDropEvent* ev)override;

    void timerEvent(QTimerEvent* ev)override;

    bool event(QEvent* ev)override; //事件分发函数
    void customEvent(QEvent* ev)override; //处理自定义事件的分发函数
    void testEventDiffuse(); //事件传播
public:
    //定时器
    void testTimer();
    void testDIYEvent();
public slots:
    //定时器处理的槽函数
    void onTimerHandle();
private:
    Button* btn;
    QPoint pressPos;
    LineEdit* edit;
    int timeId;
    int cnt=0;

};
#endif // WIDGET_H
