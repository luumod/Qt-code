#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>
#include <utility>
#include <list>
#include "astarfindway.h"

//-------------------------------------------------------------

class Snake : public QGraphicsScene
{
    Q_OBJECT
public:
    Snake(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
    ~Snake();
    void init();
    void FindWay();
    bool snakeDied()const;
    QGraphicsRectItem* createNode(int x,int y);
    void checkColliders();
    void gameOver();
public slots:
    void AutoMove();
    void normalMove();

signals:
    void emitGenerateFood();
protected:
    void keyPressEvent(QKeyEvent* ev)override;
private:
    void destroyedSnake();
private:
    QList<QGraphicsRectItem*> m_snake;
    QTimer* timerNormalMoveStart = nullptr;
    int timerId2 = 0, timerId3 = 0;
    int m_dirX = 0;
    int m_dirY = 0;
    QGraphicsRectItem* foodItem = nullptr;
    bool isAlive = true;
    AStarFindWay* Astar = nullptr;
    std::list<std::pair<int,int>> m_path;

    QTimer* timerFindWayMoveStart = nullptr;
    bool m_isAutoFind = false; //默认是不自动寻路

};

#endif // SNAKE_H
