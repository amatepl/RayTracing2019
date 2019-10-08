#include "ray.h"


/*
 * Ray is the multi-traject class, it is simpler to use a complet class to follow the ray, it detains the \teta information as well as the total distance
 * The ray object gets after processing a set on points, on which all lines are drawn. It has one starting point, one point of segmentation.
 *
 * The rays will be put into two-dimentionnal arrays, the full path taken by light is one of those ray vectors, and all rays are the vector of those vectors.
 *
 * d ==  distance
 * teta == incidence angle
 * wallIbouncedOn == indice of the wall it has been reflected to.
 */


ray::ray(double x01, double y01, double x02, double y02,double Tetai,int indWall):
    Line(x01, y01, x02, y02),wallIBouncedOn(indWall)

{
    setTetai(Tetai);
    updateMeterLength();
//    double a;
//    if(x01 == x02){
//        if (y02 - y01 >= 0){
//            a = -INFINITY;
//            theta = -M_PI/2;
//        }else{
//        // If the line is vertically oriented, the slope is infinite
//            a = INFINITY;
//            theta = M_PI/2;
//        }
//    }
//    else{
//        if (x02-x01 >= 0){
//            a =(y02 - y01)/(x02 - x01);
//            theta = atan(a)+M_PI;
//        }else{
//            a =(y02 - y01)/(x02 - x01);
//            theta = atan(a);
//        }
//    }
}

ray::ray(const QPointF &p1,const QPointF &p2, double Tetai, int indWall):
    Line(p1,p2),wallIBouncedOn(indWall)
{
    setTetai(Tetai);
    updateMeterLength();
}

ray::~ray(void){
    //std::cout<<"Ray destroyed"<<std::endl;
}

/*
 * It is necessary to update the real length when the ray is transmitted through a wall. See function in room::distInWall()
 */

// void ray::updateLength(double length_inWall){
//     meterLength += length_inWall;
//     d += length_inWall/(2*pow(10,-2));
// }


/*
 * The scale chosen for the meter-pixels conversion is 1px = 1dm
 */


void ray::updateMeterLength(){meterLength = length()*0.1;} // pxToMeter = 0.1



// --> Getters && Settets

int ray::getWallInd() const{return wallInd;}
double ray::getTetai()const{return m_tetai;}
double ray::getTheta()const{return theta;}
int ray::getIndWall()const{return wallIBouncedOn;}
double ray::getMeterLength()const{return meterLength;}

void ray::setTetai(double tetai){
    if(tetai > 180){
        m_tetai = (tetai-180)*M_PI/180;
    }
    else
        m_tetai = tetai*M_PI/180;
}

