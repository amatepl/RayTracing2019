#include "Line.h"

Line::Line(qreal x1, qreal y1, qreal x2, qreal y2):QLineF(x1,y1,x2,y2)
{

}

Line::Line(const QPointF &p1,const QPointF &p2):QLineF(p1,p2)
{

}

double Line::getAngleRad()const{
    double angle_in_radians;
    if(angle()>180){
        angle_in_radians = (angle() -180)*M_PI/180;
    }
    else
        angle_in_radians = angle()*M_PI/180;
    return angle_in_radians;
}

double Line::getSlope()const{
    double slope;
    if(dx() != 0){
        slope = dy()/dx();
    }else
        if(dy()>0){
            slope = -INFINITY;
        }
        else
            slope = INFINITY;
}
