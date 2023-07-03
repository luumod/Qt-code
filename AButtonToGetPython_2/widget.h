#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <Python.h>
#include <QMessageBox>
#include <QTextEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void init();
    void setQPushButton();
    void setQTextEdit();
public slots:
    void actionOnButtonMess();
    void actionOnButtonList();
private:
    QPushButton* button1,*button2;
    QTextEdit* edit;
    QLineEdit* input;
    PyObject* Module;
    int start=1,end=10;

};
#endif // WIDGET_H
