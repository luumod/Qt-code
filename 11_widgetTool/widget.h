#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeySequenceEdit>
#include <QDebug>
#include <QPushButton>
#include <QShortcut>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QTimer>
#include <QComboBox>
#include <QStyle>
#include <QSlider>
#include <QScrollBar>
#include <QDial>
#include <QRubberBand>
#include <QMouseEvent>
#include <QCheckBox>
#include <QString>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void init();
    void testQKeySequenceEdit();
    void testQSpinBox();
    void testQDateTimeEdit();
    void testQComboBox();
    void testQSlider();
    void testQRubberBand();
public slots:
    void onClicked();
    void activated_Ctrl_Shift_A();
    void timeGoOn();
public:
    void mousePressEvent(QMouseEvent* ev)override;
    void mouseMoveEvent(QMouseEvent* ev)override;
    void mouseReleaseEvent(QMouseEvent* ev)override;
private:
    QKeySequenceEdit* key;
    QSpinBox* sp;
    QDateTimeEdit* dt;
    QComboBox* cbx;
    QSlider* sld;
    QRubberBand* rband;
    QPoint origin;
};
#endif // WIDGET_H
