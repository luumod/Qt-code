#ifndef SPRITE_H
#define SPRITE_H

#include "Entity.h"
#include <QVector2D>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include "Animation.h"
#include <QMap>

//精灵继承抽象类
class Sprite: public Entity
{
public:
    Sprite();
    Sprite(int x,int y,const QString& pixmapFileName,qreal speedF);
    ~Sprite();
public:
    //需要实现抽象接口
    void update()override;
    void draw(QPainter* painter)override;
public:
    void moveBy(qreal dx,qreal dy);
    qreal getSpeed()const{return speed;}
    void setSpeed(qreal speedF){speed=speedF;}
    void setPosition(qreal x,qreal y){
        position.setX(x);
        position.setY(y);
    }
    void setVelocity(qreal x,qreal y){
        velocity.setX(x);
        velocity.setY(y);
    }
    QVector2D& getVelocity(){
        return velocity;
    }
    QVector2D& getPosition(){
        return position;
    }
    const QPixmap& getPixmap()const{
        return pixmap;
    }
    const QRect& getCollider()const{
        return collider;
    }
public:
    //添加动画
    Animation* addAnimation(const QString& tag,Animation* animation);
    void runAnimation(const QString& tag,bool autoDel=false);
private:
    QVector2D position;
    QVector2D velocity; //速率
    QPixmap pixmap;
    qreal speed;
    QRect collider; //碰撞器
private:
    Animation* currentAnima=nullptr;
    QMap<QString,Animation*> anima;
    bool autoDel=false; //控制只播放一次动画
};

#endif // SPRITE_H
