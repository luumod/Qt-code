#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter> //画家
#include <qrandom.h> //随机数，没有大写
#include <QDebug>
#include <QColor>
#include <QTimer>
#include <QPolygon>
#include <QPainterPath>
#include <QKeyEvent>
#include <QGlyphRun>

class Sprite{
public:
    Sprite(){}
    Sprite(int x,int y,int w,int h,const QPixmap& pix)
        :pos(x,y),size(w,h),pix(pix){}
    void draw(QPainter* painter){
        if (isActive){
            painter->drawPixmap(pos,pix.scaled(size));
        }
    }
    void update(){
        collider.addRect(QRect(pos,size));
    }
    void move(int dx,int dy){
        pos.rx()+=dx;
        pos.ry()+=dy;
    }
    void setActive(bool active){
        isActive=active;
    }
private:
    QPoint pos;
    QSize size;
    QPixmap pix;
    bool isActive;
public:
    QPainterPath collider;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void testdraw1();
    void testPen(QPainter* painter);
    void testBrush(QPainter* painter);
    void testBrush2(QPainter* painter);
    void testLinearGradient(QPainter* painter);
    void testRadialGradient(QPainter* painter);
    void testConicalGradient(QPainter* painter);
    void testGradientMode(QPainter* painter);
    void testTransform(QPainter* painter);
    void testDraw(QPainter* painter);
    void testPainterPath(QPainter* painter);
    void testDrawText(QPainter* painter);
    void testDrawImage(QPainter* painter);
    void testImage(QPainter* painter);
    void ProcessPicture();
    void testDrawGlyphRun(QPainter* painter);
public:
    void paintEvent(QPaintEvent* ev)override;//绘制函数：必须把绘图的操作放在个事件处理函数中
    void keyPressEvent(QKeyEvent* ev)override;

private:
    QPixmap pix;
    QBitmap mask;
private:
    Sprite* s1,* s2;
};
#endif // WIDGET_H
