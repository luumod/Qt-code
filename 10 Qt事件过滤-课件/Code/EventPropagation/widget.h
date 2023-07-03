#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
class Button : public QPushButton
{
public:
    Button(QWidget*parent = nullptr);
    void mousePressEvent(QMouseEvent*ev)override;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void mousePressEvent(QMouseEvent*ev)override;
};
#endif // WIDGET_H
