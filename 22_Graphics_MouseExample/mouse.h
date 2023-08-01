#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsItem>

//! [0]
class Mouse : public QGraphicsItem
{
public:
    Mouse();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    qreal m_angle = 0;
    qreal m_speed = 0;
    qreal m_mouseEyeDirection = 0;
    QColor m_color;
};
//! [0]

#endif
