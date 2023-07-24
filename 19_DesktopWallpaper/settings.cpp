#include "settings.h"
#include "ui_settings.h"
#include "toolsMod/eventfilterobject.h"
#include <QDebug>
#include <QFileDialog>


Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopWidget)
{
    ui->setupUi(this);

    this->setVisible(true);
    this->setWindowFlags(Qt::WindowType::WindowStaysOnTopHint | Qt::WindowType::FramelessWindowHint);
    this->installEventFilter(new EventFilterObject(this));

    //默认选中一张模型
    ui->confirmCbxPage3->setChecked(true);

    addButtonsToButtonGroup();

    connect(m_buttonGroup,&QButtonGroup::buttonToggled,this,[=](QAbstractButton* button,bool checked){
        if (checked){
            if (button == ui->uniformHappy){
                emit ChangeModel("blackGril.happy");
            }
            else if (button == ui->uniformNaughty){
                emit ChangeModel("blackGril.naughty");
            }
            else if (button == ui->uniformSad){
                emit ChangeModel("blackGril.sad");
            }
            else if (button == ui->uniformShy){
                emit ChangeModel("blackGril.shy");
            }
            else if (button == ui->confirmCbxPage3){
                m_buttonGroup->buttons();
                emit ChangeModel("summerGril");
            }
            else if (button == ui->confirmCbxPage4){
                emit ChangeModel("littleBoy");
            }
        }
    });
}

Settings::~Settings()
{
    delete ui;
}

void Settings::addButtonsToButtonGroup()
{
    //init
    //三个模型的切换
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);
    m_buttonGroup->addButton(ui->confirmCbxPage3,2);
    m_buttonGroup->addButton(ui->confirmCbxPage4,3);
    m_buttonGroup->addButton(ui->uniformHappy,4);
    m_buttonGroup->addButton(ui->uniformNaughty,5);
    m_buttonGroup->addButton(ui->uniformSad,6);
    m_buttonGroup->addButton(ui->uniformShy,7);

}

void Settings::on_set_clicked()
{
    ui->stackedShowArea->setCurrentIndex(0);
}


void Settings::on_model1_clicked()
{
    ui->stackedShowArea->setCurrentIndex(1);
}

void Settings::on_model2_clicked()
{
    ui->stackedShowArea->setCurrentIndex(2);
}

void Settings::on_model3_clicked()
{
    ui->stackedShowArea->setCurrentIndex(3);
}


void Settings::on_buttonClose_clicked()
{
    this->close();
}


void Settings::on_buttonChoice_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,"选择壁纸","./",QString("images (*.png *.jpg *.jpeg);; all(*.*)"));
    if (!fileName.isEmpty()){
        emit ChangeWallpeper(fileName);
    }
}

