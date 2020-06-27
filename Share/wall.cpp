#include "wall.h"

Wall::Wall(double x01, double y01, double x02, double y02, double thickness, double relEps, double sig, int listInd):
    Line(x01, y01, x02, y02),thick(thickness),epsilon(relEps),sigma(sig),indWall(listInd)

  /*
   * inherits from Line, basic line function to be called when interacting with rays
   */

{

}

Wall::Wall(const QPointF &p1, const QPointF &p2, double thickness, double relEps, double sig, int listInd):
    Line(p1,p2),thick(thickness),epsilon(relEps),sigma(sig),indWall(listInd)
{

}
Wall::~Wall(void){}

QPointF Wall::symetricalPoint(const QPointF &point){
    QLineF normal = normalVector();
    QLineF finalVector(point,point);
    normal.translate(point);
    QPointF closestPoint;
    intersect(normal,&closestPoint);
    //intersect(normalVector().translate(point),&closestPoint);
    finalVector.setP2(closestPoint);
    finalVector.setLength(2*finalVector.length());
    return finalVector.p2();
}

QPointF Wall::otherPoint(const QPointF &point) const{
    QPointF res;
    if(point == p1()){
        res = p2();
    }
    else{
        res = p1();
    }
    return res;
}

QPointF Wall::farestExtrem(const QPointF &point) const{
    QLineF line1(point,this->p1()),line2(point,this->p2());
    QPointF res;
    if(line1.length()>line2.length()){
        res = p1();
    }else {
        res = p2();
    }
    return res;
}
