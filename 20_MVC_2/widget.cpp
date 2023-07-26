#include "widget.h"
#include <QGridLayout>
#include <qrandom.h>
#include <QDebug>
#include <QHeaderView>

Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
    resize(640,480);
    testW2();
}

Widget::~Widget()
{
}

void Widget::init()
{
    m_tableView = new QTableView(this);
    m_treeView = new QTreeView(this);
    m_listView = new QListView(this);
    QGridLayout* m_layout = new QGridLayout(this);
    m_layout->addWidget(m_tableView,0,0);
    m_layout->addWidget(m_treeView,0,1);
    m_layout->addWidget(m_listView,1,0);

    m_itemModel = new QStandardItemModel(this);

    m_tableView->setModel(m_itemModel);
    m_treeView->setModel(m_itemModel);
    m_listView->setModel(m_itemModel);
}

void Widget::test1()
{
    //添加行
    //一行只有一列
    m_itemModel->appendRow(new QStandardItem("蔡徐坤"));
    //一行里面有多列 tree table
    QList<QStandardItem*> ls;
    for (int i=0;i<5;i++){
        ls.push_back(new QStandardItem(QString::number(QRandomGenerator::global()->bounded(1000,100000))));
    }
    m_itemModel->appendRow(ls);

    //添加列: 在最后一列追加
    m_itemModel->appendColumn(QList<QStandardItem*>()<<new QStandardItem("老虎")<<new QStandardItem("母鸡"));

    //添加水平头
    m_itemModel->setHorizontalHeaderItem(0,new QStandardItem("名字"));
    m_itemModel->setVerticalHeaderLabels(QStringList()<<"one"<<"two"<<"three");
    m_itemModel->setItem(2,0,new QStandardItem("范丞丞 "));
}

void Widget::test2()
{
    QStandardItem* pItem = new QStandardItem("20_MVC_2[master]");
    pItem->appendRow(new QStandardItem("CMakeLists.txt"));

    QStandardItem* pItemFilesMain = new QStandardItem("20_MVC_2");

    QStandardItem* subHeader = new QStandardItem("Header Files");
    auto File = new QStandardItem("widget.h");
    File->setIcon(style()->standardPixmap(QStyle::StandardPixmap::SP_FileIcon));
    subHeader->appendRow(File);

    QStandardItem* subSource = new QStandardItem("Source Files");
    File = new QStandardItem("main.cpp");
    File->setIcon(style()->standardPixmap(QStyle::StandardPixmap::SP_FileIcon));
    subSource->appendRow(File);
    File = new QStandardItem("widget.cpp");
    File->setIcon(style()->standardPixmap(QStyle::StandardPixmap::SP_FileIcon));
    subSource->appendRow(File);
    pItemFilesMain->appendRow(subHeader);
    pItemFilesMain->appendRow(subSource);

    pItem->appendRow(pItemFilesMain);
    pItem->appendRow(new QStandardItem("CMake Modules"));

    //设置可以选中
    pItem->setCheckable(true);
    m_itemModel->appendRow(pItem);

}

void Widget::initW()
{
    m_treeWidget = new QTreeWidget;

}

void Widget::testW1()
{
    m_listWidget = new QListWidget(this);
    this->setCentralWidget(m_listWidget);
    //添加项目
    m_listWidget->addItem("蔡徐坤");
    m_listWidget->addItem("陈立农");
    m_listWidget->addItem("范丞丞");
    //m_listWidget->addItems();
}

void Widget::testW2()
{
    m_tableWidget = new QTableWidget(this);
    this->setCentralWidget(m_tableWidget);
    m_tableWidget->setRowCount(10);
    m_tableWidget->setColumnCount(10);
    for (int i=0;i<m_tableWidget->rowCount();i++){
        for (int j=0;j<m_tableWidget->columnCount();j++){
            m_tableWidget->setItem(i,j,new QTableWidgetItem(QString("%1 %2").arg(i).arg(j)));
        }
    }
    //删除某一行
    //m_tableWidget->removeRow(1);
    m_tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("标题"));
    m_tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);

    connect(m_tableWidget,&QTableWidget::itemPressed,this,[=](QTableWidgetItem* item){
        qInfo()<<item->text();
    });
}

