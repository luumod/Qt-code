#include "widget.h"

//生成随机数
#define random(min,max) QRandomGenerator::global()->bounded((min),(max))

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(640,480);

    //设置计时器 使图片旋转
    QTimer* img_time=new QTimer(this);
    img_time->callOnTimeout(this,QOverload<>::of(&Widget::update));
    img_time->setInterval(5);
    img_time->start();

    //图片处理
    ProcessPicture();

    s1=new Sprite(0,0,200,200,QPixmap(":/img.bmp"));
    s2=new Sprite(300,300,200,200,QPixmap(":/touxiang.png"));
}

Widget::~Widget()
{
    delete s1;
    delete s2;
}

void Widget::testdraw1()
{
    //1. 创建画家对象，栈区
    //QPainter painter;
    ////2. 指定画家的绘图设备
    //painter.begin(this);
//
    //painter.drawLine(0,0,width(),height());
    //painter.drawLine(0,0,100,100);
//
    ////end. 画家结束绘制
    //painter.end();

    //推荐的方式：
    QPainter painter(this);
    painter.drawLine(0,0,width(),height());


}

void Widget::testPen(QPainter *painter)
{
    //设置画笔
    //单独的设置：
    //painter->setPen(Qt::PenStyle::DashLine);
    //painter->setPen(Qt::red);

    //单独设置Pen
    Qt::PenCapStyle s[]={
        Qt::PenCapStyle::FlatCap,
        Qt::PenCapStyle::RoundCap,
        Qt::PenCapStyle::SquareCap};
    for (int i=0;i<=6;i++){
        QPen pen(Qt::red,5,Qt::PenStyle(i),s[i%3]);
        painter->setPen(pen);
        painter->drawLine(10+i*50,0,200+50*i,200);
    }
    // joinstyle 多边形的边框拐角设置
}

void Widget::testBrush(QPainter *painter)
{
    //painter->setBrush(Qt::BrushStyle::Dense1Pattern);
    //painter->drawRect(10,10,100,100);

    QBrush brush;
    brush.setColor(QColor(random(0,256),random(0,256),random(0,256)));
    painter->setBrush(brush); //设置画家的画刷

    const int W=50,H=50;
    for (int i=0;i<6;i++){
        for (int j=0;j<3;j++){
            brush.setStyle(Qt::BrushStyle(i*3+j));
            painter->setBrush(brush);
            painter->drawRect(j*W,i*H,W,H);
        }
    }
}

void Widget::testBrush2(QPainter *painter)
{
    const int L=100;
    painter->setBrush(QBrush(Qt::GlobalColor::blue));
    painter->drawRect(0,0,L,L);

    painter->setBrush(QBrush(QPixmap(":/touxiang.png").scaled(100,100)));
    painter->drawRect(L,0,L,L);
}

void Widget::testLinearGradient(QPainter *painter)
{
    //线性渐变
    QLinearGradient gradient( 0,0,200,200);

    //默认是灰色，自己设置渐变颜色
    //gradient.setColorAt(0.3,qRgb(127,194,65));
    //gradient.setColorAt(0.7,qRgb(107,211,220));

    gradient.setColorAt(0,0xfbc2eb);
    gradient.setColorAt(1,0xa6c1ee);

    //设置渐变规则
    //gradient.setSpread(QGradient::Spread::ReflectSpread);
    gradient.setSpread(QGradient::Spread::RepeatSpread);

    painter->setBrush(gradient);
    painter->drawEllipse(0,0,200,200);

    painter->drawRect(200,200,width()-200,height()-200);
}

void Widget::testRadialGradient(QPainter *painter)
{
    //镜像渐变
    QRadialGradient gradient(100,100,100);

    //默认是灰色，自己设置渐变颜色
    gradient.setColorAt(0,0xfbc2eb);
    gradient.setColorAt(1,0xa6c1ee);

    painter->setBrush(gradient);
    painter->drawEllipse(0,0,200,200);
}

void Widget::testConicalGradient(QPainter *painter)
{
    //锥形渐变
    QConicalGradient gradient(QPoint(200,200),0);
    gradient.setColorAt(0,Qt::green);
    gradient.setColorAt(0.5,Qt::red);
    gradient.setColorAt(1,Qt::yellow);

    painter->setBrush(gradient);
    painter->drawEllipse(QPoint(200,200),100,100);
}

void Widget::testGradientMode(QPainter *painter)
{
    //设置渐变模式
    QLinearGradient gradient;

    gradient.setColorAt(0,0x84fab0);
    gradient.setColorAt(1,0x8fd3f4);

    //无须指定渐变的起点与终点，对每一个 draw对象都执行相同的渐变
    gradient.setCoordinateMode(QGradient::ObjectMode);

    painter->setBrush(gradient);
    painter->drawEllipse(0,0,200,200);
    painter->drawEllipse(200,0,200,200);
    painter->drawEllipse(400,0,200,200);
}

void Widget::testTransform(QPainter *painter)
{
    painter->save(); //保存

    //错切
    qreal sh=0.2,sv=0.5;
    painter->shear(sh,sv);

    painter->drawPixmap(0,0,QPixmap(":/touxiang.png").scaled(250,250));
    //平移坐标系
    painter->restore(); //返回状态


    //坐标系缩放
    painter->save();
    painter->translate(250,250);
    painter->scale(0.5,0.5);
    //旋转
    static qreal Delta=0;
    //默认使以Z轴旋转
    painter->rotate(Delta++);
    //沿X轴旋转
    QTransform trans;
    trans.rotate(Delta++,Qt::Axis::YAxis);
    //painter->setTransform(trans); //返回到painter

    painter->drawPixmap(0,0,QPixmap(":/touxiang.png").scaled(250,250));
    painter->restore();


}

void Widget::testDraw(QPainter* painter)
{
    //painter->setPen(Qt::red);
    //painter->drawPoint(50,50);
//
    //QPolygon ploy;
    //for (int i=0;i<100;i++){
    //    ploy.append(QPoint(i,i));
    //}
    //painter->drawPoints(ploy);
//
    ////绘制线段
    //QList<QLine> lines{{0,0,100,100},{100,100,0,200}};
    //painter->drawLines(lines);
//
    ////圆角矩形
    //painter->drawRoundedRect(QRect(100,100,100,100),50,50,Qt::SizeMode::RelativeSize);
//
    //painter->fillRect(QRect(100,0,80,80),QGradient::Preset::BigMango); //填充矩形
//
    ////绘制弧: 注意弧度是 1/16度，要乘以16
    //painter->drawArc(QRect(200,10,100,100),45*16,135*16);
    ////绘制弦
    //painter->drawChord(QRect(200,10,100,100),-45*16,90*16);
    //painter->drawPie(QRect(200,10,100,100),180*16,135*16);
    //

    painter->setBrush(Qt::GlobalColor::blue);
    QPolygon pol1{{0,200},{150,0},{300,200},{0,0},{300,0},{150,200}};
    painter->drawPolygon(pol1,Qt::FillRule::WindingFill);
}

void Widget::testPainterPath(QPainter *painter)
{
    //painter->setBrush(Qt::GlobalColor::blue);

    QPainterPath path;
    //path.addRect(0,0,200,200);
    //path.addRect(100,100,200,200);

    //设置填充方式: 默认是奇偶填充
    //path.setFillRule(Qt::FillRule::WindingFill); ///缠绕填充
    path.setFillRule(Qt::FillRule::OddEvenFill);//奇偶填充

    //painter->drawPath(path);

    //path.lineTo(300,300); //默认是 (0,0)点
    //path.lineTo(300,0);
    //path.lineTo(0,300);
    //painter->drawPath(path);

    //绘制二次贝塞尔曲线
    //path.moveTo(0,100);
    //path.quadTo(QPoint(150,200),QPoint(300,100));
    //painter->drawPath(path);

    //三次贝塞尔曲线
    path.moveTo(0,0);
    path.cubicTo(QPoint(100,200),QPoint(150,450),QPoint(90,90));
    painter->drawPath(path);

}

void Widget::testDrawText(QPainter *painter)
{
    painter->setPen(Qt::red);
    painter->setFont(QFont(QFont("微软雅黑",30,QFont::Bold,true)));
    painter->drawText(QPoint(10,50),"你好，我是于良浩");
}

void Widget::testDrawImage(QPainter *painter)
{
    //painter->drawPixmap(0,0,QPixmap(":/touxiang.png"));
    //painter->drawPixmap(QRect(0,0,300,300),QPixmap(":/touxiang.png"));

    //圆形图片制作
    mask=QBitmap(":/mask.jpg");
    QPixmap pic=QPixmap(":/t.jpg").scaled(mask.size());
    pic.setMask(mask);
    //if (pic.save("./")){
    //    qInfo()<<"保存成功";
    //}
    //else{
    //    qInfo()<<"保存失败";
    //}
    painter->drawPixmap(0,0,pic);
}

void Widget::testImage(QPainter* painter)
{
    //QPixmap: 针对输出显示优化的
    //QImage: 专门进行图片处理的
    //QPicture: Qt独有的图形格式

    painter->drawPixmap(0,0,QPixmap("F:\\code\\qt\\08_QGame\\images\\bg5.jpg"));
    painter->drawPixmap(0,0,QPixmap("F:\\code\\qt\\08_QGame\\images1 - 副本\\enemy2_trans.png"));

}

void Widget::ProcessPicture()
{
    //构造时处理图片

    //处理图片信息

    //mask=QBitmap(":/mask.jpg");
    pix=QPixmap(":/boom1.png");
    mask=pix.createMaskFromColor(Qt::GlobalColor::white, Qt::MaskInColor);
    pix.setMask(mask);
    mask.save("bitmask.png"); //保存图片
}

void Widget::testDrawGlyphRun(QPainter *painter)
{
    painter->setBrush(Qt::GlobalColor::green);
    painter->drawRect(0,0,100,100);
}

void Widget::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing); //抗锯齿
    testImage(&painter);

    //s1->draw(&painter);
    //s2->draw(&painter);
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key()){
    case Qt::Key_Up:
        s2->move(0,-3);
        break;
    case Qt::Key_Left:
        s2->move(-3,0);
        break;
    case Qt::Key_Right:
        s2->move(3,0);
        break;
    case Qt::Key_Down:
        s2->move(0,3);
        break;
    }
    qInfo()<<s1->collider.boundingRect()<<s2->collider.boundingRect();
    if (s1->collider.intersects(s2->collider)){
        s2->setActive(false);
    }

    update(); //更新绘制
    s1->update(); //更新
    s2->update();
}

