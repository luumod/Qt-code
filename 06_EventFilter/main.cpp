#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QWidget ww;
    ww.show();
    ww.installEventFilter(new EventFilterObject(&ww));

    return a.exec();
}
