#include "inputtableheader.h"
#include "ui_inputtableheader.h"
#include <QDebug>

inputTableHeader::inputTableHeader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inputTableHeader)
{
    ui->setupUi(this);
    //this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    //this->setAttribute(Qt::WA_QuitOnClose,false);
}

inputTableHeader::~inputTableHeader()
{
    qInfo()<<"inputHeader->close()";
    //this->close();  //delete On close
    delete ui;
}

void inputTableHeader::setRow(int num)
{
    m_rowCount = num;
}

void inputTableHeader::setCol(int num)
{
    m_colCount = num;
}

void inputTableHeader::input()
{
    ui->Coledit->setPlaceholderText(QString("请输入%1个col列表头，空格作为间隔").arg(m_colCount));
    ui->Rowedit->setPlaceholderText(QString("请输入%1个row行表头，空格作为间隔").arg(m_rowCount));

    connect(ui->btnGenerate,&QPushButton::clicked,this,[=](){
        m_rowHeader = ui->Rowedit->text().split(" ");
        m_colHeader = ui->Coledit->text().split(" ");

        emit finished(); //发送完成信号
    });
}

QStringList inputTableHeader::rowHeader() const
{
    return m_rowHeader;
}

QStringList inputTableHeader::colHeader() const
{
    return m_colHeader;
}
