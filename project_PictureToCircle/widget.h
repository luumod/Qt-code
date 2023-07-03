#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBitmap>
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPaintEvent>
#include <QMimeData>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void paintEvent(QPaintEvent* ev)override;
    void dragEnterEvent(QDragEnterEvent* ev)override;
    void dropEvent(QDropEvent* ev)override;
public:
    bool Handle();
    void DrawText(QPainter* painter);
public:
    QBitmap mask; //
    QPixmap pix;
    QString filename;
};
#endif // WIDGET_H
