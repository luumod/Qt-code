#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QLabel>
#include <QWhatsThis>
#include <QLineEdit>
#include <QMenu>

constexpr int W=50,H=50;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void testWidgetSize(){
        QWidget w;
        w.show();
        qInfo()<<w.x()<<w.y()<<w.pos();
        qInfo()<<w.width()<<w.height()<<w.size();

        qInfo()<<w.geometry()<<w.frameGeometry();

        //移动窗口位置
        //w.move(50,50);// 带边框
        //调整大小
        //w.resize(250,250);

        //设置几何大小
        //w.setGeometry(50,50,150,150);//不带边框

        //固定大小
        //w.setFixedSize(250,250); //resize无效
        //w.resize(600,600);

        //设置窗口最大，最小 大小
        w.setMaximumSize(640,480);
        w.setMinimumSize(250,250);
    }
    void testPos(){
        QWidget w;
        w.setGeometry(600,300,640,480);
        auto w1=new QWidget(&w);
        auto w2=new QWidget(w1);
        auto w3=new QWidget(&w);

        w1->setGeometry(100,100,100,100);
        w1->setStyleSheet("background-color:red");
        w2->setGeometry(20,20,20,20);
        w2->setStyleSheet("background-color:blue");

        qInfo()<<w1->pos();

        //子窗口的位置在父窗口上的位置
        qInfo()<<w1->mapToParent(QPoint(50,50));

        //父窗口的位置在子窗口上的位置
        qInfo()<<w1->mapFromParent(QPoint(120,120));

        //子子窗口位置在父窗口上的位置
        qInfo()<<w2->mapTo(&w,QPoint(0,0));

        //全局坐标相对于窗口上的位置
        qInfo()<<w.mapFromGlobal(QPoint(660,340));

        w.show();
    }
    void testWidgetMargins(){
        QWidget w;
        w.resize(640,480);
        w.move(150,150);

        auto lb=new QLabel("文本边距",&w);
        lb->resize(150,150);
        lb->setContentsMargins(20,20,0,0); //设置内容边距

        w.show();
    }
    void testWindowCursor(){
        QWidget w;
        w.resize(640,480);
        w.setCursor(QCursor(Qt::OpenHandCursor));

        auto btn=new QPushButton("点击切换按钮",&w);
        QObject::connect(btn,&QPushButton::clicked,&w,[&](){
            static int i=0;
            w.setCursor(QCursor(Qt::CursorShape(i++)));
            i%=20;
        });

        w.setCursor(QCursor(QPixmap(":/ylh.png"),0,0)); //path 定义光标的热点为 0，0
        w.show();

        //光标的全局位置
        qInfo()<<QCursor::pos();
        QCursor::setPos(500,500);
    }
    void testWindowIcon(){
        QWidget* w=new QWidget();
        w->setWindowIcon(QIcon(QString(":/ylh.png")));

        w->show();
    }
    void testWindowText(){
        QWidget* w=new QWidget();
        w->resize(640,480);
        w->setWindowIcon(QIcon(QString(":/ylh.png")));
        w->setWindowTitle("这是一个窗口[*]"); //构造函数
        //自动保存: [*]

        qInfo()<<w->windowTitle();

        w->setWindowModified(true);
        auto btn=new QPushButton("保存",w);
        QObject::connect(btn,&QPushButton::clicked,w,[=](){
            w->setWindowModified(false);
        });

        w->setWindowOpacity(0.5);

        w->show();
    }
    void testWindowState(){
        QWidget* w=new QWidget();
        w->resize(640,480);
        qInfo()<<w->windowState();

        //设置窗口状态
        //w->setWindowState(Qt::WindowState::WindowFullScreen);

        auto btn=new QPushButton("切换",w);
        QObject::connect(btn,&QPushButton::clicked,w,[=](){
            //if (w->windowState()==Qt::WindowState::WindowNoState){
            //    w->setWindowState(Qt::WindowState::WindowMaximized);
            //}
            //else if (w->windowState()==Qt::WindowState::WindowMaximized){
            //    w->setWindowState(Qt::WindowState::WindowNoState);
            //}
            //在普通与最大化之间切换
            w->setWindowState(w->windowState() ^ Qt::WindowState::WindowMaximized);
        });
        w->show();
    }
    void testWindowFlag(){
        QWidget* w=new QWidget();
        w->resize(640,480);
        auto btn=new QPushButton("button",w);

        qInfo()<<w->windowFlags()<<btn->windowFlags();//显示窗口的状态标志
        w->show();
    }
    void testWindowParent(); //父子关系
    void testCengji(); //层级控制
    void testJiaohu(); //交互状态
    void testFocus();  //焦点控制
    void testContextMenu(); //右键弹出菜单
public:
    void mousePressEvent(QMouseEvent* event)override; //testWindowParent
public slots:
    void onContextMenu(const QPoint&);
private:
    QMenu* cxt_menu;
};
#endif // WIDGET_H
