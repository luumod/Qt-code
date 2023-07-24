#ifndef FULLWINDOW_H
#define FULLWINDOW_H

#include <QWidget>
#include <QLabel>

class FullWindow :public QLabel
{
public:
    FullWindow(QWidget* parent =nullptr);
public Q_SLOTS:
    void setWallpaper(const QString& fileName);
};

#endif // FULLWINDOW_H
