#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class InputInfo;
class inputTableHeader;
class table;
class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    InputInfo* m_windowInput; //输入窗口
    inputTableHeader* m_windowInputHeader; //输入表头

    int m_tableRowCount;
    int m_tableColCount;

    //生成表格
    table* m_tab;
};
#endif // WIDGET_H
