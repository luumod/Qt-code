#include "table.h"
#include "ui_table.h"

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);

}

table::~table()
{
    delete ui;
}

void table::setRowCount(int num)
{
    m_rowCount = num;
}

void table::setColCount(int num)
{
    m_colCount = num;
}

void table::setRowHeader(const QStringList& rowHeader)
{
    m_rowHeader = rowHeader;
}

void table::setColHeader(const QStringList& colHeader)
{
    m_colHeader = colHeader;
}

void table::generate()
{
    //生成表格
    m_tableWidget = new QTableWidget(this);
    this->setCentralWidget(m_tableWidget);
    m_tableWidget->setRowCount(m_rowCount);
    m_tableWidget->setColumnCount(m_colCount);
    m_tableWidget->setHorizontalHeaderLabels(m_colHeader);
    m_tableWidget->setVerticalHeaderLabels(m_rowHeader);
}
