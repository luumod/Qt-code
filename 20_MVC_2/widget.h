#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QTreeView>
#include <QListView>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QListWidget>
#include <QTreeWidget>
#include <QMainWindow>

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void init();
    void test1();
    void test2();
    //************ Widget  **************
    void initW();
    void testW1();
    void testW2();
private:
    QTableView* m_tableView = nullptr;
    QTreeView* m_treeView = nullptr;
    QListView* m_listView = nullptr;
    QStandardItemModel* m_itemModel = nullptr;

    QTableWidget* m_tableWidget = nullptr;
    QListWidget* m_listWidget = nullptr;
    QTreeWidget* m_treeWidget = nullptr;
};
#endif // WIDGET_H
