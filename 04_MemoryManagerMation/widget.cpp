#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(640,480);
    testDIYProperty();
}

Widget::~Widget()
{
    qInfo()<<__FUNCTION__;
}

void Widget::testQPointer()
{
    //QPointer指针: 管理QObject对象，自动释放
    QPointer<PushButton> btn=new PushButton("QPointer指针",this);
    connect(btn,&QPushButton::clicked,this,&Widget::close);
}

void Widget::testQScopedPointer()
{
    //超出作用域自动释放
    //QScopedPointer<PushButton> btn(new PushButton("QScopedPointer",this));

    //定义为类的私有属性
    s_btn.reset(new PushButton("QScopedPointer指针",this));

    connect(s_btn.data(),&QPushButton::clicked,this,&Widget::close);
}

void Widget::testQSharedPointer()
{
    //没有其他对象引用的时候，超出作用域，自动释放
    QSharedPointer<PushButton> btn(new PushButton("PushButton指针",this));
    qInfo()<<btn->text();

    QWeakPointer<PushButton> w_btn(btn);
    if (!w_btn.isNull()){
        qInfo()<<"btn is not Null";
    }
    auto s_btn=btn;
    QWeakPointer<PushButton> w_btn2(s_btn);
    if (!w_btn2.isNull()){
        qInfo()<<"s_btn is not Null";
    }

}

void Widget::testProperty()
{
    QObject obj;
    //通过函数获取对象名
    obj.setObjectName("obj");
    qInfo()<<obj.objectName();

    //通过属性获取修改
    obj.setProperty("objectName","ylh1号");
    qInfo()<<obj.property("objectName");

    //设置临时属性
    obj.setProperty("name","ylh");
    qInfo()<<obj.property("name");

    //取消临时属性
    obj.setProperty("name",QVariant());
    qInfo()<<obj.property("name");
}

void Widget::testDIYProperty()
{
    QObject::connect(&stu,&Student::onChangedAge,this,[=](int age){
        qInfo()<<"(changed)age: "<<age;
    });
    stu.setProperty("age",50); //写访问器
    qInfo()<<stu.property("age"); //读访问器

    //重置属性: 多次只会发出一次信号
    stu.setProperty("age",QVariant());
    stu.setProperty("age",QVariant());
    stu.setProperty("age",QVariant());



    //QObject::connect(&stu,&Student::onChangedAge,this,&Widget::close);
}

