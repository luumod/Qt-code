#include "widget.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsItem>
#include <QDebug>


class YTriangleItem: public QAbstractGraphicsShapeItem{
public:
    using QAbstractGraphicsShapeItem::QAbstractGraphicsShapeItem;
    YTriangleItem(qreal x,qreal y,qreal w,qreal h,QGraphicsItem* item = nullptr)
        :m_w(w),m_h(h),QAbstractGraphicsShapeItem(item){
        setPos(x,y);
    }
    YTriangleItem(QRectF rect,QGraphicsItem* item = nullptr)
        :YTriangleItem(rect.x(),rect.y(),rect.width(),rect.height(),item){}
    QRectF boundingRect() const override{
        return QRectF(-0.5,-0.5,m_w,m_h);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)override{
        painter->save();
        painter->setPen(pen());
        painter->setBrush(brush());

        QPolygonF triangle;
        triangle<<QPointF(m_w/2,0)<<QPointF(0,m_h)<<QPointF(m_w,m_h);
        painter->drawPolygon(triangle);
    }
private:
    qreal m_w,m_h;
};

class Test{
public:
    Test(){}
    void test1(){
        //创建场景
        m_view1 = new QGraphicsView;
        m_scene = new QGraphicsScene(QRect(0,0,640,480),m_view1);
        //创建视图,将场景添加到视图上
        m_view1->setScene(m_scene);

        //显示视图
        m_view1->show();

        //m_view1->setBackgroundBrush(QColor(0,255,255));
        //m_view1->setBackgroundBrush(QBrush(QPixmap(":/dog.png")));

        ////设置前景色 加透明度
        //m_view1->setForegroundBrush(QColor(128,128,128,100));

        //对场景设置，则所有设置该场景的视图都会改变
        m_scene->setBackgroundBrush(QColor(0,255,255));
        m_scene->setBackgroundBrush(QBrush(QPixmap(":/dog.png")));
        m_scene->setForegroundBrush(QColor(128,128,128,100));

        //给场景添加图元 item
        //m_scene->addEllipse(QRect(0,0,50,50),QPen(Qt::GlobalColor::darkRed));
        //m_scene->addLine(QLine(0,0,100,100),QPen(Qt::GlobalColor::darkCyan));
        //QPolygon triggler;
        //triggler<<QPoint(m_scene->width()/2,0)<<QPoint(m_scene->width(),m_scene->height())<<QPoint(0,m_scene->height());
        //m_scene->addPolygon(triggler,QPen(Qt::GlobalColor::green,5,Qt::PenStyle::DashLine));
        //m_scene->addPixmap(QPixmap(":/dog.png").scaled(150,150,Qt::KeepAspectRatio));
        //m_scene->addSimpleText(QString("我是大帅哥"));
        //auto btn = new QPushButton("按钮");
        //m_scene->addWidget(btn);

        //添加标准图元
        //SimpleTextItem
        auto sText = new QGraphicsSimpleTextItem("天王盖地虎");
        sText->setBrush(Qt::GlobalColor::blue);
        sText->setFont(QFont("楷体",20,3,true));
        sText->setPos(QPoint(100,100));
        m_scene->addItem(sText);

        //TextItem
        auto sText2 = m_scene->addText(QString("宝塔镇河妖"));
        sText2->setFont(QFont("楷体",20,3,true));
        sText2->setPos(QPoint(sText->x()+150,100));
        sText2->setDefaultTextColor(Qt::GlobalColor::blue);


        //做对比
        m_scene->addRect(QRect(0,0,100,100))->setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable | QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);

        //自定义图元
        YTriangleItem* triangleItem = new YTriangleItem(0,0,50,50);
        triangleItem->setPen(QPen(Qt::GlobalColor::red));
        triangleItem->setBrush(QColor(Qt::blue));
        triangleItem->setPos(200,100);
        //允许拖拽此图元
        triangleItem->setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable | QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
        m_scene->addItem(triangleItem);
        qInfo()<<triangleItem<<triangleItem->boundingRect();

        //启动橡皮筋选择
        m_view1->setDragMode(QGraphicsView::DragMode::RubberBandDrag);
    }
private:
    QGraphicsView* m_view1;
    QGraphicsView* m_view2;
    QGraphicsScene* m_scene;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Test t;
    t.test1();

    return a.exec();
}
