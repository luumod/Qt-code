#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("圆形图片转换器");
    resize(280,260);

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
    if (Handle()){
        QMessageBox::information(this,"操作成功！","已经在原文件路径下生成!");
    }
    else {
        QMessageBox::warning(this,"错误","生成失败，请检查图片格式是否正确！");
    }
}

bool Widget::Handle()
{
    mask=QBitmap(":/mask.jpg");
    //加载Pixmap图片...
    pix=QPixmap(filename).scaled(mask.size());
    if (pix.isNull()){
        return false;
    }
    pix.setMask(mask);

    QString preStr=filename.mid(0,filename.lastIndexOf("."));
    preStr+="_Circle.png";
    pix.save(preStr);
    return true;
}

void Widget::DrawText(QPainter* painter)
{
    painter->setFont(QFont("微软雅黑",28,QFont::Bold,true));
    painter->drawText(10,height()/2,"拖拽图片到此处");
}
