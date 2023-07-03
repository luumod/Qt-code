#ifndef MANAGER_H
#define MANAGER_H

#include "Entity.h"
#include <QSet>
#include <QPainter>
#include "GlobalDefinition.h"

#define Mgr Manager::getInstance()
class Manager
{
public:
    static Manager* getInstance();
public:
    template <typename T>
    T* addEntity(T* e){
        set.insert(e);
        return e;
    }

    void draw(QPainter* painter);
    void update();
    int count()const{
        return set.size();
    }
    void refersh();

    //获取类型
    template<typename T>
    QSet<T *> getQSetType(Entity_type type)
    {
        QSet<T*> s;
        for (auto& x:set){
            if (x->type()==type){
                s.insert(static_cast<T*>(x));
            }
        }
        return s;
    }

private:
    QSet<Entity*> set;
    Manager(){}
};

#endif // MANAGER_H
