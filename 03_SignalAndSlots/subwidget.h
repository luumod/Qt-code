#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = nullptr);
    ~SubWidget(){}

signals:
    //自定义信号函数: 只声明无定义
    void cutMainWindow();
    //信号的重载
    void cutMainWindow(const QString&);
};

#endif // SUBWIDGET_H
