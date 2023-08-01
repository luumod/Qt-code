#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsItem>
#include <QDebug>
#include <QObject>
#include <QLabel>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QToolButton>

class YTriangleItem: public QAbstractGraphicsShapeItem{
public:
    using QAbstractGraphicsShapeItem::QAbstractGraphicsShapeItem;
    YTriangleItem(qreal w,qreal h,QGraphicsItem* item = nullptr)
        :m_w(w),m_h(h),QAbstractGraphicsShapeItem(item){

        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
    }
    QRectF boundingRect() const override{
        qreal width = 1;
        //包围矩形
        return QRectF(-m_w/2 - width/2,-m_h/2-width/2,m_w + width,m_h + width);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)override{
        painter->save();
        painter->setPen(pen());
        painter->setBrush(brush());

        QPolygonF polygon;
        polygon<<QPointF(0,-m_h/2)<<QPointF(m_w/2,m_h/2)<<QPointF(-m_w/2,m_h/2)<<QPointF(0,-m_h/2);
        painter->drawPolygon(polygon); //闭合
    }
private:
    qreal m_w,m_h;
};

class CircleItem: public QAbstractGraphicsShapeItem{
public:
    CircleItem(qreal radius,QGraphicsItem* item = nullptr)
        :radius(radius),QAbstractGraphicsShapeItem(item){
        diameter = 2*radius;
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
    }
    QRectF boundingRect()const override{
        qreal width = 1;
        return QRectF(-radius-width/2,-radius-width/2,diameter+width,diameter+width);
    }
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* wodget=nullptr)override{
        painter->save();
        painter->setPen(pen());
        painter->setBrush(brush());

        painter->drawEllipse(-radius,-radius,diameter,diameter);
    }
private:
    qreal radius,diameter;
};

class Scene :public QGraphicsScene{
public:
    Scene(QRect rect,QObject* parent = nullptr){
        this->setSceneRect(rect);
    }
    Scene(QObject* parent = nullptr){}
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev)override{
    }
};

class View :public QGraphicsView{
    Q_OBJECT
public:
    View(QGraphicsScene* scene,QWidget* parent = nullptr)
         :QGraphicsView(parent){
         this->setScene(scene);
        btn = new QToolButton();
        //connect()
        this->scene()->addWidget(btn); //映射到场景坐标
        btn->setCheckable(true);
        btn->setChecked(false);
        btn->setGeometry(10,10,50,50);
        btn->setIcon(QIcon(":/dog.png"));
        btn->setIconSize(QSize(50,50));
    }
    View(QWidget* parent = nullptr):QGraphicsView(parent){}
public slots:
    void zoomIn() { scale(1.2, 1.2); }
    void zoomOut() { scale(1 / 1.2, 1 / 1.2); }
    void rotateLeft() { rotate(-10); }
    void rotateRight() { rotate(10); }
protected:
    void mousePressEvent(QMouseEvent *ev)override{
        QPoint pos = ev->pos();
        //视图坐标转换为场景坐标
        QPointF scene_pos = this->mapToScene(pos);
        qInfo()<<"视图坐标: "<<pos<<"场景坐标: "<<scene_pos<<"全局坐标: "<<this->mapToGlobal(pos);
        QGraphicsItem * item = this->scene()->itemAt(scene_pos.toPoint(),QTransform());
        if (!item){
            return;
        }

        QPointF itemScenePos = item->scenePos();
        QPoint itemViewPos = this->mapFromScene(itemScenePos);
        qInfo()<< "项目在View中的位置: "<< itemViewPos;


        QPainterPath path;
        path.addEllipse(QRectF(ev->pos(),QSizeF(20,20)));
        auto scenePath = this->mapToScene(path);
        auto itemList = this->scene()->items(scenePath);
        qInfo()<<itemList.size();

    }
private:
    QToolButton* btn;
};

class Test:public QGraphicsScene{
    Q_OBJECT
public:
    Test(){}
    void test1(){
        //创建场景
        m_view1 = new View;
        m_scene = new Scene(QRect(0,0,640,480),m_view1);
        //为视图指定场景
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
//
        ////添加标准图元
        ////SimpleTextItem
        //auto sText = new QGraphicsSimpleTextItem("天王盖地虎");
        //sText->setBrush(Qt::GlobalColor::blue);
        //sText->setFont(QFont("楷体",20,3,true));
        //sText->setPos(QPoint(100,100));
        //m_scene->addItem(sText);
//
        ////TextItem
        //auto sText2 = m_scene->addText(QString("宝塔镇河妖"));
        //sText2->setFont(QFont("楷体",20,3,true));
        //sText2->setPos(QPoint(sText->x()+150,100));
        //sText2->setDefaultTextColor(Qt::GlobalColor::blue);
//
//
        ////做对比
        //m_scene->addRect(QRect(0,0,100,100))->setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable | QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
//
        ////自定义图元
        //YTriangleItem* triangleItem = new YTriangleItem(0,0,50,50);
        //triangleItem->setPen(QPen(Qt::GlobalColor::red));
        //triangleItem->setBrush(QColor(Qt::blue));
        //triangleItem->setPos(200,100);
        ////允许拖拽此图元
        //triangleItem->setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable | QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
        //m_scene->addItem(triangleItem);
        //qInfo()<<triangleItem<<triangleItem->boundingRect();
//
        ////启动橡皮筋选择
        //m_view1->setDragMode(QGraphicsView::DragMode::RubberBandDrag);
    }
    void test2(){
        m_scene = new Scene(QRect(0,0,640,480));
        m_view1 = new View(m_scene);

        m_view1->show();

        QPolygonF polygon;
        //画一个正菱形
        polygon << QPointF(-100, 0) << QPointF(0, 100)
                  << QPointF(100, 0) << QPointF(0, -100)
                  << QPointF(-100, 0);

        m_scene->addPolygon(polygon);


        //画一个正方形
        polygon.clear();
        polygon << QPointF(-100, -100) << QPointF(100, -100)
                << QPointF(100, 100) << QPointF(-100, 100)
                << QPointF(-100, -100);

        m_scene->addPolygon(polygon);

        //画一个梯形
        polygon.clear();
        polygon << QPointF(-120, -80) << QPointF(-70, 80)
                  << QPointF(120, 80) << QPointF(70, -80)
                  << QPointF(-120, -80);

        m_scene->addPolygon(polygon);


        //画一个圆角矩阵
        QPainterPath path;
        path.moveTo(200, 50);
        path.arcTo(150, 0, 50, 50, 0, 90);
        path.arcTo(50, 0, 50, 50, 90, 90);
        path.arcTo(50, 50, 50, 50, 180, 90);
        path.arcTo(150, 50, 50, 50, 270, 90);
        path.lineTo(200, 25);
        polygon = path.toFillPolygon();

        m_scene->addPolygon(polygon);


        auto btn = new QPushButton("按钮");
        m_scene->addWidget(btn);


        connect(btn,&QPushButton::clicked,this,&Test::onButtonClicked);

        auto item = new QGraphicsLineItem(QLineF(0,0,200,200));
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        m_scene->addItem(item);


        polygon.clear();
        polygon<<QPointF(300,300)<<QPointF(400,400)<<QPointF(300,350);
        QGraphicsPolygonItem* pItem = new QGraphicsPolygonItem;
        pItem->setPolygon(polygon); //设置

        m_scene->addItem(pItem);

        QPixmap pixmap(500, 800);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        QPixmap image(":/images/textpointer.png");//加载图片
        // Draw icon centred horizontally on button.
        QRect target(4, 0, 42, 43);
        QRect source(0, 0, 42, 43);
        painter.fillRect(QRect(0, 60, 50, 80), Qt::red);
        painter.drawPixmap(target, image, source);

        pixmap.save("./aa.png");


    }
    void test3(){
        m_scene = new Scene;
        m_view1 = new View(m_scene);

        //窗口中间的坐标是（0，0）
        m_scene->setSceneRect(QRect(-320,-240,640,480));
        qInfo()<<m_scene->sceneRect();


        auto circle = new CircleItem(100);
        circle->setPos(0,0);
        qInfo()<<circle->boundingRect()<<circle->scenePos()<<circle->sceneBoundingRect()<<circle->shape();
        auto rect = new YTriangleItem(100,100);
        rect->setPos(-100,-100);

        m_scene->addItem(circle);
        m_scene->addItem(rect);


        m_view1->show();
    }
public slots:
    void onButtonClicked(){
        qInfo()<<"触发";
        QGraphicsItem* selectItem = m_scene->selectedItems().first();
        selectItem->collidingItems();
    }
public:
    void paintEvent(QPaintEvent* painterrr){

    }
private:
    View* m_view1;
    QGraphicsView* m_view2;
    Scene* m_scene;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Test t;
    t.test3();

    return a.exec();
}


#include "main.moc"

