#ifndef RAY_H
#define RAY_H


// Dependencies
#include "lineo.h"
#include "wall.h"

// Libraries
#include "math.h"
#include <vector>


class lineo;

class ray: public lineo
{
private:

    int state;       // 0 for direct ray, 1 for transmitted ray, 2 for reflected ray, 3 for refracted ray

    // Coefficients

    double T;   // Transmission coefficient
    double G;   // Reflection coefficient

    int wallInd;
    double tetai ;
    double meterLength;
    int wallIBouncedOn;

    std::vector <wall*> walls_intersected;   // Pas la meilleure approche, trop à enregsitrer.

    void updateMeterLength();

public:

    ray(int x01 = 0, int y01 = 0, int x02 = 0, int y02 = 0,double tetai = 0,int indWall = 0, room *scene = 0);


    // Getters && Setters

    void updateLength(double length_inWall);
    double getCoefficient();
    int getWallInd();
    void setCoefficient(double iAngle, wall inWall);
    double getTetai();
    double getMeterLength();
    int getIndWall();

};

#endif // RAY_H
