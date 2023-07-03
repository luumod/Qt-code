#include "Enemyplane.h"
#include "Manager.h"
#include "Game.h"
#include <qrandom.h>
#include "GlobalDefinition.h"

EnemyPlane::EnemyPlane()
{
    enemies.append(":/images1/enemy1_trans.png"); //0 1 2 3 4
    enemies.append(":/images1/enemy2_trans.png");
    enemies.append(":/images1/enemy3_trans.png");
    enemies.append(":/images1/enemy4_trans.png");
    enemies.append(":/images1/Boss_trans.png");
}

EnemyPlane::~EnemyPlane()
{
    enemies.clear();
}

void EnemyPlane::addAnimation()
{
    enemy_Died_anima->addFrame(QPixmap(":/common/boom1_trans.png"));
    enemy_Died_anima->addFrame(QPixmap(":/common/boom2_trans.png"));
    enemy_Died_anima->addFrame(QPixmap(":/common/boom3_trans.png"));
    enemy_Died_anima->addFrame(QPixmap(":/common/boom4_trans.png"));
    enemy_Died_anima->addFrame(QPixmap(":/common/boom5_trans.png"));
    enemy_Died_anima->addFrame(QPixmap(":/common/boom6_trans.png"));
}

void EnemyPlane::appear()
{
    qInfo()<<Game::score;

    Sprite* e=nullptr;
    if (Game::score<120){
        e=new Sprite(0,0,enemies[0],3);
    }
    else if (Game::score>=120 && Game::score<320){
        e=new Sprite(0,0,enemies[QRandomGenerator::global()->bounded(0,2)],5);
    }
    else if (Game::score>=320 && Game::score<600){
        e=new Sprite(0,0,enemies[QRandomGenerator::global()->bounded(0,3)],2);
    }
    else if (Game::score>=600 && Game::score<1000){
        e=new Sprite(0,0,enemies[QRandomGenerator::global()->bounded(0,4)],2);
    }
    else{
        //Boss出现
        e=new Sprite(0,0,enemies[QRandomGenerator::global()->bounded(0,4)],4);
    }

    e->setPosition(QRandomGenerator::global()->bounded(Game::WIDTH-e->getPixmap().width()),-50);
    enemy_Died_anima = e->addAnimation("enemyplane_Died",new Animation(120));
    addAnimation(); //添加动画

    e->setType(Entity_type::ET_ENEMY);

    Mgr->addEntity(e);

    e->getVelocity().setY(1);

}

void EnemyPlane::update()
{
    if (getPosition().y()>Game::HEIGHT){
        Destory();
    }
    Sprite::update();
}
