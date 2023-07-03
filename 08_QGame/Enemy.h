#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"

class Enemy: public Sprite
{
public:
    using Sprite::Sprite;
    void update()override;

};

#endif // ENEMY_H
