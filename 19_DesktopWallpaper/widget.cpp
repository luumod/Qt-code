#include "widget.h"
#include <QPixmap>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include "toolsMod/eventfilterobject.h"
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //设置固定大小
    setFixedSize(350,640);
    //边框隐藏
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint |
                         Qt::WindowType::WindowStaysOnTopHint);
    //窗口透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_DeleteOnClose);
    //可拖动
    installEventFilter(new EventFilterObject(this));

    init();

    setSystemTray();


}

void Widget::init()
{
    //加载模型资源
    loadModelResource();

    //设置窗口的创建，不能指定父对象，这样的话才是两个窗口
    m_windowSettings = new Settings;
    //模型资源，用label加载
    m_roleModelLab = new QLabel(this);
    m_roleModelLab->setScaledContents(true);

    //计时器用于更新模型的动画效果
    QTimer* timer = new QTimer(this);
    timer->callOnTimeout(this,&Widget::updateModel);
    timer->start(500);

    m_contextMenu = new QMenu(this);
    m_contextMenu->addAction("设置",m_windowSettings,&Settings::show);
    m_contextMenu->addAction("退出",this,[=](){
        qApp->quit();
    });


    //设置桌面壁纸
    //m_wallpaper = new FullWindow();

    currentPicture = "summerGril";

    connect(m_windowSettings,&Settings::ChangeModel,this,[=](const QString& form){
        if (!m_roles[form].isEmpty()){
            currentPicture = form;
        }
    });
    connect(m_windowSettings,&Settings::ChangeWallpeper,this,[=](const QString& fileName){
        m_wallpaper->setWallpaper(fileName);
    });


    //最后显示模型
    updateModel();
}

void Widget::loadModelResource()
{
    RoleModel role;
    for (int i=0;i<6;i++){
        role.push_back(QString(":/new/prefix1/assets/desktopRole/blackGril/action1-happy/%1.png").arg(i));
    }
    m_roles.insert("blackGril.happy",role);
    role.clear();

    for (int i=0;i<6;i++){
        role.push_back(QString(":/new/prefix1/assets/desktopRole/blackGril/action2-sad/%1.png").arg(i));
    }
    m_roles.insert("blackGril.sad",role);
    role.clear();

    for (int i=0;i<6;i++){
        role.push_back(QString(":/new/prefix1/assets/desktopRole/blackGril/action3-naughty/%1.png").arg(i));
    }
    m_roles.insert("blackGril.naughty",role);
    role.clear();

    for (int i=0;i<6;i++){
        role.push_back(QString(":/new/prefix1/assets/desktopRole/blackGril/action4-shy/%1.png").arg(i));
    }
    m_roles.insert("blackGril.shy",role);
    role.clear();

    for (int i=0;i<6;i++){
        role.push_back(QString(":/new/prefix1/assets/desktopRole/littleBoy/%1.png").arg(i));
    }
    m_roles.insert("littleBoy",role);
    role.clear();

    for (int i=0;i<6;i++){
        role.push_back(QString(":/new/prefix1/assets/desktopRole/summerGril/%1.png").arg(i));
    }
    m_roles.insert("summerGril",role);
    role.clear();

}

void Widget::setSystemTray()
{
    auto tray = new QSystemTrayIcon(QIcon(QPixmap(":/assets/icon.ico")),this);
    //图标的文字提示
    tray->setToolTip("桌面小宠物");
    tray->show();

    QMenu* menu = new QMenu(this);
    menu->addAction("退出",this,[=](){
        qApp->quit();
    });
    tray->setContextMenu(menu);

}

void Widget::updateModel()
{
    this->setFixedSize(m_roles[currentPicture].getQSize());
    m_roleModelLab->setPixmap(m_roles[currentPicture].getAt(m_index));
    m_index = (m_index+1)%m_frames;
}

Widget::~Widget()
{
    delete m_windowSettings;
    m_windowSettings=nullptr;

    delete m_wallpaper;
    m_wallpaper=nullptr;
}

void Widget::resizeEvent(QResizeEvent *ev)
{
    //调整尺寸
    m_roleModelLab->resize(ev->size());
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
}

void Widget::contextMenuEvent(QContextMenuEvent *ev)
{
    //弹出右键菜单
    m_contextMenu->popup(ev->globalPos());
}

