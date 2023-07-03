#include "Enemy.h"
#include "Game.h"

void Enemy::update()
{
    if (getPosition().y()>Game::HEIGHT){
        Destory(); //销毁敌机
    }
    Sprite::update();
}
