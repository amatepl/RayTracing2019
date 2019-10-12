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
    return slope;
}

QPointF Line::symetricalPoint(const QPointF &point){
    QLineF pointToWall(p1(), point);
    pointToWall.setAngle(angle()-angleTo(pointToWall));
    return pointToWall.p2();



//    double ray_vector_length = sqrt(pow(transmitterPosY - current_wall->y2(),2) + pow(transmitterPosX - current_wall->x2(),2));
//    double virtual_slope;

//    if (transmitterPosY - current_wall->y2() < 0 && transmitterPosX - current_wall->x2()){
//        virtual_slope = -acos((transmitterPosX - current_wall->x2())/ray_vector_length);
//    }

//    else{
//        virtual_slope = acos((transmitterPosX - current_wall->x2())/ray_vector_length);
//    }

//    double ray_slope = angle_wall + (angle_wall - virtual_slope);
//    double ray_vector[2] ={cos(ray_slope) , sin(ray_slope)};
//    double x2 = ray_vector_length * ray_vector[0];
//    double y2 = ray_vector_length * ray_vector[1];
//    double transmitterImagePosX = current_wall->x2() + x2;
//    double transmitterImagePosY = current_wall->y2() + y2;

}

QPointF Line::symetricalPoint(const double x, const double y){
    double vec1x = (p2().x() - p1().x())/length();
    double vec1y = (p2().y() - p1().y())/length();
    double length = sqrt(pow(x-p1().x(),2) + pow(y-p1().y(),2));
    double vec2x = (x-p1().x())/length;
    double vec2y = (y-p1().y())/length;

    vec2x = vec1x*vec2x + vec1y*vec2y;              //  cos(theta) = vec1.vec2

    vec2x = sqrt(1 - pow(vec2x,2));                 //  sin(theta) = sqrt(1 - cos(theta)^2)

    vec2x = vec2x*2*length;   // Distance from the initial point to p1

    vec2y = -vec1x*vec2x;

    vec1x = vec1y*vec2x;

//    if(x == vec1x && y == vec2y){
//        vec2y = -vec2y;

//        vec1x = -vec1x;
//    }

    QPointF image(x+vec1x,y+vec2y);

    return image;



//    QPointF point(x,y);
//    QLineF pointToWall(p1(), point);
//    pointToWall.setAngle(angle()-angleTo(pointToWall));
//    return pointToWall.p2();


//    QLineF normal = normalVector();
//    normal.translate(point);

//    QLineF finalVector(point,point);
//    QPointF closestPoint;
//    intersect(normal,&closestPoint);
//    finalVector.setP2(closestPoint);
//    finalVector.setLength(2*finalVector.length());
//    std::cout<<finalVector.length()<<std::endl;
//    return finalVector.p2();

}
