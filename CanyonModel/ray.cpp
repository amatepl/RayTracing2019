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
    lineo(x01, y01, x02, y02)

{
    tetai = Tetai;
    wallIBouncedOn = indWall;
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
 * The scale chosen for the meter-pixels conversion is 1px = 2cm
 */

void ray::updateMeterLength(){meterLength = d*0.1;} // pxToMeter = 0.1


// --> Getters && Settets

int ray::getWallInd(){return wallInd;}
double ray::getTetai(){return tetai;}
int ray::getIndWall(){return wallIBouncedOn;}
double ray::getMeterLength(){return meterLength;}
