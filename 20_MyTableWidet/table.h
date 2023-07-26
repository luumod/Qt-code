#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QMainWindow>
#include <QStringList>
#include <QTableWidget>

namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = nullptr);
    ~table();
    void setRowCount(int num);
    void setColCount(int num);
    void setRowHeader(const QStringList& rowHeader);
    void setColHeader(const QStringList& colHeader);
    void generate();
private:
    Ui::table *ui;

    int m_rowCount;
    int m_colCount;
    QStringList m_rowHeader;
    QStringList m_colHeader;

    QTableWidget* m_tableWidget;
};

#endif // TABLE_H
