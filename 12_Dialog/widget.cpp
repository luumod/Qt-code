#include "widget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(640,480);
    testQColorDialog();
}

MainWindow::~MainWindow()
{
}

void MainWindow::testQMenu()
{
    QMenuBar *bar = menuBar();
    bar->addAction("模态对话框",this,&MainWindow::actionOnDialog);
    bar->addAction("半模态对话框",this,&MainWindow::actionOnHalfDialog);;
    bar->addAction("非模态对话框",this,&MainWindow::actionOnNoDialog);
}

void MainWindow::testMessage()
{
    //QMessageBox::aboutQt(this);
    //QMessageBox::about(this,"关于","<a href='https://www.pronhub.com'>异性交友网站</a>");
    //QMessageBox::critical(this,"致命错误","请重启电脑",QMessageBox::StandardButton::Cancel);

    if (QMessageBox::StandardButton::Ok == QMessageBox::information(this,"提示","请重启电脑!")){
        qInfo()<<"OK!";
    }
    else{
        qInfo()<<"NO!";
    }

}

void MainWindow::testQFileDialog()
{
    //获取当前存在的目录
    //auto Dir = QFileDialog::getExistingDirectory(this,"请选择文件","C:\\users");
    //qInfo()<<Dir;

    //获取url形式
    //auto DirUrl=QFileDialog::getExistingDirectoryUrl();
    //qInfo()<<DirUrl;

    //QString filename = QFileDialog::getOpenFileName(this,"选择文件","."
    //    ,"images (*.png *.jpg *.bmp);;Video(*.avi *.mp4 *.wav)");
    //qInfo()<<filename;

    QStringList filenames = QFileDialog::getOpenFileNames(this,"选择文件","./");
    qInfo()<<filenames;
}

void MainWindow::testFontDialog()
{
    lab=new QLabel(this);
    lab->setText("测试字体 helloylh");
    lab->setGeometry(200,200,200,200);
    auto btn=new QPushButton("选择字体",this);
    btn->setGeometry(10,50,80,30);
    connect(btn,&QPushButton::clicked,this,[=](){
        bool ok=false;
        auto font = QFontDialog::getFont(&ok,this);
        lab->setFont(font);
    });

}

void MainWindow::testQColorDialog()
{
    auto btn=new QPushButton("选择颜色",this);
    btn->setGeometry(80,50,80,30);
    connect(btn,&QPushButton::clicked,this,[=](){
        auto color=QColorDialog::getColor();
        lab->setStyleSheet(QString("color: rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue()));
    });
}

void MainWindow::actionOnDialog()
{
    //模态对话框
    QDialog dlg;
    if (!button){
        button=new QPushButton("Accepted",&dlg);
    }
    connect(button,&QPushButton::clicked,this,[&](){
        dlg.accept();
    });
    int ret = dlg.exec();//完全阻塞
    delete button;
    button=nullptr;
    if (ret==QDialog::Accepted){
        qInfo()<<"QDialog::Accepted";
    }
    else{
        qInfo()<<"QDialog::Rejected";
    }
    qInfo()<<__FUNCTION__;
}

void MainWindow::actionOnNoDialog()
{
    //非模态对话框
    QDialog* dlg=new QDialog(this);
    dlg->setSizeGripEnabled(true); //设置抓取手柄

    //添加对话框按钮组
    auto* _dbbox=new QDialogButtonBox(dlg);
    //设置系统标准按钮
    _dbbox->addButton(QDialogButtonBox::StandardButton::Ok);
    _dbbox->addButton(QDialogButtonBox::StandardButton::Yes);
    _dbbox->addButton(QDialogButtonBox::StandardButton::No);
    //设置角色
    _dbbox->addButton("选择",QDialogButtonBox::ApplyRole);

    //系统标准按钮直接具有信号
    connect(_dbbox,&QDialogButtonBox::accepted,this,[=](){
        qInfo()<<"accepted";
    });
    connect(_dbbox,&QDialogButtonBox::rejected,this,[=](){
        qInfo()<<"rejected";
    });

    //自定义的角色需要获取这个角色然后进行判断操作
    connect(_dbbox,&QDialogButtonBox::clicked,this,[=](QAbstractButton* btn){
        if (_dbbox->buttonRole(btn)==QDialogButtonBox::ApplyRole){
            dlg->accept();
            dlg->hide();
        }
    });
    dlg->show();
    qInfo()<<__FUNCTION__;
}

void MainWindow::actionOnHalfDialog()
{
    //半模态对话框
    QDialog* dlg=new QDialog(this);
    dlg->open(); //不会阻塞程序，即可以执行下面的代码
    dlg->setAttribute(Qt::WA_DeleteOnClose); //关闭隐藏
    qInfo()<<__FUNCTION__;
}

