#include "Game.h"
#include "Playerplane.h"
#include "Manager.h"  //对象管理器
#include "GlobalDefinition.h"
#include "Animation.h"

PlayerPlane* player; //测试
Game::Game(QWidget* parent)
    :QWidget(parent)
{
    QTimer* time=new QTimer(this);
    time->callOnTimeout(this,[=](){
        //更新
        updateGame();
        update();
    });
    time->start(1000/60);

    key_time=new QTimer(this);
    key_time->callOnTimeout(this,&Game::slotOnKeyPress);

    fire_time=new QTimer(this);
    fire_time->callOnTimeout(this,&Game::slotOnBulletFire);
    fire_time->start(200);

    enemy_time=new QTimer(this);
    enemy_time->callOnTimeout(this,&Game::slotOnEnemyAppear);
    enemy_time->start(400);

    exit_time=new QTimer(this);
    exit_time->callOnTimeout(this,&Game::slotOnMyDied);
    exit_time->start(10);

    enemy=new EnemyPlane();

    map=new Map(":/background/bk2.jpg");
    player=Mgr->addEntity(new PlayerPlane(width()/2,height()/2,":/images1/plane1_trans.png",9));
    player->setType(Entity_type::ET_PLAYER);

    Animation* player_died_Anima = player->addAnimation("myplane_Died",new Animation(120));
    player_died_Anima->addFrame(QPixmap(":/common/boom1_trans.png"));
    player_died_Anima->addFrame(QPixmap(":/common/boom2_trans.png"));
    player_died_Anima->addFrame(QPixmap(":/common/boom3_trans.png"));
    player_died_Anima->addFrame(QPixmap(":/common/boom4_trans.png"));
    player_died_Anima->addFrame(QPixmap(":/common/boom5_trans.png"));
    player_died_Anima->addFrame(QPixmap(":/common/boom6_trans.png"));
}

Game::~Game()
{

}

void Game::run()
{
    this->show();
}

void Game::initGame(int w,int h,const QString& title){
    setFixedSize(w,h);
    setWindowTitle(title);
    Game::HEIGHT=h; //地图大小
    Game::WIDTH=w;
}

void Game::clearGame()
{
    delete map;
    delete Mgr;
    delete enemy;
}

void Game::updateGame()
{
    map->update();
    Mgr->update();


    if (player->getPosition().x()+player->getPixmap().width()/2<0){ //左
        player->getPosition().setX(-player->getPixmap().width()/2);
    }
    if (player->getPosition().x()+player->getPixmap().width()/2>Game::WIDTH){ //右
        player->getPosition().setX(Game::WIDTH-player->getPixmap().width()/2);
    }
    if (player->getPosition().y()<0){ //上
        player->getPosition().setY(0);
    }
    if (player->getPosition().y()+player->getPixmap().height()/2>Game::HEIGHT){
        player->getPosition().setY(Game::HEIGHT-player->getPixmap().height()/2);
    }

    //攻击敌机
    player->AttackEnemy();

    qInfo()<<Mgr->count();
}

void Game::drawGame(QPainter *painter)
{
    map->draw(painter);
    Mgr->draw(painter);
}

void Game::slotOnKeyPress()
{
    foreach (int key, keys) {
        if (key==Qt::Key_Up){
            player->getVelocity().setY(-1);
        }
        if (key==Qt::Key_Down){
            player->getVelocity().setY(1);
        }
        if (key==Qt::Key_Left){
            player->getVelocity().setX(-1);
        }
        if (key==Qt::Key_Right){
            player->getVelocity().setX(1);
        }
    }
}

void Game::slotOnBulletFire()
{
    //子弹发射
    player->fire();
}

void Game::slotOnEnemyAppear()
{
    //敌机出现
    enemy->appear();
}

void Game::slotOnMyDied()
{
    //我方死亡
    if (!player->active()){
        close();
    }
}


//-------------事件处理--------------------

void Game::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    drawGame(&painter);
}

void Game::closeEvent(QCloseEvent *ev)
{
    clearGame();
    exit(0);
}

void Game::keyPressEvent(QKeyEvent *ev)
{
    if (!ev->isAutoRepeat()){
        keys.append(ev->key());
    }
    if (!key_time->isActive()){
        key_time->start(1000/60);
    }
}

void Game::keyReleaseEvent(QKeyEvent *ev)
{
    if (!ev->isAutoRepeat()){
        keys.removeAll(ev->key());
    }
    if (keys.isEmpty()){
        key_time->stop();
    }
    int key=ev->key();
    if (key==Qt::Key_Up){
        player->getVelocity().setY(0);
    }
    if (key==Qt::Key_Down){
        player->getVelocity().setY(0);
    }
    if (key==Qt::Key_Left){
        player->getVelocity().setX(0);
    }
    if (key==Qt::Key_Right){
        player->getVelocity().setX(0);
    }
}

