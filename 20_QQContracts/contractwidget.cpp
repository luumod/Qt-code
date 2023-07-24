#include "contractwidget.h"
#include "contractinfo.h"
#include <QLabel>
#include <QGridLayout>
#include <QBoxLayout>

ContractWidget::ContractWidget(QWidget* parent)
    :ContractWidget(nullptr,parent)
{
}

ContractWidget::ContractWidget(ContractInfo *info,QWidget* parent)
    :m_info(info),QWidget(parent)
{
    init();
}

ContractWidget::~ContractWidget()
{

}

void ContractWidget::init()
{
    QLabel* userName = new QLabel(m_info->m_name,this);

    QLabel* userPixmap = new QLabel(this);
    userPixmap->setPixmap(m_info->m_picture);
    userPixmap->setScaledContents(true);
    userPixmap->setFixedSize(42,42);

    QLabel* userSignature = new QLabel(m_info->m_signature,this);

    QLabel* userType = new QLabel(this);
    if (m_info->m_type == ContractInfo::no){
        userType->hide();
    }
    else if (m_info->m_type == ContractInfo::vip){
        userType->setPixmap(QPixmap(":/assets/images/vip.png"));
    }
    else if (m_info->m_type == ContractInfo::svip){
        userType->setPixmap(QPixmap(":/assets/images/svip.png"));
    }

    QHBoxLayout* hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(userName);
    hBoxLayout->addWidget(userType);
    hBoxLayout->addStretch(1);
    hBoxLayout->setSpacing(5);

    QGridLayout* MainGridLayout = new QGridLayout(this);
    MainGridLayout->addWidget(userPixmap,0,0,2,1);
    MainGridLayout->addLayout(hBoxLayout,0,1);
    MainGridLayout->addWidget(userSignature,1,1);
    MainGridLayout->setColumnStretch(2,1);
    MainGridLayout->setSpacing(1);
    //设置某一列的最小宽度
    MainGridLayout->setColumnMinimumWidth(0,50);
}
