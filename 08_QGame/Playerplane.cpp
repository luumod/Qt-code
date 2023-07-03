#include "Playerplane.h"
#include "Manager.h"
#include "Bullet.h"
#include "GlobalDefinition.h"
#include "Bullet.h"
#include "Enemyplane.h"
#include "QWidget"
#include "Game.h"

void PlayerPlane::fire()
{
    auto bullet=new Bullet(0,0,":/images1/biu1_trans.png",6);
    bullet->setPosition(getPosition().x()+getPixmap().width()/2-bullet->getPixmap().width()/2,getPosition().y());
    bullet->setType(Entity_type::ET_MY_BULLET);

    Mgr->addEntity(bullet);

    bullet->getVelocity().setY(-1);
}

void PlayerPlane::AttackEnemy()
{
    auto bullets= Mgr->getQSetType<Bullet>(Entity_type::ET_MY_BULLET);
    auto enemies= Mgr->getQSetType<EnemyPlane>(Entity_type::ET_ENEMY);

    for (auto& b: bullets){
        for (auto& e: enemies){
            //我方攻击敌机
            if (b->getCollider().intersects(e->getCollider())){
                b->Destory();
                e->runAnimation("enemyplane_Died",true);
                if (e->type()==Enemy_Type::EMY_SMALL){
                    Game::score+=10;
                }
                else if (e->type()==Enemy_Type::EMY_MIDDLE){
                    Game::score+=20;
                }
                else if (e->type()==Enemy_Type::EMY_BIG){
                    Game::score+=50;
                }
                else if (e->type()==Enemy_Type::EMY_WORST){
                    Game::score+=100;
                }
                else if (e->type()==Enemy_Type::EMY_BOSS){
                    //通关
                    Game::score+=1000;
                }
                break;
            }
            //我方碰撞敌机
            if (getCollider().intersects(e->getCollider())){
                //我方死亡
                e->runAnimation("enemyplane_Died",true);
                this->runAnimation("myplane_Died",true);
            }
        }
    }
}
