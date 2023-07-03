#include <QApplication>
#include "Game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game;
    game.initGame(512,760,"飞机大战");
    game.run();

    return a.exec();
}
