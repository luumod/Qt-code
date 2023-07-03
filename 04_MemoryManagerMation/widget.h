#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QPointer>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QVariant>

//自定义属性
class Student:public QObject
{
    Q_OBJECT
    //设置属性
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY onChangedAge RESET reset)
public:
    Student(QObject* parent=nullptr):QObject(parent) {}
    ~Student(){}
    //设置属性： READ访问器
    int getAge(){
        //qInfo()<<__FUNCTION__;
        return m_age;
    }
    void setAge(int age){
        //qInfo()<<__FUNCTION__;
        if (m_age!=age){
            m_age=age;
            emit onChangedAge(m_age); //发送修改信号
        }
    }
    //重置器
    void reset(){
        if (m_age!=18){
            m_age=18;
            emit onChangedAge(m_age);
        }
    }
signals:
    //信号
    void onChangedAge(int age);
private:
    int m_age;
};

class PushButton: public QPushButton{
public:
    using QPushButton::QPushButton;
    ~PushButton(){
        qInfo()<<__FUNCTION__;
    }
private:

};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void testQPointer();
    void testQScopedPointer();
    void testQSharedPointer();
    void testProperty();
    void testDIYProperty();
private:
    //QPushButton* btn;
    QScopedPointer<PushButton> s_btn;
    Student stu;
};
#endif // WIDGET_H
