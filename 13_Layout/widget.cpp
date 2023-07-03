#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    testQTabWidget();
}

void Widget::testQBoxLayout()
{
    //创建控件
    QLabel* lab = new QLabel("请输入账号",this);
    QLineEdit* edit = new QLineEdit(this);

    //创建布局
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
    //设置不同的方向
    //layout->setDirection(QBoxLayout::Direction::Up);

    //布局中添加控件
    layout->addWidget(lab);
    layout->addWidget(edit);

    //将布局添加到窗口
    //this->setLayout(layout);
}

void Widget::testNestLayout()
{
    auto lab1 = new QLabel("username",this);
    auto edit1 = new QLineEdit(this);
    auto lab2 = new QLabel("password",this);
    auto edit2 = new QLineEdit(this);

    //创建水平的布局，但是不指定父对象，最后再添加一个最终的布局
    QHBoxLayout* layout1= new QHBoxLayout();
    QHBoxLayout* layout2= new QHBoxLayout();

    layout1->addWidget(lab1);
    layout1->addWidget(edit1);

    layout2->addWidget(lab2);
    layout2->addWidget(edit2);

    //设置一个最终的布局，然后添加this
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addLayout(layout2);
}

void Widget::testButton()
{
    QPushButton* btn1 = new QPushButton("btn1",this);
    QPushButton* btn2 = new QPushButton("btn2",this);
    QPushButton* btn3 = new QPushButton("btn3",this);
    QPushButton* btn4 = new QPushButton("btn4",this);
    QPushButton* btn5 = new QPushButton("btn5",this);

    //创建布局
    QHBoxLayout* hlayout =new QHBoxLayout(this);
    hlayout->addWidget(btn1);
    //设置按钮之间的拉伸空间
    hlayout->addStretch(1);
    hlayout->addWidget(btn2); //按钮内的拉伸方式
    hlayout->addStretch(2);

    hlayout->addWidget(btn3);
    hlayout->addStretch(3);

    hlayout->addWidget(btn4,4);
    hlayout->addStretch(4);

    hlayout->addWidget(btn5);

    //设置边距
    hlayout->setContentsMargins(10,10,10,10);

    //设置按钮之间的间距
    hlayout->setSpacing(10);

    //设置拉伸因子
    //hlayout->setStretchFactor(btn1,2,this);

    //获取布局内的元素(包括拉伸因子控件)
    auto wgs = hlayout->itemAt(0);
    auto w_btn1 = static_cast<QPushButton*>(wgs->widget());
    qInfo()<<w_btn1->text()<<hlayout->count();
}

void Widget::testGridLayout()
{
    //图标
    auto Icon = new QLabel(this);
    auto accountEdit = new QLineEdit(this);
    auto btn1 = new QPushButton("注册账号",this);
    auto passwdEdit = new QLineEdit(this);
    auto btn2 = new QPushButton("找回密码",this);
    auto cbx1 = new QCheckBox("记住密码",this);
    auto cbx2 = new QCheckBox("自动登录",this);
    auto loginbtn = new QPushButton("登录",this);

    accountEdit->setPlaceholderText("QQ号码/手机/邮箱");
    passwdEdit->setPlaceholderText("密码");

    Icon->setPixmap(QPixmap(":/C++.jpg").scaled(90,90));  //添加图标
    //创建Grid布局并应用
    auto glayout = new QGridLayout(this);

    //默认是垂直的，需要自己设置相对位置：
    glayout->addWidget(Icon,0,0,2,2);//(0,0)的位置开始，占据两行两列
    glayout->addWidget(accountEdit,0,2,1,2);
    glayout->addWidget(btn1,0,4,1,1);
    glayout->addWidget(passwdEdit,1,2,1,2);
    glayout->addWidget(btn2,1,4,1,1);
    glayout->addWidget(cbx1,2,2,1,1);
    glayout->addWidget(cbx2,2,3,1,1);
    glayout->addWidget(loginbtn,3,2,1,2);

    //设置尺寸限制
    //glayout->setSizeConstraint(QGridLayout::SetFixedSize); //固定大小
    //glayout->setSizeConstraint(QGridLayout::SetMaximumSize); //尺寸: [无穷小,最大值]

    //设置布局
    //设置间距
}

void Widget::testQFormLayout()
{
    auto edit1 =new QLineEdit(this);
    auto edit2 =new QLineEdit(this);
    auto btn = new QPushButton("贯穿一整行",this);
    //表单布局
    QFormLayout* flayout = new QFormLayout(this);
    //一行一行的添加
    flayout->addRow("username",edit1); //自动添加标签，标签对应的后面的控件
    flayout->addRow("password",edit2);

    //为某个控件设置跨越一行
    flayout->setWidget(2,QFormLayout::SpanningRole,btn);

    //设置换行策略
    //1. 为所有都添加换行
    flayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::WrapAllRows);
    //2. 按照长度换行
    //flayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::WrapLongRows);
}

void Widget::testQStackedLayout()
{
    QLabel* lab1 = new QLabel("你好",this);
    QLabel* lab2 = new QLabel("我是",this);
    QLabel* lab3 = new QLabel("大帅哥",this);

    lab1->setStyleSheet("background-color: red");
    lab2->setStyleSheet("background-color: blue");
    lab3->setStyleSheet("background-color: green");

    //堆栈布局
    QStackedLayout* slayout = new QStackedLayout(this);
    slayout->addWidget(lab1);   //0
    slayout->addWidget(lab2);   //1
    slayout->addWidget(lab3);   //2

    //切换界面
    auto cutBtn = new QPushButton("点击切换界面",this);
    connect(cutBtn,&QPushButton::clicked,this,[=](){
        //切换当前显示索引
        slayout->setCurrentIndex((slayout->currentIndex()+1)%slayout->count());
        //提升控件的显示等级到堆栈最顶端
        cutBtn->raise();
    });
}

void Widget::testQSplitter()
{
    auto text1 = new QTextEdit(this);
    auto text2 = new QTextEdit(this);

    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(text1);
    splitter->addWidget(text2);
    //添加预览：false
    splitter->setOpaqueResize(true);
}

void Widget::testQStackedWidget()
{
    QLabel* lab1 = new QLabel("你好",this);
    QLabel* lab2 = new QLabel("我是",this);
    QLabel* lab3 = new QLabel("大帅哥",this);
    lab1->setStyleSheet("background-color: red");
    lab2->setStyleSheet("background-color: blue");
    lab3->setStyleSheet("background-color: green");

    QStackedWidget* sWidget = new QStackedWidget(this);
    sWidget->addWidget(lab1);
    sWidget->addWidget(lab2);
    sWidget->addWidget(lab3);

    QHBoxLayout* box_layout = new QHBoxLayout(this);
    box_layout->addWidget(sWidget);

    auto btn = new QPushButton("点击切换界面");
    connect(btn,&QPushButton::clicked,this,[=](){
        sWidget->setCurrentIndex((sWidget->currentIndex()+1)%sWidget->count());
    });
    btn->show();
}

void Widget::testQTabWidget()
{
    resize(640,480);
    QTextEdit* text1 = new QTextEdit(this);
    QTextEdit* text2 = new QTextEdit(this);
    QTextEdit* text3 = new QTextEdit(this);
    text1->setStyleSheet("background-color: red");
    text2->setStyleSheet("background-color: blue");
    text3->setStyleSheet("background-color: green");

    QTabWidget* tWidget = new QTabWidget(this);
    tWidget->addTab(text1,"test1.txt");
    tWidget->addTab(text2,"test2.txt");
    tWidget->addTab(text3,"test3.txt");

    tWidget->setTabsClosable(true); //可以关闭
    connect(tWidget,&QTabWidget::tabCloseRequested,this,[=](int index){
        tWidget->removeTab(index);
    });

}

Widget::~Widget()
{
}

