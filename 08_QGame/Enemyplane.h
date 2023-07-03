#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "Sprite.h"
#include <QPixmap>

class EnemyPlane :public Sprite
{
public:
    EnemyPlane();
    ~EnemyPlane();
    void addAnimation();
    void appear();
    void update()override;
private:
    Animation* enemy_Died_anima=nullptr;
    QList<QString> enemies;
};

#endif // ENEMYPLANE_H
