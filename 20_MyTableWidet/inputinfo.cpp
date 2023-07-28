#include "inputinfo.h"
#include "ui_inputinfo.h"
#include <QDebug>

InputInfo::InputInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputInfo)
{
    ui->setupUi(this);
    //this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    //this->setAttribute(Qt::WA_QuitOnClose,false);
    input();
}

InputInfo::~InputInfo()
{
    qInfo()<<"InputInfo->close";
    //this->close(); //delete On close
    delete ui;
}

void InputInfo::input()
{
    //输入行数和列数
    connect(ui->btnOk,&QPushButton::clicked,this,[=](){
        row = ui->editRow->text().toInt();
        col = ui->editCol->text().toInt();
        emit finished();
    });
}

int InputInfo::colCount() const
{
    return col;
}

int InputInfo::rowCount() const
{
    return row;
}

void InputInfo::closeEvent(QCloseEvent *ev)
{
}
