#include "widget.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QShortcut>
#include <QKeySequence>
#include <QToolBar>
#include <QStyle>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QStatusBar>
#include <QLabel>
#include <QPlainTextEdit>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QApplication>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    resize(640,480);
    testMenuBar();
    testToolBar();
    testStatusBar();
    testDockWidget();
    SystemTrayIcon();
}

MainWindow::~MainWindow()
{
}

void MainWindow::testMenuBar()
{
    auto mainMenuBar=menuBar();
    QMenu* fileMenu=mainMenuBar->addMenu("文件");
    QMenu* pro=fileMenu->addMenu("项目");
    pro->addAction("打开");
    pro->addAction("保存",this,&MainWindow::on_Ctrl_S,QKeySequence("Ctrl+S"));
    pro->addAction("新建");
    fileMenu->addSeparator();
    fileMenu->addAction("关闭");
    fileMenu->addAction("视图");

    QMenu* editMenu=mainMenuBar->addMenu("编辑(&E)");

    connect(mainMenuBar,&QMenuBar::hovered,this,[=](QAction* act){
        qInfo()<<act->text();
    });
}

void MainWindow::testToolBar()
{
    auto mainToolBar=addToolBar("ToolBar1");
    mainToolBar->addAction(style()->standardPixmap(QStyle::StandardPixmap::SP_ArrowRight),"前进");
    mainToolBar->addAction(style()->standardPixmap(QStyle::StandardPixmap::SP_ArrowLeft),"后退");
    mainToolBar->addSeparator();

    auto chx=new QCheckBox("自动保存",this);
    mainToolBar->addWidget(chx);

    auto edit=new QLineEdit(this);
    edit->setPlaceholderText("搜索内容");
    mainToolBar->addWidget(edit);

    auto btn=new QPushButton("搜索",this);
    mainToolBar->addWidget(btn);

    auto toolbtn=new QToolButton(this);
    toolbtn->resize(150,150);
    toolbtn->setText("返回桌面");
    toolbtn->setIcon(style()->standardPixmap(QStyle::StandardPixmap::SP_DesktopIcon));
    toolbtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    mainToolBar->addWidget(toolbtn);
}

void MainWindow::testStatusBar()
{
    auto sBar=statusBar();
    sBar->addWidget(new QLabel("准备就绪",this));
    sBar->addWidget(new QPushButton("发射",this));
    sBar->addPermanentWidget(new QLabel("完成",this));
}

void MainWindow::testDockWidget()
{
    //设置中心区域
    setCentralWidget(new QPlainTextEdit(this));

    auto DockWidget1=createDockWidget("解决方案资源管理器");
    auto DockWidget2=createDockWidget("团队资源管理器");
    auto DockWidget3=createDockWidget("命令窗口");
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,DockWidget1);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,DockWidget2);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,DockWidget3);

    //设置浮动窗口的堆叠
    tabifyDockWidget(DockWidget1,DockWidget2);
    tabifyDockWidget(DockWidget2,DockWidget3);
}

void MainWindow::SystemTrayIcon()
{
    auto trayIcon=new QSystemTrayIcon(QIcon(":/icon.png"),this);
    trayIcon->show();

    QMenu* trayMenu=new QMenu(this);
    trayMenu->addAction("退出",qApp,[=](){
        qApp->quit(); //退出系统
    });
    trayMenu->addSeparator();
    trayMenu->addAction("最小化",this,[=](){
        this->setVisible(!this->isVisible());
    });
    trayMenu->addAction("别点我",this,[=](){
        //trayIcon->showMessage("警告，电脑即将爆炸","错误操作，爆炸倒计时!");
        qInfo()<<"!!!!";
    });
    //添加上下文菜单
    trayIcon->setContextMenu(trayMenu);

    trayIcon->setToolTip("你好");

    //处理激活原因
    connect(trayIcon,&QSystemTrayIcon::activated,this,[=](QSystemTrayIcon::ActivationReason reason){
        switch (reason) {
        case QSystemTrayIcon::Unknown:  //0

            break;
        case QSystemTrayIcon::Context:  //1

            break;
        case QSystemTrayIcon::DoubleClick://2
            //弹出菜单
            trayIcon->contextMenu()->popup(QCursor::pos());
            break;
        case QSystemTrayIcon::Trigger:  //左键点击
            //窗口切换
            this->setVisible(!this->isVisible());
            break;
        default:
            break;
        }
        qInfo()<<reason;
    });
}

void MainWindow::on_Ctrl_O()
{
    qInfo()<<__FUNCTION__;

    statusBar()->showMessage("正在打开",2000);
}

void MainWindow::on_Ctrl_S()
{
    qInfo()<<__FUNCTION__;

    statusBar()->showMessage("保存成功",2000);
}

void MainWindow::on_Alt_E()
{
    qInfo()<<__FUNCTION__;

    statusBar()->showMessage("打开编辑",2000);
}

