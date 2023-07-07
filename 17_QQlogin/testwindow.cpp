#include "testwindow.h"
#include <QDebug>

TestWindow::TestWindow(QWidget *parent)
    :QWidget(parent)
{

}

TestWindow::~TestWindow()
{
    qInfo()<<"TestWindow Destory";
}
