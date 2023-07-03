#include "widget.h"

//全局函数
void Global(){
    qInfo()<<__FUNCTION__;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("主窗口");
    resize(640,480);
    solve4();
}

Widget::~Widget()
{
}

void Widget::solve1()
{
    auto btn =new QPushButton("退出",this);

    //绑定连接：发送与接收信号
    connect(btn,&QPushButton::clicked,this,&QWidget::close);

    //关闭连接：取消绑定
    disconnect(btn,&QPushButton::clicked,this,&QWidget::close);
}

void Widget::solve2()
{
    /*
     *  自定义槽函数：
     *  1. 槽函数的返回类型必须要void
     *  2. 槽函数的参数不能多于信号的参数
     */
    auto btn=new QPushButton("点击",this);
    //1. 关联成员函数
    connect(btn,&QPushButton::pressed,this,&Widget::onButtonPressed);
    //2. 关联静态函数
    connect(btn,&QPushButton::released,this,&Widget::onButtonReleased);
    //3. 关联全局函数
    connect(btn,&QPushButton::clicked,Global);
    //4. 关联lambda表达式
    connect(btn,&QPushButton::clicked,[=](){
        qInfo()<<__FUNCTION__;
        static int i=0;
        btn->setText("我是于良浩"+QString::number(i++));
    });

    //关于lambda表达式：不要传递引用！
    //connect(btn,&QPushButton::clicked,[&](){
    //    btn->setText("我是于良浩");
    //});
}

void Widget::solve3()
{
    //切换窗口
    subwidget=new SubWidget();
    auto btn=new QPushButton("切换到子窗口",this);
    //点击切换子窗口
    connect(btn,&QPushButton::clicked,this,[=](){
        subwidget->show();
        this->hide();
    });
    //接收信号，显示主窗口
    //connect(subwidget,&SubWidget::cutMainWindow,this,[=](){
    //    this->show();
    //    subwidget->hide();
    //});
}

void Widget::solve4()
{
    //切换窗口
    subwidget=new SubWidget();
    auto btn=new QPushButton("切换到子窗口",this);
    //点击切换子窗口
    connect(btn,&QPushButton::clicked,this,&Widget::onFromMainToSubWindow);


    //接收信号，显示主窗口
    //connect(subwidget,&SubWidget::cutMainWindow2,this,&Widget::onFromSubToMainWindow);
    //解决重载的信号的方式：
    //1.函数指针形式
    //(1). 信号发送
    void (SubWidget::*cutNone)()=&SubWidget::cutMainWindow;
    void (SubWidget::*cutStr)(const QString&)=&SubWidget::cutMainWindow;
    //(2). 槽函数接受
    void (Widget::*MainNone)()=&Widget::onFromSubToMainWindow;
    void (Widget::*MainStr)(const QString&)=&Widget::onFromSubToMainWindow;
    //connect(subwidget,cutStr,this,MainStr);
    //connect(subwidget,cutNone,this,&Widget::onFromSubToMainWindow);

    //2. QOverLoad解决 使用这种方式！！！！！！！
    connect(subwidget,QOverload<const QString&>::of(&SubWidget::cutMainWindow),this,QOverload<const QString&>::of(&Widget::onFromSubToMainWindow));
    connect(subwidget,QOverload<>::of(&SubWidget::cutMainWindow),this,QOverload<>::of(&Widget::onFromSubToMainWindow));

    //3. 通过Qt4的宏函数
    //connect(subwidget,SIGNAL(cutMainWindow()),this,SLOT(onFromSubToMainWindow()));
    //connect(subwidget,SIGNAL(cutMainWindow(const QString&)),this,SLOT(onFromSubToMainWindow(const QString&)));
}

void Widget::onButtonPressed()
{
    qInfo()<<__FUNCTION__;
}

void Widget::onButtonReleased()
{
    qInfo()<<__FUNCTION__;
}

void Widget::onFromSubToMainWindow()
{
    this->show();
    subwidget->hide();
}

void Widget::onFromSubToMainWindow(const QString& str)
{
    qInfo()<<str; //输出
    this->show();
    subwidget->hide();
}

void Widget::onFromMainToSubWindow()
{
    subwidget->show();
    this->hide();
}



