#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QPoint>
#include <QEvent>
#include <QMouseEvent>
#include "eventfilterobject.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    //bool eventFilter(QObject* obj,QEvent* ev)override;
private:
    QPoint pressPos;
};
#endif // WIDGET_H
