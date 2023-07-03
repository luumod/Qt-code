#include "Animation.h"
#include "Game.h"

Animation::Animation(int Animation_speed)
    :Animation_speed(Animation_speed)
{

}

void Animation::addFrame(const QPixmap &filename)
{
    pixmaps.append(QPixmap(filename));
}

QPixmap Animation::getFrame(int index) const
{
    assert(index>=0 && index<size());
    return pixmaps[index];
}

qsizetype Animation::size() const
{
    return pixmaps.size();
}

void Animation::setPosition(qreal x,qreal y)
{
    xpos=x;
    ypos=y;
}

bool Animation::finished_ones() const
{
    return index==size()-1;
}

void Animation::update()
{
    index=Game::globalElaspedTimer.elapsed()/Animation_speed%size();
}

void Animation::draw(QPainter *painter)
{
    painter->drawPixmap(xpos,ypos,pixmaps[index]);
}
