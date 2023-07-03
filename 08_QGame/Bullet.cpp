#include "Bullet.h"


void Bullet::update()
{
    if (getPosition().y()<0){
        Destory();
    }
    Sprite::update();
}
