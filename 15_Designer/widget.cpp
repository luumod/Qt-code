#include "widget.h"
#include "./ui_widget.h"
#include <QPushButton>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    auto file = QFileDialog::getOpenFileName(this,"打开文件");
    qInfo()<<file;
}

