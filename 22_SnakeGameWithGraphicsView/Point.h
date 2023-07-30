#ifndef POINT_H
#define POINT_H

#include <cmath>

class point{
public:
    point(const point& pos){
        m_row = pos.m_row;
        m_col = pos.m_col;
    }
    ~point(){

    }
    point(int x,int y):m_row(x/10),m_col(y/10){
    }
    void operator=(const point& pos){
        m_row = pos.m_row;
        m_col = pos.m_col;
    }
    bool operator==(const point& pos)
    {
        return (pos.m_row == m_row && pos.m_col == m_col);
    }
    void GetH(const point& Begpos, const point& Endpos)
    {
        int x = abs(Begpos.m_col - Endpos.m_col)*10;//计算水平差距
        int y = abs(Begpos.m_row - Endpos.m_row)*10;//计算垂直差距
        m_h = x + y;//计算总的差距
    }
    inline void GetF()
    {
        m_f = m_g + m_h;//计算f
    }
    bool canWalk(int xMin=0,int xMax=70,int yMin=0,int yMax=60){
        //判断当前点能不能走
        if (m_row<xMin || m_row>=xMax || m_col<yMin || m_col>=yMax){
            return false;
        }
        return true;
    }
    int m_row;
    int m_col;
    int m_f = 0;
    int m_g = 0;
    int m_h = 0;
};

#endif // POINT_H
