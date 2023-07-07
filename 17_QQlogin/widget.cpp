#include "widget.h"
#include "./ui_widget.h"
#include <QMovie>
#include <QFile>
#include "eventfilterobject.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QDebug>
#include "testwindow.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();

    //读取样式表
    QFile qssFile(":/images/style.css");
    if (qssFile.open(QIODeviceBase::ReadOnly)){
        this->setStyleSheet(qssFile.readAll());
    }

    //事件过滤器
    installEventFilter(new EventFilterObject(parent));
}

Widget::~Widget()
{
    delete ui;
    qInfo()<<"destory Login";
}

void Widget::initUI()
{
    //去除边框
    setWindowFlag(Qt::WindowType::FramelessWindowHint);
    setWindowFlag(Qt::WindowType::WindowStaysOnTopHint);
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);

    //边框阴影
    auto shadow =new QGraphicsDropShadowEffect(this);
    shadow->setColor(qRgb(68, 68, 68));
    shadow->setBlurRadius(10);
    shadow->setOffset(0);
    this->setGraphicsEffect(shadow);

    auto movie = new QMovie(":/images/gifLabel.gif");
    ui->topLabel->setMovie(movie);
    movie->setSpeed(200);
    movie->start();

    //设置图标
    ui->account->lineEdit()->addAction(QPixmap(":/images/username.png"),QLineEdit::LeadingPosition);
    ui->passwd->addAction(QPixmap(":/images/passwd.png"),QLineEdit::LeadingPosition);
}


void Widget::on_closeBtn_clicked()
{
    this->close();
}


void Widget::on_minimum_clicked()
{
    this->showMinimized();
}


void Widget::on_loginBtn_clicked()
{
    //点击登录切换界面
    auto name = ui->account->currentText();
    auto pwd = ui->passwd->text();
    if (name == "1173012900" && pwd == "woshishuaige666"){
        auto window = new TestWindow;
        connect(window,&QWidget::destroyed,this,[](){
            qInfo()<<"destory!";
        });
        window->setAttribute(Qt::WA_DeleteOnClose);
        window->show();
        this->close();
    }
}

