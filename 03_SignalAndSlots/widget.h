#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include "subwidget.h"

class SubWidget;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void solve1();
    void solve2(); //信号与槽
    void solve3(); //切换窗口
    void solve4(); //信号与槽重载的解决
public slots:
    //槽函数声明位置
    void onButtonPressed();
    void onButtonReleased();
    void onFromMainToSubWindow();
    void onFromSubToMainWindow();
    void onFromSubToMainWindow(const QString&);
private:
    SubWidget* subwidget=nullptr;
};
#endif // WIDGET_H
