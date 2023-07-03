#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include <QPixmap>
#include <QPainter>

class Map:public Entity
{
public:
    Map(const QString& mapFilename,qreal speed=3);
    ~Map();
public:
    void draw(QPainter* painter)override;
    void update()override;
private:
    QPixmap pixmap;
    qreal ypos1,ypos2;
    qreal speed; //移动速度
};

#endif // MAP_H
