#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("透明图与掩码图制作");
    resize(300,260);

    setAcceptDrops(true); //Widget接受拖拽

    update();
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent* ev){

    QPainter painter(this);
    DrawText(&painter);

}

void Widget::dragEnterEvent(QDragEnterEvent *ev)
{
    ev->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent *ev)
{
    auto thing=ev->mimeData();
    filename=thing->text();
    filename.remove(0,8);
    if (HandleToMask()){
        QMessageBox::information(this,"操作成功！","已经在原文件路径下生成掩码图和透明图!");
    }
    else {
        QMessageBox::warning(this,"错误","生成失败，请检查图片格式是否正确！");
    }
}

bool Widget::HandleToMask()
{
    //加载Pixmap图片...
    pix=QPixmap(filename);
    translate=QPixmap(filename);
    if (pix.isNull()){
        return false;
    }
    //注意：背景需要是白色的图
    //mask=pix.createMaskFromColor(Qt::GlobalColor::white,Qt::MaskInColor);
    mask=pix.createHeuristicMask(true);

    translate.setMask(mask);

    QString preStrMask=filename.mid(0,filename.lastIndexOf("."));
    QString preStrTrans=filename.mid(0,filename.lastIndexOf("."));
    preStrMask+="_mask.png";
    preStrTrans+="_trans.png";
    mask.save(preStrMask);
    translate.save(preStrTrans);
    return true;
}

void Widget::DrawText(QPainter* painter)
{
    painter->setFont(QFont("微软雅黑",28,QFont::Bold,true));
    painter->drawText(10,height()/2,"拖拽图片到此处");
}
