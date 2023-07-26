#include "widget.h"
#include "./ui_widget.h"
#include "inputinfo.h"
#include "inputtableheader.h"
#include "table.h"
#include <QMainWindow>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_windowInput = new InputInfo;
    m_windowInputHeader = new inputTableHeader;

    this->setCentralWidget(ui->tableWidget);
    //打开输入窗口
    connect(ui->btnNewFile,&QPushButton::clicked,this,[=](){
        this->close();
        m_windowInput->show();
    });

    //关闭输入窗口，获取输入的行列数，打开表头输入窗口
    connect(m_windowInput,&InputInfo::finished,this,[=](){
        //输入完成
        m_windowInput->close();
        //获取行列
        m_tableRowCount = m_windowInput->rowCount();
        m_tableColCount = m_windowInput->colCount();

        //打开表头输入窗口
        m_windowInputHeader->show();
        m_windowInputHeader->setCol(m_tableColCount);
        m_windowInputHeader->setRow(m_tableRowCount);
        m_windowInputHeader->input();
    });

    //关闭行列表头输入窗口，生成表格窗口
    connect(m_windowInputHeader,&inputTableHeader::finished,this,[=](){
        m_windowInputHeader->close();
        m_tab = new table;
        m_tab->setRowCount(m_tableRowCount);
        m_tab->setColCount(m_tableColCount);
        m_tab->setRowHeader(m_windowInputHeader->rowHeader());
        m_tab->setColHeader(m_windowInputHeader->colHeader());
        m_tab->generate();

        m_tab->show();
    });

}

Widget::~Widget()
{
    delete ui;
}

