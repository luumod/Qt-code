#include "scheckbox.h"
#include "ui_scheckbox.h"

SCheckBox::SCheckBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCheckBox)
{
    ui->setupUi(this);
}

SCheckBox::~SCheckBox()
{
    delete ui;
}

void SCheckBox::mousePressEvent(QMouseEvent *ev)
{
    if (!cut){
        ui->label->setStyleSheet("image: url(:/check_off.png)");
    }
    else{
        ui->label->setStyleSheet("image: url(:/check_on.png)");
    }
    cut = !cut;
}
