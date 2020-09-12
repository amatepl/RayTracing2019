#include "wall.h"

Wall::Wall(double x01, double y01, double x02, double y02, double thickness, double relEps, double sig, int indWall):
    Line(x01, y01, x02, y02), m_thick(thickness), m_epsilon(relEps), m_sigma(sig), m_indWall(indWall)

  /*
   * inherits from Line, basic line function to be called when interacting with rays
   */

{

}


Wall::Wall(const QPointF &p1, const QPointF &p2, double thickness, double relEps, double sig, int indWall):
    Line(p1,p2), m_thick(thickness), m_epsilon(relEps), m_sigma(sig), m_indWall(indWall)
{

}


Wall::~Wall(void)
{
    std::cout << "Wall Deleted." << std::endl;
}


QPointF Wall::symetricalPoint(const QPointF &point){
    QLineF normal = normalVector();
    QLineF finalVector(point,point);
    normal.translate(point);
    QPointF closestPoint;
    intersects(normal,&closestPoint);
    //intersect(normalVector().translate(point),&closestPoint);
    finalVector.setP2(closestPoint);
    finalVector.setLength(2*finalVector.length());
    return finalVector.p2();
}


double Wall::getSpeed() const
{
    return m_movement.length();
}


double Wall::getOrientation() const
{
    return m_movement.angle();
}


int Wall::getWallType() const
{
    return m_wallType;
}

QLineF Wall::movement() const{
    return m_movement;
}

void Wall::setWallType(int type)
{
    m_wallType = type;
}


void Wall::setSpeed(double speed)
{
    m_movement.setLength(speed);
}


void Wall::setOrientation(double orientation)
{
    m_movement.setAngle(orientation);
}

void Wall::setMovement(const QLineF movement){
    m_movement = movement;
}

void Wall::setPoints(const QPointF &p0, const QPointF &p1){
    setP1(p0);
    setP2(p1);
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
