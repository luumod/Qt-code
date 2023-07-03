#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("子窗口");
    resize(640,480);
    auto btn=new QPushButton("切换到主窗口",this);
    //切换主窗口
    connect(btn,&QPushButton::clicked,this,[=](){
        emit this->cutMainWindow("我还想再显示会儿"); //发送信号
        emit this->cutMainWindow();
    });
}
