#ifndef ASTARFINDWAY_H
#define ASTARFINDWAY_H

#include <QObject>
#include "Node.h"
#include <QDebug>

const int ROW = 10;
const int COL = 10;
const int ZXDJ = 10;	//直线代价
const int XXDJ = 14;	//斜线代价
enum Dir { p_up, p_down, p_left, p_right, p_lup, p_ldown, p_rup, p_rdown };

#define DEBUG false

//单例寻路
class AStarFindWay:public QObject
{
    Q_OBJECT
public:
    AStarFindWay(const point& begPos,const point& endPos)
        :m_begPos(begPos),m_endPos(endPos),m_pRoot(new Node(begPos)),
        m_currentNode(m_pRoot),m_isFind(false){
        memset(vis,false,sizeof(vis));
    }
    void getPath(std::list<std::pair<int,int>>& res){
        res.swap(m_path);
        emit findFinished(); // 发送完成搜索信号
    }
    ~AStarFindWay(){
        m_path.clear();
        for (auto& x:buff){
            if (x){
                delete x;
                x = nullptr;
            }
        }
    }
    bool find(){
        while (true)
        {
            //1. 某个点八个方向依次遍历 计算g代价
            for (int i = 0; i < 8; ++i)
            {
                //确定试探点的属性
                m_seerPoint = new Node(m_currentNode->currentPoint());
                //八个方向进行试探！
                switch (i)
                {
                    //直线代价
                case p_up://上
                    m_seerPoint->currentPoint().m_row-=1;
                    m_seerPoint->currentPoint().m_g += ZXDJ;
                    break;
                case p_down://下
                    m_seerPoint->currentPoint().m_row+=1;
                    m_seerPoint->currentPoint().m_g += ZXDJ;
                    break;
                case p_left://左
                    m_seerPoint->currentPoint().m_col-=1;
                    m_seerPoint->currentPoint().m_g += ZXDJ;
                    break;
                case p_right://右
                    m_seerPoint->currentPoint().m_col+=1;
                    m_seerPoint->currentPoint().m_g += ZXDJ;
                    break;
                    //斜线代价
                case p_lup://左上
                    m_seerPoint->currentPoint().m_row-=1;
                    m_seerPoint->currentPoint().m_col-=1;
                    m_seerPoint->currentPoint().m_g += XXDJ;
                    break;
                case p_ldown://左下
                    m_seerPoint->currentPoint().m_row+=1;
                    m_seerPoint->currentPoint().m_col-=1;
                    m_seerPoint->currentPoint().m_g += XXDJ;
                    break;
                case p_rup://右上
                    m_seerPoint->currentPoint().m_row-=1;
                    m_seerPoint->currentPoint().m_col+=1;
                    m_seerPoint->currentPoint().m_g += XXDJ;
                    break;
                case p_rdown://右下
                    m_seerPoint->currentPoint().m_row+=1;
                    m_seerPoint->currentPoint().m_col+=1;
                    m_seerPoint->currentPoint().m_g += XXDJ;
                    break;
                }
                //判断他们能不能走，能走的计算h及f 入树  存储在buff数组
                if (m_seerPoint->currentPoint().canWalk() &&
                    !vis[m_seerPoint->currentPoint().m_row][m_seerPoint->currentPoint().m_col] &&
                    true /*不能碰到蛇的身体*/)
                {	//能走
                    //计算代价
                    m_seerPoint->currentPoint().GetH(m_seerPoint->currentPoint(), m_endPos);//计算h代价
                    m_seerPoint->currentPoint().GetF();//得到最后的f代价，f=g+h
                    //把能走的这个点存入树中
                    m_currentNode->childPoints().push_back(m_seerPoint);//pTemp表示的就是下一个能走的点
                    m_seerPoint->fatherNode() = m_currentNode;//父子关系确定
                    //存入数组
                    buff.push_back(m_seerPoint);
                    //标记这个点走过
                    vis[m_seerPoint->currentPoint().m_row][m_seerPoint->currentPoint().m_col] = true;
                }
                else
                {
                    //不能走则删除pTemp，继续遍历下一个方向的点
                    delete m_seerPoint;
                    m_seerPoint = nullptr;
                }
            }
            /*
        遍历完八个方向后，找到最小代价点，并且移动，然后删除
        */
            auto itMin =  min_element(buff.begin(), buff.end(), [&](Node* p1,Node* p2)
                                     {
                                         return p1->currentPoint().m_f < p2->currentPoint().m_f;
                                     });

            //当前点移动到这个最小代价点
            m_currentNode = *itMin;
            buff.erase(itMin);

            //有没有到达终点
            if (m_currentNode->currentPoint() == m_endPos)
            {
                m_isFind = true;
                return true;
            }
            //没有终点，自然一直删除节点，则buff为空
            if (buff.size() == 0)
            {
                assert("没有终点!!!");
                return false;
            }
        }
        return false;
    }
    void getWay(){
#if DEBUG
        qInfo()<<"有无到达终点:"<<m_isFind;
#endif
        if (m_isFind)
        {
            while (m_currentNode)
            {
                m_path.push_back({m_currentNode->currentPoint().m_row*10,m_currentNode->currentPoint().m_col*10});
                m_currentNode = m_currentNode->fatherNode();
            }
#if DEBUG //打印路径
            qInfo()<<"完成！";
#endif
            std::reverse(m_path.begin(),m_path.end());
#if DEBUG //打印路径
            for (auto&x :m_path){
                qInfo()<<x;
            }
#endif
        }
    }
    bool vis[70][60]{false};
signals:
    void findFinished();
private:
    point m_begPos;
    point m_endPos;
    Node* m_pRoot = nullptr;
    std::vector<Node*> buff;
    Node* m_currentNode = nullptr;
    Node* m_seerPoint = nullptr;
    bool m_isFind = false;


    std::list<std::pair<int,int>> m_path;
};

#endif // ASTARFINDWAY_H
