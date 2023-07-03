#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QTimerEvent>
#include <QLineEdit>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void paintEvent(QPaintEvent* ev)override;
public:
    void draw(QPainter* painter);
    void buttons();
private:
    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;
    QPushButton* btn4;
    QPushButton* ok;
    int msec; //定时器超时间隔
    QTimer* time;
    QLineEdit* edit;
};
#endif // WIDGET_H
