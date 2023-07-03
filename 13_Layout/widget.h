#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QGridLayout>
#include <QCheckBox>
#include <QFormLayout>
#include <QStackedLayout>
#include <QSplitter>
#include <QTextEdit>
#include <QStackedWidget>
#include <QTabWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void testQBoxLayout();
    void testNestLayout();
    void testButton();
    void testGridLayout();
    void testQFormLayout();
    void testQStackedLayout();
    void testQSplitter();
    void testQStackedWidget();
    void testQTabWidget();
    ~Widget();
};
#endif // WIDGET_H
