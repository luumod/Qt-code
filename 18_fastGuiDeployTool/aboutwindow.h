#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QObject>
#include <QWidget>

class aboutWindow:public QWidget
{
    Q_OBJECT
public:
    aboutWindow(QWidget* parent=nullptr);
    ~aboutWindow();
};

#endif // ABOUTWINDOW_H
