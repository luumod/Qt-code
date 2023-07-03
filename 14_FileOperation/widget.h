#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCloseEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void showEvent(QShowEvent* ev)override;
    void closeEvent(QCloseEvent* ev)override;
};
#endif // WIDGET_H
