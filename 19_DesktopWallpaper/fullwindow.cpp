#include "fullwindow.h"
#include "toolsMod/finddektophwnd.h"

FullWindow::FullWindow(QWidget *parent)
    :QLabel(parent)
{
    this->showFullScreen();//全屏

    FindDektopHwnd::SetParent(this,nullptr);
}

void FullWindow::setWallpaper(const QString &fileName)
{
    if (!fileName.isEmpty()){
        this->setPixmap(QPixmap(fileName));
    }
}
