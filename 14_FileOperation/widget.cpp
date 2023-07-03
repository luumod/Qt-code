#include "widget.h"
#include <QIcon>
#include <QSettings>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //setWindowTitle("我的窗口");
    //setWindowIcon(QIcon("icon.jpg"));
}

Widget::~Widget()
{
}

void Widget::showEvent(QShowEvent *ev)
{
    QSettings sets("./login_info.ini",QSettings::Format::IniFormat);
    setWindowTitle(sets.value("windowTitle").toString());
    setWindowIcon(sets.value("windowIcon").value<QIcon>());
    restoreGeometry(sets.value("geometry").toByteArray());
}

void Widget::closeEvent(QCloseEvent *ev)
{
    QSettings sets("./login_info.ini",QSettings::Format::IniFormat);
    sets.setValue("windowTitle",windowTitle());
    sets.setValue("windowIcon",windowIcon());
    sets.setValue("geometry",saveGeometry());
}

