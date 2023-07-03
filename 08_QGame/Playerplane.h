#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "Sprite.h"
#include <QKeyEvent>

class PlayerPlane: public Sprite
{
public:
    using Sprite::Sprite;
public:
    void fire();
    void AttackEnemy();
};

#endif // PLAYERPLANE_H
