#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("傻狗转转转");
    setWindowIcon(QIcon(QPixmap(":/images/touxiang.png")));

    resize(640,480);

    time=new QTimer(this);
    time->callOnTimeout(this,QOverload<>::of(&Widget::update));
    time->setInterval(20);
    time->start();

    buttons();
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent* ev){
    QPainter painter(this);
    draw(&painter);
}


void Widget::draw(QPainter* painter)
{
    //painter->save();
    painter->translate(200,200);

    static qreal Delta=0;
    painter->rotate(Delta++);
    if (Delta>100000){
        Delta=0;
    }
    //QTransform transform;
    //transform.rotate(Delta++,Qt::Axis::XAxis);
    //painter->setTransform(transform);

    painter->drawPixmap(0,0,QPixmap(":/images/touxiang.png").scaled(150,150));
    //painter->restore();
}

void Widget::buttons()
{
    btn1=new QPushButton("最快速度",this);
    btn1->setGeometry(450,50,100,40);
    connect(btn1,&QPushButton::clicked,this,[=](){
        time->setInterval(1);
    });

    btn2=new QPushButton("较快速度",this);
    btn2->setGeometry(450,150,100,40);
    connect(btn2,&QPushButton::clicked,this,[=](){
        time->setInterval(5);
    });

    btn3=new QPushButton("普通速度",this);
    btn3->setGeometry(450,250,100,40);
    connect(btn3,&QPushButton::clicked,this,[=](){
        time->setInterval(15);
    });

    btn4=new QPushButton("较慢速度",this);
    btn4->setGeometry(450,350,100,40);
    connect(btn4,&QPushButton::clicked,this,[=](){
        time->setInterval(30);
    });

    auto lab=new QLabel("自定义输入(1-100)：",this);
    lab->setGeometry(290,10,100,20);
    edit=new QLineEdit(this);
    edit->setGeometry(400,10,60,20);

    ok=new QPushButton("确定",this);
    ok->setGeometry(465,10,50,20);
    connect(ok,&QPushButton::clicked,this,[=](){
        int num=edit->text().toInt();
        if (num>=1 && num<=100){
            time->setInterval(num);
        }
    });
}



