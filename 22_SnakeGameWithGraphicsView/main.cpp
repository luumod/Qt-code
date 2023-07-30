#include <QApplication>
#include <QGraphicsView>
#include "snake.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //创建游戏视图
    QGraphicsView view;
    //创建游戏场景
    Snake* obj = new Snake(0,0,640,480,&view);
    view.setScene(obj);
    view.show();

    return a.exec();
}
