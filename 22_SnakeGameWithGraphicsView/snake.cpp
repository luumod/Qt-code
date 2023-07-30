#include "snake.h"
#include <QTimer>
#include <QTimerEvent>
#include <chrono>
#include <QKeyEvent>
#include <qrandom.h>
#include <cmath>
#include <random>
#include <QApplication>
#include <QMessageBox>
#include <QTimer>

//辅助函数
#define randomColor() QRandomGenerator::global()->bounded(256)
int random10(int min,int max){
    /*
     *生成从【min,max】的10的倍数的随机数
     */
    std::random_device rd;
    std::mt19937 gen(rd());
    return std::ceil((std::generate_canonical<double, 10>(gen)*(max-min)+min)/10)*10;
}

Snake::Snake(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    :QGraphicsScene(x,y,width,height,parent)
{

    this->init();

    //游戏开始
    //正常移动
    timerNormalMoveStart = new QTimer(this);
    timerNormalMoveStart->callOnTimeout(this,&Snake::normalMove);
    timerNormalMoveStart->setInterval(100);
    timerNormalMoveStart->start();

    //寻路移动
    timerFindWayMoveStart = new QTimer(this);
    timerFindWayMoveStart->callOnTimeout(this,&Snake::AutoMove);
    timerFindWayMoveStart->setInterval(20);
}

Snake::~Snake()
{
    destroyedSnake();
    if (foodItem){
        delete foodItem;
        foodItem = nullptr;
    }
    qInfo()<<"destroyed";
}

void Snake::init()
{
    //QGraphicsRectItem*
    destroyedSnake();
    m_snake.push_back(this->addRect(0,0,10,10));
    m_snake.push_back(this->addRect(0,0,10,10));
    m_snake.push_back(this->addRect(0,0,10,10));

    for (int i=0;i<m_snake.size();i++){
        m_snake[i]->setPos((2-i)*10,100);
        m_snake[i]->setBrush(QColor(randomColor(),randomColor(),randomColor()));
    }
    //产生食物
    foodItem = createNode(random10(0,this->width()),random10(0,this->height()));
}

void Snake::FindWay()
{
    //A星搜索
    m_path.clear();
    if (Astar){
        delete Astar;
        Astar = nullptr;
    }
    Astar = new AStarFindWay(point(m_snake.front()->x(),m_snake.front()->y()),point(foodItem->x(),foodItem->y()));
    if (Astar->find()){
        Astar->getWay();
        Astar->getPath(m_path);
    }
}

bool Snake::snakeDied()const
{
    if (m_snake.front()->pos().x()<0 ||
        m_snake.front()->pos().y()<0 ||
        m_snake.front()->pos().x()>this->width() ||
        m_snake.front()->pos().y()>this->height() ){
        return false;
    }
    //for (auto& x:m_snake){
    //    if (m_snake.front()->collidesWithItem(x)){
    //        return false;
    //    }
    //}
    return true;
}

QGraphicsRectItem* Snake::createNode(int x,int y)
{
    auto item = new QGraphicsRectItem(0,0,10,10);
    item->setPos(x,y);
    item->setBrush(QColor(randomColor(),randomColor(),randomColor()));
    this->addItem(item); //添加到场景
    return item;
}

void Snake::checkColliders()
{
    //检测碰撞: 吃到食物
    if (m_snake.front()->collidesWithItem(foodItem,Qt::ItemSelectionMode::ContainsItemBoundingRect)){
        //蛇尾增长
        m_snake.push_back(foodItem);
        foodItem = createNode(random10(0,this->width()),random10(0,this->height()));
        if (m_isAutoFind){ //开始自动寻路选项
            FindWay();
        }

    }
}

void Snake::gameOver()
{
    //游戏结束
    if (!snakeDied()){
        auto wid = new QWidget;
        wid->deleteLater();
        QMessageBox::warning(wid,"提示","碰撞到墙了，游戏结束");
        connect(wid,&QWidget::destroyed,this,[=](){
            qApp->closeAllWindows();
        });
    }
}

void Snake::AutoMove()
{
    //后一个的位置等于前一个的位置
    if (!m_path.empty()){

        for (int i = m_snake.size()-1;i>0;--i){

            m_snake.at(i)->setPos(m_snake.at(i-1)->pos());
        }
        //头部移动
        m_snake.front()->setPos(m_path.front().first,m_path.front().second);
        m_path.pop_front();
        //吃食物
        checkColliders();
    }
    else{
        timerFindWayMoveStart->stop();
    }
}

void Snake::normalMove()
{
    //蛇移动
    //后一个的位置等于前一个的位置
    for (int i = m_snake.size()-1;i>0;--i){
        m_snake.at(i)->setPos(m_snake.at(i-1)->pos());
    }
    //头部移动
    m_snake.front()->moveBy(m_dirX,m_dirY);

    //碰撞检测
    checkColliders();

    //游戏结束
    gameOver();
}

void Snake::keyPressEvent(QKeyEvent *ev)
{
    switch (ev->key()) {
    case Qt::Key_Up:
        m_dirX = 0;
        m_dirY = -10;
        m_isAutoFind = false;
        if (!timerNormalMoveStart->isActive()){ //停止自动寻路，开始手动控制
            timerNormalMoveStart->start();
            timerFindWayMoveStart->stop();
        }
        break;
    case Qt::Key_Left:
        m_dirX = -10;
        m_dirY = 0;
        m_isAutoFind = false;
        if (!timerNormalMoveStart->isActive()){
            timerNormalMoveStart->start();
            timerFindWayMoveStart->stop();
        }
        break;
    case Qt::Key_Down:
        m_dirX = 0;
        m_dirY = 10;
        m_isAutoFind = false;
        if (!timerNormalMoveStart->isActive()){
            timerNormalMoveStart->start();
            timerFindWayMoveStart->stop();
        }
        break;
    case Qt::Key_Right:
        m_dirX = 10;
        m_dirY = 0;
        m_isAutoFind = false;
        if (!timerNormalMoveStart->isActive()){
            timerNormalMoveStart->start();
            timerFindWayMoveStart->stop();
        }
        break;
    case Qt::Key_A:
        m_isAutoFind = true;
        if (m_isAutoFind){
            timerFindWayMoveStart->start();
            timerNormalMoveStart->stop(); //停止手动移动
            FindWay();              //开始自动寻路
        }
        break;
    }
}

void Snake::destroyedSnake()
{
    for (auto& x:m_snake){
        if (x){
            delete x;
            x = nullptr;
        }
    }
}
