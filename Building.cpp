#include "Building.h"

Building::Building(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{

//    1----(4)----4
//    |           |
//   (1)         (3)
//    |           |
//    2----(2)----3

    Wall wall1(x1,y1,x2,y2,0.0,0.0,0.0,0),wall2(x2,y2,x3,y3,0.0,0.0,0.0,0),wall3(x3,y3,x4,y4,0.0,0.0,0.0,0),wall4(x4,y4,x1,y1,0.0,0.0,0.0,0);
}

Building::Building(const QPointF &p1,const QPointF &p2)
{
    const QPointF &dp = p2-p1;
    //Wall wall1(p1,p1+dp.y(),0.0,0.0,0.0,0),wall2((p1+dp.y()),p2,0.0,0.0,0.0,0),wall3(p2,p1+dp.x(),0.0,0.0,0.0,0),wall4(p1+dp.x(),p1,0.0,0.0,0.0,0);

}
