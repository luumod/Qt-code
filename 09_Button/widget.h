#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void testPushButton();
    void testCommandLinkButton();
    void testToolButton();
    void testRadioButton();
    void testButtonGroup();
};
#endif // WIDGET_H
