#include "mouse.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsItem>

static constexpr int MouseCount = 10;

//! [0]
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    //创建场景
    QGraphicsScene scene;
    scene.setSceneRect(-300,-300, 600, 600);
    /*
     * 对于静态场景可以使用索引加速
     * 对于动态场景会拖慢速度
     */
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    //! [3]
    for (int i = 0; i < MouseCount; ++i) {
        Mouse *mouse = new Mouse;
        //产生的位置
        auto x = ::sin((i * 6.28) / MouseCount) * 200;
        auto y = ::cos((i * 6.28) / MouseCount) * 200;
        mouse->setPos(x,y);
        scene.addItem(mouse);
    }
    //! [3]

    // 创建视图并且设置场景
    QGraphicsView view(&scene);
    //设置渲染： 抗锯齿
    view.setRenderHint(QPainter::Antialiasing);
    //设置背景色
    view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    //后台缓存背景
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //设置推拽
    view.setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));
    view.resize(400, 300);
    //显示视图
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);

    return app.exec();
}
