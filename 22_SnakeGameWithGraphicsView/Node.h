#ifndef NODE_H
#define NODE_H

#include "Point.h"
#include <vector>

class Node{
public:
    Node(const point& pos):m_currentPoint(pos),m_fatherPoint(nullptr){}
    ~Node(){
        m_fatherPoint = nullptr;
        for (auto& x:m_child){
            x = nullptr;
        }
    }
    point& currentPoint(){
        return m_currentPoint;
    }
    Node*& fatherNode(){
        return m_fatherPoint;
    }
    std::vector<Node*> childPoints()const{
        return m_child;
    }
private:
    point m_currentPoint;
    Node* m_fatherPoint = nullptr;
    std::vector<Node*> m_child;
};
#endif // NODE_H
