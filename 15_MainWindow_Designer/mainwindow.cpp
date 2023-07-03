#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //连接信号
    connect(ui->open_action,&QAction::triggered,this,[](){
        qInfo()<<"新建文件";
    });
    connect(ui->close_action,&QAction::triggered,this,[](){
        QApplication::closeAllWindows();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

