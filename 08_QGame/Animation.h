#ifndef ANIMATION_H
#define ANIMATION_H

#include <QList>
#include <QPixmap>
#include <QPainter>

class Animation
{
public:
    Animation(int Animation_speed=500);  //相当于每500ms播放一帧图片
    //添加帧图
    void addFrame(const QPixmap& filename);
    QPixmap getFrame(int index)const;
    qsizetype size()const;
    void setPosition(qreal x,qreal y);
    bool finished_ones()const;
public:
    void update();
    void draw(QPainter* painter);
private:
    QList<QPixmap> pixmaps;

    //播放位置
    qreal xpos=-100,ypos=-100;

    //当前下标
    int index=0;

    int Animation_speed=0;

};

#endif // ANIMATION_H
