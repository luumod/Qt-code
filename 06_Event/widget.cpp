#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(640,480);

    //启用鼠标追踪:mousemove事件
    setMouseTracking(true);
    //设置窗口无边框
    //setWindowFlags(Qt::WindowType::FramelessWindowHint);
    //设置关闭时销毁
    setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    //设置窗口接受拖拽
    setAcceptDrops(true);

    btn=new Button("变色按钮");
    btn->show();

    edit=new LineEdit(this);
    edit->setGeometry(100,100,100,30);
    edit->setFocus();

    testEventDiffuse();
}

Widget::~Widget()
{
    btn->deleteLater();
    edit->deleteLater();
}

void Widget::closeEvent(QCloseEvent *ev)
{
    //QMessageBox::warning(this,"提示","你有未保存的操作，是否继续")   ;
    qInfo()<<__FUNCTION__;
}

void Widget::showEvent(QShowEvent *ev)
{
    qInfo()<<__FUNCTION__;
}

void Widget::moveEvent(QMoveEvent *ev)
{
    qInfo()<<__FUNCTION__<<ev->oldPos()<<ev->pos();
}

void Widget::resizeEvent(QResizeEvent *ev)
{
    qInfo()<<__FUNCTION__<<ev->oldSize()<<ev->size();
}

void Widget::enterEvent(QEnterEvent *ev)
{

}

void Widget::leaveEvent(QEvent *ev)
{

}

void Widget::mousePressEvent(QMouseEvent* ev){
    //qInfo()<<"Widget::mousePressEvent";
    if (ev->button()==Qt::MouseButton::LeftButton){
        btn->move(btn->pos()+QPoint(5,0));

        //保存第一次拖动的点
        pressPos=ev->pos();
    }
}
void Widget::mouseReleaseEvent(QMouseEvent* ev){
    if (ev->button()==Qt::MouseButton::LeftButton){
        btn->move(btn->pos()+QPoint(0,5));
    }
}
void Widget::mouseDoubleClickEvent(QMouseEvent* ev){
    //qInfo()<<ev->button();
}
void Widget::mouseMoveEvent(QMouseEvent* ev){
    //qInfo()<<"Widget::mouseMoveEvent";

    //如果有鼠标按下再移动，则无法通过ev->button获得按键
    //通过buttons获得之前已经捕获的状态
    if (ev->buttons() & Qt::MouseButton::LeftButton){
        //qInfo()<<__FUNCTION__<<ev->buttons();

        //拖动窗口
        this->move(ev->globalPosition().toPoint()-pressPos);
    }
}
void Widget::wheelEvent(QWheelEvent* ev){
    //qInfo()<<__FUNCTION__<<ev->angleDelta()<<ev->angleDelta().x(),ev->angleDelta().y();
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    //Q_UNUSED(ev);
    switch (ev->key()) {
    case Qt::Key_Up:
        btn->move(btn->pos()+QPoint(0,-1));
        break;
    case Qt::Key_Left:
        btn->move(btn->pos()+QPoint(-1,0));
        break;
    case Qt::Key_Right:
        btn->move(btn->pos()+QPoint(1,0));
        break;
    case Qt::Key_Down:
        btn->move(btn->pos()+QPoint(0,1));
        break;
    default:
        break;
    }

    //快捷键
    if (ev->matches(QKeySequence::SelectAll)){
        qInfo()<<"Ctrl + A";
    }
}

void Widget::keyReleaseEvent(QKeyEvent *ev)
{

}

void Widget::focusInEvent(QFocusEvent *ev)
{
    //焦点事件
}

void Widget::focusOutEvent(QFocusEvent *ev)
{

}

void Widget::changeEvent(QEvent *ev)
{
    //qInfo()<<__FUNCTION__;
}

void Widget::contextMenuEvent(QContextMenuEvent *ev)
{
    qInfo() << "报告长官，请求弹出上下文菜单，也就是右键菜单！"
            << "请弹出在\n"
            << "全局坐标:"<<ev->globalPos()
            << "局部坐标:"<<ev->pos() << "位置";
}

void Widget::dragEnterEvent(QDragEnterEvent *ev)
{
    //拖拽
    ev->acceptProposedAction(); //接受拖拽
    auto thing=ev->mimeData();
    //qInfo()<<thing->text();
}

void Widget::dropEvent(QDropEvent *ev)
{
    const QMimeData* thing=ev->mimeData();
    //qInfo()<<thing->text();
}

void Widget::timerEvent(QTimerEvent *ev)
{
    //处理定时器事件
    if (ev->timerId()==timeId){
        //qInfo()<<__FUNCTION__<<timeId;
    }
}

bool Widget::event(QEvent *ev)
{
    //在此来控制相应事件的处理
    switch (ev->type()) {
    case QEvent::Type::MouseButtonPress:
        qInfo()<<"Widget::event::MouseButtonPress";
        break;
    default:
        break;
    }
    return QWidget::event(ev); //事件分发
}

void Widget::customEvent(QEvent *ev)
{
    switch (ev->type()) {
    case EventType::My_Event:
    {
        auto cev=static_cast<CustomEvent*>(ev);
        cev->show();
        break;
    }
    default:
        break;
    }
}

void Widget::testEventDiffuse()
{
    //事件传播
    auto btn=new Button("事件传播",this);
    btn->setGeometry(10,10,100,30);
}


void Widget::testTimer()
{
    QTimer* time=new QTimer(this);

    //1. 方法一
    //connect(time,&QTimer::timeout,this,&Widget::onTimerHandle);
    //2. 方法二： 推荐！
    time->callOnTimeout(this,&Widget::onTimerHandle); //绑定槽函数
    time->start(1000); //每隔1s进行一次


    //只会触发一次的定时器
    QTimer::singleShot(5000,[](){qInfo()<<"我只会被调用一次!";});

    timeId = startTimer(2000); //QObject的定时器

}

void Widget::testDIYEvent()
{
    auto btn=new QPushButton("发送事件",this);
    connect(btn,&QPushButton::clicked,this,[=](){
        //1. 使用sendEvent发送事件: 栈区变量，堆区需要delete
        CustomEvent ev1(18,"于良浩");
        QApplication::sendEvent(this,&ev1);

        //2. 使用postEvent发送事件：只能是堆区变量，栈区无效
        auto ev2=new CustomEvent(20,"喜羊羊");
        QApplication::postEvent(this,ev2);
    });
}

void Widget::onTimerHandle()
{
    //qInfo()<<__FUNCTION__<<cnt++;
}


