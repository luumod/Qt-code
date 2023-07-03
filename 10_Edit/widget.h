#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void init();
    void testLineEdit();
    void testTextEdit();
public slots:
    void onClicked();
private:
    QLineEdit* edit;
    QTextEdit* tedit;
};
#endif // WIDGET_H
