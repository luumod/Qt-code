#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QDragEnterEvent>
#include "findqtenv.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initUi();
public:
    void dragEnterEvent(QDragEnterEvent* ev)override;
    void dropEvent(QDropEvent* ev)override;
public slots:
    void onOpenFile();
private:
    QComboBox* m_qtVersionCbx;
    QComboBox* m_qtCompilerCbx;

    QPushButton* m_exeFileBtn;
    QPushButton* m_generateBtn;
    QPushButton* m_testBtn;
    QPushButton* m_aboutBtn;

    findQtEnv m_qtEnv;
};
#endif // WIDGET_H
