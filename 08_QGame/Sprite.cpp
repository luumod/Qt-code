#include "Sprite.h"
#include <QDebug>

Sprite::Sprite()
{

}

Sprite::Sprite(int x, int y, const QString &pixmapFileName,qreal speedF)
    :position(x,y),speed(speedF)
{
    pixmap.load(pixmapFileName);
}

Sprite::~Sprite()
{
    foreach (Animation* x, anima) {
        delete x;
        x=nullptr;
    }
}

void Sprite::update()
{
    position+=velocity*speed; //velocity: -1 0 1
    //更新碰撞器
    collider=QRect(position.toPoint(),pixmap.size());

    if (currentAnima){
        currentAnima->update(); ///更新动画
        currentAnima->setPosition(position.x(),position.y());
        if (currentAnima->finished_ones() && autoDel){
            Destory(); //播放完成动画后销毁
        }
    }
}

void Sprite::draw(QPainter *painter)
{
    if (!currentAnima){
        painter->drawPixmap(position.toPoint(),pixmap);
    }
    else{
        currentAnima->draw(painter);
    }
}

void Sprite::moveBy(qreal dx, qreal dy)
{
    position+=QVector2D(dx,dy);
}

Animation *Sprite::addAnimation(const QString &tag, Animation *animation)
{
    if (!animation){
        qWarning()<<animation<<"为空!";
        return nullptr;
    }
    if (anima.contains(tag)){
        qWarning()<<"已经存在! 标签为"<<tag<<"的动画";
        return animation;
    }
    anima.insert(tag,animation);
    return animation;
}

void Sprite::runAnimation(const QString &tag,bool autoDel) //播放完成
{
    this->autoDel=autoDel;
    if (!anima.contains(tag)){
        qWarning()<<tag<<"动画不存在! ";
        return ;
    }
    currentAnima=anima.value(tag);
}
