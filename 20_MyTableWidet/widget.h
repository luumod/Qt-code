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
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void init();
public:
    void onNewBtn();

private:
    Ui::Widget *ui;

    InputInfo* m_windowInput = nullptr; //输入窗口
    inputTableHeader* m_windowInputHeader = nullptr; //输入表头

    int m_tableRowCount;
    int m_tableColCount;

    //生成表格
    table* m_tab = nullptr;
};
#endif // WIDGET_H
