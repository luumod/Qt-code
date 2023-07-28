#include "widget.h"
#include "./ui_widget.h"
#include "inputinfo.h"
#include "inputtableheader.h"
#include "table.h"
#include <QMainWindow>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //connect(this,&QWidget::destroyed,this,[=](){
    //    qApp->closeAllWindows();
    //});
    init();
    this->setAttribute(Qt::WA_QuitOnClose,true);
    m_windowInputHeader->setAttribute(Qt::WA_QuitOnClose,false);
    m_tab->setAttribute(Qt::WA_QuitOnClose,false);
    m_windowInput->setAttribute(Qt::WA_QuitOnClose,false);

    onNewBtn();
}

Widget::~Widget()
{
    qInfo()<<"this->close";
    //delete m_windowInputHeader;
    //delete m_tab;
    //m_windowInputHeader->close();
    //m_tab->close();
    delete ui;
}

void Widget::init()
{
    m_windowInput = new InputInfo;
    m_windowInputHeader = new inputTableHeader;
    m_tab = new table;
}

void Widget::onNewBtn()
{

    //打开输入窗口
    connect(ui->btnNewFile,&QPushButton::clicked,this,[=](){
        m_windowInput->show();
    });


    //关闭输入窗口，获取输入的行列数，打开表头输入窗口
    connect(m_windowInput,&InputInfo::finished,this,[=](){
        //获取行列
        m_tableRowCount = m_windowInput->rowCount();
        m_tableColCount = m_windowInput->colCount();
        m_windowInput->hide();

        //打开表头输入窗口
        m_windowInputHeader->setCol(m_tableColCount);
        m_windowInputHeader->setRow(m_tableRowCount);
        m_windowInputHeader->input();

        m_windowInputHeader->show();
    });

    //关闭行列表头输入窗口，生成表格窗口
    connect(m_windowInputHeader,&inputTableHeader::finished,this,[=](){
        m_tab->setRowCount(m_tableRowCount);
        m_tab->setColCount(m_tableColCount);
        m_tab->setRowHeader(m_windowInputHeader->rowHeader());
        m_tab->setColHeader(m_windowInputHeader->colHeader());
        m_tab->generate();

        m_windowInputHeader->hide();
        m_tab->show();
    });
}

