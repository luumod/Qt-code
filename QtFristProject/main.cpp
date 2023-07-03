#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[]) //带参数版本
{
    QApplication a(argc, argv);  //应用程序对象
    Widget w;
    w.show();
    return a.exec();
}
