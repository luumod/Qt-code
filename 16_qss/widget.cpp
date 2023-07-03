#include "widget.h"
#include "./ui_widget.h"
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //直接写
    //this->setStyleSheet("QPushButton{ color: red;}");

    //外部加载
    QFile qssFile(":/images/qss/qt.css");
    if (qssFile.open(QFile::OpenModeFlag::ReadOnly)){
        this->setStyleSheet(qssFile.readAll());
    }
}

Widget::~Widget()
{
    delete ui;
}

