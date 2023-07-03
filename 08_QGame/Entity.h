#ifndef ENTITY_H
#define ENTITY_H

#include <QPainter>

//游戏实体抽象类
class Entity{
public:
    Entity(){}
    virtual ~Entity(){}
public:
    virtual void update()=0;
    virtual void draw(QPainter* painter)=0;

    bool active()const{return isActive;}
    void Destory(){isActive=false;}

    int type()const{return E_type;}
    void setType(int type){E_type=type;}
private:
    bool isActive=true;
    int E_type; //类型
};

#endif // ENTITY_H
