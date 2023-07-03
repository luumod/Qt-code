#include "widget.h"
#include <QStyle>
#include <QMenu>
#include <QDebug>
#include <QCommandLinkButton>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(640,480);
    testButtonGroup();
}

Widget::~Widget()
{
}

void Widget::testPushButton()
{
    auto btn=new QPushButton(style()->standardPixmap(QStyle::SP_DialogCloseButton),"干我",this);

    auto menu=new QMenu(this);
    menu->addMenu("唱跳");
    menu->addMenu("RAP");
    menu->addMenu("篮球");

    //添加按钮菜单
    //btn->setMenu(menu);

    //设置按钮扁平化
    btn->setFlat(true);

    //设置能被选中
    btn->setCheckable(true);

    //检测是否被选中
    connect(btn,&QPushButton::toggled,this,[=](bool checked){qInfo()<<"toggled"<<checked;});

}

void Widget::testCommandLinkButton()
{
    auto btn=new QCommandLinkButton("Github",this);
    btn->setDescription("点击跳转到Github");
    connect(btn,&QCommandLinkButton::clicked,this,[](){
        qInfo()<<"正在打开!";
    });
}

void Widget::testToolButton()
{
    auto btn=new QToolButton(this);
    btn->setText("ToolButton");
    btn->setIcon(style()->standardPixmap(QStyle::SP_ComputerIcon));
    //设置文字与图标显示位置
    btn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

    //btn->setArrowType(Qt::ArrowType::RightArrow);
    auto menu=new QMenu(this);
    menu->addMenu("唱跳");
    menu->addMenu("RAP");
    menu->addMenu("篮球");
    btn->setMenu(menu);

    //设置按钮菜单弹出模式
    btn->setPopupMode(QToolButton::ToolButtonPopupMode::MenuButtonPopup);
    //设置按钮点击动态效果
    btn->setAutoRaise(true);

}

void Widget::testRadioButton()
{
    auto btn=new QRadioButton("男",this);
    auto btn2=new QRadioButton("女",this);
    btn2->move(0,50);
}

void Widget::testButtonGroup()
{
    auto btnSexGroup=new QButtonGroup(this);
    //性别组
    btnSexGroup->addButton(new QRadioButton("男",this),0);
    btnSexGroup->addButton(new QRadioButton("女",this),1);
    btnSexGroup->addButton(new QRadioButton("人妖",this),2);
    btnSexGroup->addButton(new QRadioButton("日本人",this),3);
    auto sexLists=btnSexGroup->buttons(); //获取按钮的所有按钮
    for (int i=0;i<sexLists.size();i++){
        btnSexGroup->button(i)->move(0,i*35);
    }

    //按钮组的点击
    connect(btnSexGroup,&QButtonGroup::idToggled,this,[=](int id,bool checked){
        if (!checked){
            return;
        }
        if (id==0){
            qInfo()<<btnSexGroup->button(id)->text()<<checked;
        }
        if (id==1){
            qInfo()<<btnSexGroup->button(id)->text()<<checked;
        }
        if (id==2){
            qInfo()<<btnSexGroup->button(id)->text()<<checked;
        }
        if (id==3){
            qInfo()<<btnSexGroup->button(id)->text()<<checked;
        }
    });

    //收入组
    auto btnIncomeGroup=new QButtonGroup(this);
    btnIncomeGroup->addButton(new QRadioButton("5k-1w",this),0);
    btnIncomeGroup->addButton(new QRadioButton("1w-2w",this),1);
    btnIncomeGroup->addButton(new QRadioButton("2w-5w",this),2);
    btnIncomeGroup->addButton(new QRadioButton("5w-10w",this),3);
    auto incomeLists=btnSexGroup->buttons(); //获取按钮的所有按钮
    for (int i=0;i<incomeLists.size();i++){
        btnIncomeGroup->button(i)->move(150,i*35);
    }

    //你喜欢的偶像
    auto btnYourLove=new QButtonGroup(this);
    btnYourLove->addButton(new QCheckBox("蔡徐坤",this),0);
    btnYourLove->addButton(new QCheckBox("陈立农",this),1);
    btnYourLove->addButton(new QCheckBox("范丞丞",this),2);
    btnYourLove->addButton(new QCheckBox("王源",this),3);
    btnYourLove->addButton(new QCheckBox("易烊千玺",this),4);
    auto loveLists=btnYourLove->buttons(); //获取按钮的所有按钮
    for (int i=0;i<loveLists.size();i++){
        btnYourLove->button(i)->move(300,i*35);
    }
    //多选按钮默认是排斥的
    qInfo()<<btnYourLove->exclusive(); //true
    btnYourLove->setExclusive(false); //设置不排斥
}

