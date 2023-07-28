#include "widget.h"
#include "ui_widget.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <QSequentialAnimationGroup> //
#include <QParallelAnimationGroup>
#include <QApplication>
#include <QScreen>
#include <QTimer>
#include <QAbstractButton>
#include <QPushButton>
#include <QLabel>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QSignalTransition>
#include <QTimeLine>
#include <QProgressBar>

class styleSheetAnimation: public QPropertyAnimation{
public:
    using QPropertyAnimation::QPropertyAnimation;
    //动画播放时每次都会更新其currentValue
    void updateCurrentValue(const QVariant &value)override{
        //获取服务对象并且设置其style
        //1.
        //qobject_cast<QWidget*>(targetObject())->setStyleSheet(QString("background-color:#%1").arg(value.toUInt(),0,16));
        //2.
        auto color = value.value<QColor>();
        qobject_cast<QWidget*>(targetObject())->setStyleSheet(QString("background-color: rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue()));
    }
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    resize(640,480);
    ui->setupUi(this);

    testMech1();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::test1()
{
    auto anima = new QPropertyAnimation(ui->btn11,"pos",this);
    //设置服务目标对象
    //anima->setTargetObject(ui->btn1);
    //设置进行操作的属性名
    //anima->setPropertyName("pos");
    anima->setStartValue(QPoint(50,50));
    anima->setKeyValueAt(0.5,QPoint(200,0)); //在[0,0.5]的时候走到（200，0）的位置然后再走到终点
    anima->setEndValue(QPoint(500,400));
    anima->setDuration(2000);

    //设置缓和曲线
    anima->setEasingCurve(QEasingCurve::Type::OutBounce);

    anima->start();


}

void Widget::test2()
{
    auto positionAnima = new QPropertyAnimation(this,"pos",this);
    auto opacityAnima = new QPropertyAnimation(this,"windowOpacity",this);
    auto styleAnima = new styleSheetAnimation(this,"",this);

    positionAnima->setStartValue(QPoint(0,0));
    auto screenSize = QApplication::primaryScreen()->size();
    positionAnima->setEndValue(QPoint(screenSize.width()-this->width(),screenSize.height()-this->height()));
    positionAnima->setDuration(2000);
    positionAnima->setEasingCurve(QEasingCurve::Type::OutBounce);

    opacityAnima->setStartValue(1);
    opacityAnima->setEndValue(0.2);
    opacityAnima->setDuration(2000);

    styleAnima->setStartValue(QColor(234,29,29));
    styleAnima->setEndValue(QColor(39,5,5));
    styleAnima->setDuration(2000);

    //串行动画
    //auto AnimaGroup = new QSequentialAnimationGroup(this);
    //并行动画
    auto AnimaGroup = new QParallelAnimationGroup(this);
    AnimaGroup->addAnimation(styleAnima);
    AnimaGroup->addAnimation(positionAnima);
    AnimaGroup->addAnimation(opacityAnima);

    AnimaGroup->start();
}

void Widget::testButtonUp()
{
    auto btn = new QPushButton(this);
    auto btn1 = new QPushButton(this);
    auto btn2 = new QPushButton(this);
    auto btn3 = new QPushButton(this);
    btn->setGeometry(this->width()/2+32,this->height()/2,32,32);
    btn1->setGeometry(btn->x()-32,-32,32,32);
    btn2->setGeometry(btn1->x()-32,-32,32,32);
    btn3->setGeometry(btn2->x()-32,-32,32,32);

    auto anima1 = new QPropertyAnimation(btn1,"pos",this);
    auto anima2 = new QPropertyAnimation(btn2,"pos",this);
    auto anima3 = new QPropertyAnimation(btn3,"pos",this);

    anima1->setStartValue(QPoint(btn1->x(),-32));
    anima1->setEndValue(QPoint(btn1->x(),this->height()/2));
    anima1->setDuration(1000);
    anima1->setEasingCurve(QEasingCurve::InOutElastic);

    anima2->setStartValue(QPoint(btn2->x(),-32));
    anima2->setEndValue(QPoint(btn2->x(),this->height()/2));
    anima2->setDuration(1000);
    anima2->setEasingCurve(QEasingCurve::InOutElastic);

    anima3->setStartValue(QPoint(btn3->x(),-32));
    anima3->setEndValue(QPoint(btn3->x(),this->height()/2));
    anima3->setDuration(1000);
    anima3->setEasingCurve(QEasingCurve::InOutElastic);

    auto group = new QSequentialAnimationGroup(this);
    group->addAnimation(anima1);
    group->addAnimation(anima2);
    group->addAnimation(anima3);

    //点击第一个按钮弹出其他的按钮
    connect(btn,&QPushButton::released,this,[=](){
        if (group->state() == QAbstractAnimation::State::Stopped &&
            group->direction() == QAbstractAnimation::Direction::Forward &&
            btn3->y() == this->height()/2){
            group->setDirection(QAbstractAnimation::Direction::Backward);
        }
        else{
            group->setDirection(QAbstractAnimation::Direction::Forward);
        }
        group->start();
    });

}

void Widget::testDrop()
{
    //窗口下坠
    auto anima = new QPropertyAnimation(this,"pos",this);
    int x = (QApplication::primaryScreen()->size().width() - this->width())/2;
    anima->setStartValue(QPoint(x,0));
    anima->setEndValue(QPoint(x,200));
    anima->setDuration(2000);
    anima->setEasingCurve(QEasingCurve::OutElastic);
    anima->start();
}

void Widget::testShake()
{
    //窗口抖动
    QPushButton* btn = new QPushButton(this);
    btn->setGeometry(this->width()-32,0,32,32);

    connect(btn,&QPushButton::released,this,[=](){
        auto anima = new QPropertyAnimation(this,"pos",this);
        anima->setStartValue(this->pos());
        anima->setKeyValueAt(0.2,this->pos() - QPoint(-3,0));
        anima->setKeyValueAt(0.4,this->pos() - QPoint(3,0));
        anima->setKeyValueAt(0.6,this->pos() - QPoint(0,-3));
        anima->setKeyValueAt(0.8,this->pos() - QPoint(0,3));
        anima->setEndValue(this->pos());
        anima->setDuration(200);
        anima->setEasingCurve(QEasingCurve::OutElastic);
        anima->setLoopCount(3); //设置循环

        anima->start();

        //播放完成后自动释放
        connect(anima,&QPropertyAnimation::finished,anima,&QPropertyAnimation::deleteLater);
    });
}


void Widget::testqobject_cast()
{
    QObject* obj = new QTimer(this);
    QTimer* timer = qobject_cast<QTimer*>(obj);
    //QPushButton* btn = qobject_cast<QPushButton*>(obj); nullptr
}

void Widget::testStateMachine()
{
    auto btn = new QPushButton("切换",this);
    btn->setGeometry(200,200,100,32);

    auto lab = new QLabel(this);
    lab->setPixmap(QPixmap(":/1.png").scaled(160,160,Qt::AspectRatioMode::KeepAspectRatio));
    lab->setScaledContents(true);

    //创建状态
    auto sta1 = new QState;
    auto sta2 = new QState;
    sta1->assignProperty(lab,"pixmap",QPixmap(":/1.png"));
    sta2->assignProperty(lab,"pixmap",QPixmap(":/2.png"));

    //添加变换
    sta1->addTransition(btn,&QPushButton::clicked,sta2);
    sta2->addTransition(btn,&QPushButton::clicked,sta1);

    //创建状态机
    auto machs = new QStateMachine(this);
    //添加状态
    machs->addState(sta1);
    machs->addState(sta2);
    machs->setInitialState(sta1); //设置默认状态
    machs->start();

}

void Widget::testStateMachineExample()
{
    /*
     * 状态机 + 动画
     */

    //按钮在四个位置上移动
    auto btn = new QPushButton(this);

    //父状态
    auto tops = new QState;
    auto btms = new QState;

    auto finalState = new QFinalState;

    //子状态
    auto st1 = new QState(tops);
    auto st2 = new QState(tops);

    auto sb1 = new QState(btms);
    auto sb2 = new QState(btms);

    st1->assignProperty(btn,"pos",QPoint(0,0));
    st2->assignProperty(btn,"pos",QPoint(this->width() - btn->width(),0));

    sb1->assignProperty(btn,"pos",QPoint(0,this->height()-btn->height()));
    sb2->assignProperty(btn,"pos",QPoint(this->width()-btn->width(),this->height()-btn->height()));

    //设置变换 并且添加动画
    auto st1_Anima = new QPropertyAnimation(btn,"pos",this);
    st1_Anima->setEasingCurve(QEasingCurve::OutElastic);
    st1_Anima->setDuration(1000);
    st1->addTransition(btn,&QPushButton::clicked,st2)->addAnimation(st1_Anima);

    auto st2_Anima = new QPropertyAnimation(btn,"pos",this);
    st2_Anima->setEasingCurve(QEasingCurve::OutBounce);
    st2_Anima->setDuration(2000);
    st2->addTransition(btn,&QPushButton::clicked,btms)->addAnimation(st2_Anima);

    auto st3_Anima = new QPropertyAnimation(btn,"pos",this);
    st3_Anima->setEasingCurve(QEasingCurve::OutElastic);
    st3_Anima->setDuration(1000);
    sb1->addTransition(btn,&QPushButton::clicked,sb2)->addAnimation(st3_Anima);
    sb2->addTransition(btn,&QPushButton::clicked,finalState);

    tops->setInitialState(st1);
    btms->setInitialState(sb1);

    //创建状态机
    auto sm = new QStateMachine(this);
    sm->addState(tops);
    sm->addState(btms);
    sm->addState(finalState);
    sm->setInitialState(tops);
    sm->start();

    connect(finalState,&QFinalState::entered,this,[=](){
        sm->stop();
        qInfo()<<"finished";
    });

}

void Widget::testMech1()
{
    auto playBtn = new QPushButton("播放",this);
    //设置 状态
    QState *playState = new QState;
    playState->assignProperty(playBtn,"text","播放");

    QState *pauseState = new QState;
    pauseState->assignProperty(playBtn,"text","暂停");

    QState *stopState = new QState;
    stopState->assignProperty(playBtn,"text","停止");

    //给状态添加转换 点击播放按钮切换到暂停状态
    playState->addTransition(playBtn,&QPushButton::clicked,pauseState);
    pauseState->addTransition(playBtn,&QPushButton::clicked,stopState);
    stopState->addTransition(playBtn,&QPushButton::clicked,playState);


    //创建状态机并添加状态
    QStateMachine *stateMachine = new QStateMachine(this);
    stateMachine->addState(playState);
    stateMachine->addState(pauseState);
    stateMachine->addState(stopState);

    //设置初始状态
    stateMachine->setInitialState(playState);

    //启动状态机
    stateMachine->start();
}

void Widget::testTimeLine()
{
    auto timeLine = new QTimeLine(2000,this);
    timeLine->setFrameRange(0,100);
    timeLine->setEasingCurve(QEasingCurve::OutCurve);

    auto gBar = new QProgressBar(this);

    connect(timeLine,&QTimeLine::frameChanged,gBar,&QProgressBar::setValue);
    connect(timeLine,&QTimeLine::valueChanged,this,[](qreal value){
        qInfo()<<value;
    });

    timeLine->setLoopCount(0); //无限循环：0
    timeLine->start();
}

