#include "Manager.h"
#include <QDebug>
#include "GlobalDefinition.h"

Manager *Manager::getInstance()
{
    static Manager* mgr=nullptr;
    if (!mgr){
        mgr=new Manager();
    }
    return mgr;
}

void Manager::draw(QPainter* painter)
{
    foreach (auto x, set) {
        x->draw(painter);
    }
}

void Manager::update()
{
    Mgr->refersh(); //销毁对象
    foreach (auto x, set) {
        x->update();
    }
}

void Manager::refersh()
{
    set.removeIf([](Entity* e){
        if (!e->active()){
            delete e;    //销毁对象
            e=nullptr;
            return true; //删除对象
        }
        return false;
    });
}

