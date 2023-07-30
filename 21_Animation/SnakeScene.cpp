#include "SnakeScene.h"
#include <QTimerEvent>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <qrandom.h>
#define random() QRandomGenerator::global()->bounded(999999)
#define randonPos() QPointF(random() %  (static_cast<int>(width())/10) *10, random() % (static_cast<int>(height())/10)*10)
SnakeScene::SnakeScene(qreal x, qreal y, qreal width, qreal height, QObject* parent)
	:QGraphicsScene(x,y,width,height,parent)
{
	init();
	//启动定时器
	gameTimerId = startTimer(100);
}

SnakeScene::~SnakeScene()
{
	killTimer(gameTimerId);
}

void SnakeScene::init()
{
	//往场景中添加三个蛇身体,后面的矩形是内部矩形
	nodes << addRect(0, 0, 10, 10);	//蛇头	
	nodes << addRect(0, 0, 10, 10);
	nodes << addRect(0, 0, 10, 10);
	//设置在场景上面的坐标
	for (int i =0;i < nodes.size() ;i++)
	{
		nodes[i]->setPos((2 - i) * 10, 0);
	}
	//创建食物
	foodItem = createNode(randonPos());

	//分数
	scoreItem = addSimpleText("分数:0");
	scoreItem->setPos(0, 0);
}

void SnakeScene::autoMove()
{
	//让身体跟着蛇头走
	for (int i = nodes.size() - 1; i > 0; --i)
	{
		nodes[i]->setPos(nodes[i - 1]->pos());
	}

	//蛇头移动
	nodes[0]->moveBy(dirX,dirY);

	//判断是否迟到了食物
	if (nodes[0]->collidesWithItem(foodItem,Qt::ItemSelectionMode::ContainsItemBoundingRect))
	{
		nodes << createNode(QPointF( - 10, -10));
		foodItem->setPos(randonPos());
		score += 10;
		scoreItem->setText(QString("分数：%1").arg(score));
	}
}

auto SnakeScene::createNode(const QPointF& pos) -> QGraphicsRectItem*
{
	auto item = new QGraphicsRectItem(0, 0, 10, 10);
	item->setPos(pos);
	item->setBrush(QColor(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)));
	addItem(item);
	return item;
}

void SnakeScene::timerEvent(QTimerEvent* ev)
{
	if (ev->timerId() == gameTimerId)
	{
		autoMove();

	}
}

void SnakeScene::keyPressEvent(QKeyEvent* ev)
{
	switch (ev->key())
	{
	case Qt::Key::Key_Up:
		dirX = 0;
		dirY = -10;
		break;
	case Qt::Key::Key_Down:
		dirX = 0;
		dirY = 10;
		break;
	case Qt::Key::Key_Left:
		dirX = -10;
		dirY = 0;
		break;
	case Qt::Key::Key_Right:
		dirX = 10;
		dirY = 0;
		break;
	default:
		break;
	}
}
