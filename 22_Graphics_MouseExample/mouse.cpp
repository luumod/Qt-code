﻿#include "mouse.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    //控制在 [0,2*pi] 之间，保持一个圆
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

//! [0]
Mouse::Mouse() : m_color(QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256))
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
}
//! [0]

//! [1]
QRectF Mouse::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}
//! [1]

//! [2]
QPainterPath Mouse::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}
//! [2]

//! [3]
void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(m_color);
    painter->drawEllipse(-10, -20, 20, 40);

    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    // Nose
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // Pupils
    painter->drawEllipse(QRectF(-8.0 + m_mouseEyeDirection, -17, 4, 4));
    painter->drawEllipse(QRectF(4.0 + m_mouseEyeDirection, -17, 4, 4));

    // Ears
    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
    painter->drawEllipse(-17, -12, 16, 16);
    painter->drawEllipse(1, -12, 16, 16);

    // Tail
    QPainterPath path(QPointF(0, 20));
    path.cubicTo(-5, 22, -5, 22, 0, 25);
    path.cubicTo(5, 27, 5, 32, 0, 30);
    path.cubicTo(-5, 32, -5, 42, 0, 35);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);
}
//! [3]

//! [4]
void Mouse::advance(int step)
{
    //每一帧运行都会调用这个函数 step为1时运行
    if (!step)
        return;
    //! [4]
    // Don't move too far away
    //! [5]
    //! mapFromScene会得到每一个Item即mouse的实际坐标位置

    //qInfo()<<mapToScene(QPointF(0,0));
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        //调整角度
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // 往左旋转
            // Rotate left
            m_angle += (m_angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // 往右旋转
            // Rotate right
            m_angle += (m_angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(m_angle) < 0) {
        m_angle += 0.25;
    } else if (::sin(m_angle) > 0) {
        m_angle -= 0.25;
        //! [5] //! [6]
    }
    //! [6]

    // Try not to crash with any other mice
    //! [7]
    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                                                             << mapToScene(0, 0)
                                                             << mapToScene(-30, -50)
                                                             << mapToScene(30, -50));

    for (const QGraphicsItem *item : dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            m_angle += 0.5;
        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            m_angle -= 0.5;
            //! [7] //! [8]
        }
        //! [8] //! [9]
    }
    //! [9]

    // Add some random movement
    //! [10]
    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            m_angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            m_angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }
    //! [10]

    //! [11]
    m_speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

    qreal dx = ::sin(m_angle) * 10;
    m_mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(m_speed) * 3)));
}
//! [11]
