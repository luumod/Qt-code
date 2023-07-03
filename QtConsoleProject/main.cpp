//#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    w.show();

    qInfo()<<"Hello Qt!\n";
    return a.exec();
}
