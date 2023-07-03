#include "Map.h"
#include "Game.h" //获取地图大小

Map::Map(const QString& mapFilename,qreal speed)
    :speed(speed)
{
    ypos1=-Game::HEIGHT;
    ypos2=0;
    pixmap.load(mapFilename);
}

Map::~Map()
{

}

void Map::draw(QPainter *painter)
{
    painter->drawPixmap(0,ypos1,pixmap);
    painter->drawPixmap(0,ypos2,pixmap);
}

void Map::update()
{
    ypos1+=speed;
    if (ypos1>=0){
        ypos1=-Game::HEIGHT;
    }
    ypos2+=speed;
    if (ypos2>=Game::HEIGHT){
        ypos2=0;
    }
}
