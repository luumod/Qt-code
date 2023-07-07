#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QObject>
#include <QWidget>

class TestWindow: public QWidget
{

public:
    TestWindow(QWidget* parent=nullptr);
    ~TestWindow();
};

#endif // TESTWINDOW_H
