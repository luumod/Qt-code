#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>
#include "Map.h"
#include "Enemyplane.h"
#include <QElapsedTimer>

class Game:public QWidget
{
    Q_OBJECT
public:
    Game(QWidget* parent=nullptr);
    ~Game();
    //游戏运行
    void run();
    //初始化游戏
    void initGame(int w,int h,const QString& title);
    //清理游戏
    void clearGame();
    //更新游戏
    void updateGame();
    ///绘制游戏
    void drawGame(QPainter* painter);
public slots:
    void slotOnKeyPress();
    void slotOnBulletFire();
    void slotOnEnemyAppear();
    void slotOnMyDied();
protected:
    void paintEvent(QPaintEvent* ev)override;
    void closeEvent(QCloseEvent* ev)override;
    void keyPressEvent(QKeyEvent* ev)override;
    void keyReleaseEvent(QKeyEvent* ev)override;
public:
    inline static qreal WIDTH=0;
    inline static qreal HEIGHT=0;
    inline static QElapsedTimer globalElaspedTimer;
    inline static int score=0;
private:
    QList<int> keys;
    Map* map;
    QTimer* key_time;
    QTimer* fire_time;
    QTimer* enemy_time;
    QTimer* exit_time;
    EnemyPlane* enemy;
};

#endif // GAME_H
