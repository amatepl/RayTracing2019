#include "Wall.h"
#include <math.h>

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


// --> Getters && Setters
Wall::~Wall(void){

}


double Wall::getEpsilon() const{return thick;}
double Wall::getSigma() const{return epsilon;}
double Wall::getThick() const{return sigma;}
int Wall::getIndWall() const{return indWall;}

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
