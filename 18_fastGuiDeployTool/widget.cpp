#include "widget.h"
#include <QBoxLayout>
#include <QFormLayout>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMimeData>
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(640,480);
    initUi();

    this->setAcceptDrops(true);

    this->setWindowTitle("windeployqt简易窗口版");
}

Widget::~Widget()
{
}

void Widget::initUi()
{
    //变量的创建
    //设置窗口固定
    this->setFixedSize(640,480);
    m_qtVersionCbx = new QComboBox(this);
    m_qtCompilerCbx = new QComboBox(this);
    m_qtVersionCbx->setObjectName("qtInfoCbx");
    m_qtCompilerCbx->setObjectName("qtInfoCbx");


    m_exeFileBtn = new QPushButton("点击或拖拽exe到此处",this);
    //设置尺寸规则：允许自由拖拽扩展其大小
    m_exeFileBtn->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);
    //设置对象的名字
    m_exeFileBtn->setObjectName("exeFileBtn");

    m_generateBtn = new QPushButton("生成",this);
    m_testBtn = new QPushButton("测试",this);
    m_aboutBtn = new QPushButton("点击查看使用说明",this);
    m_generateBtn->setObjectName("resBtn");
    m_testBtn->setObjectName("resBtn");
    m_aboutBtn->setObjectName("resBtn");

    //表单布局
    QFormLayout* formlayout = new QFormLayout;
    //addRow：标签 + 控件
    formlayout->addRow("选择Qt版本",m_qtVersionCbx);
    formlayout->addRow("选择编译套件",m_qtCompilerCbx);

    QHBoxLayout* hlayout =new QHBoxLayout;
    hlayout->addWidget(m_testBtn);
    hlayout->addWidget(m_aboutBtn);

    QVBoxLayout* vlayout =new QVBoxLayout(this);
    vlayout->addLayout(formlayout);
    vlayout->addWidget(m_exeFileBtn);
    vlayout->addWidget(m_generateBtn);
    vlayout->addLayout(hlayout);

    //vlayout->setContentsMargins(5,5,5,5);
    vlayout->setSpacing(20);

    //加载qss
    QFile qssFile(":/resource/qss/style.css");
    if (qssFile.open(QFile::OpenModeFlag::ReadOnly)){
        this->setStyleSheet(qssFile.readAll());
    }

    //点击打开文件管理器
    connect(m_exeFileBtn,&QPushButton::clicked,this,&Widget::onOpenFile);

    connect(m_qtVersionCbx,&QComboBox::currentTextChanged,this,[=](){
        //切换Qt版本时切换编译套件
        m_qtCompilerCbx->clear(); //首先清除所有Item
        //确定Qt版本号
        m_qtEnv.setQtVersion(m_qtVersionCbx->currentData().toString());
        //获取编译套件
        m_qtCompilerCbx->addItems(m_qtEnv.QtCompilerList());
    });
    //Qt的编译套件更新：自动获取当前QString，然后设置对应的编译套件
    connect(m_qtCompilerCbx,&QComboBox::currentTextChanged,&m_qtEnv,&findQtEnv::setQtCompiler);

    //点击生成
    connect(m_generateBtn,&QPushButton::clicked,&m_qtEnv,&findQtEnv::generate);

    //生成完成
    connect(&m_qtEnv,&findQtEnv::generateFinished,this,[=](){
        QMessageBox::information(this,"提示","已完成所需库的加载！请点击测试查看是否成功");
    });

    //点击测试
    connect(m_testBtn,&QPushButton::clicked,&m_qtEnv,&findQtEnv::test);

    //测试是否成功
    connect(&m_qtEnv,&findQtEnv::testFinished,this,[=](bool ok){
        qInfo()<<ok;
        if (!ok){
            QMessageBox::warning(this,"警告","测试失败，请检查编译套件是否正确，或者检查是否为exe文件");
        }
    });

    //点击关于
    connect(m_aboutBtn,&QPushButton::clicked,this,[=](){

        QMessageBox::about(this,"使用说明","使用方法： \n 1. 拖拽一个需要加载所需库的exe文件 \n 2. 点击生成，会在原exe路径下自动加载所需要的库文件 \n 3. 点击测试来检查是否加载成功 \n\n 注意：本软件会自动查找设备上的Qt程序及对应编译组件，在使用时务必保证Qt版本和编译套件与exe适配！");
    });

    //添加数据
    auto temp =m_qtEnv.QtVersionList(); //返回Qt版本列表
    for (const auto& x:temp){ //x: QString
        m_qtVersionCbx->addItem("Qt " + x,x); //添加一个Qt前缀
    }
}

void Widget::onOpenFile()
{
    //获取文件路径，包括文件名字
    auto filename = QFileDialog::getOpenFileName(
        this,"请选择exe文件","./","exe (*.exe);; all(*.*)");
    if (!filename.isEmpty()){
        //如果是可执行文件: QFile有一系列的 是否是... 的操作
        if (QFileInfo(filename).isExecutable()){
            //获取文件名字
            m_exeFileBtn->setText(QFileInfo(filename).fileName());
            m_qtEnv.setExeFilePath(filename);
        }
        else{
            QMessageBox::warning(this,"警告","请打开exe文件");
        }
    }
}

void Widget::dragEnterEvent(QDragEnterEvent* ev){
    ev->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent* ev){
    auto thing = ev->mimeData();
    if (thing->hasUrls()){
        for (auto& x:thing->urls()){
            QString path = x.url(QUrl::PreferLocalFile); //获取url地址
            if (QFileInfo(path).isExecutable()){
                //获取第一个exe程序
                m_exeFileBtn->setText(QFileInfo(path).fileName()); //设置文本
                m_qtEnv.setExeFilePath(path); //保存exe可执行文件路径
                break;
            }
        }
    }
}

