#ifndef RAY_H
#define RAY_H


// Dependencies
#include "Line.h"
#include "Wall.h"

// Libraries
#include "math.h"
#include <iostream>
#include <vector>


class ray: public Line
{
private:

    int state;       // 0 for direct ray, 1 for transmitted ray, 2 for reflected ray, 3 for refracted ray

    // Coefficients

    double T;   // Transmission coefficient
    double G;   // Reflection coefficient

    int wallInd;
    double m_tetai ;
    double meterLength;
    int wallIBouncedOn;
    double theta;

    std::vector <Wall*> walls_intersected;   // Pas la meilleure approche, trop à enregsitrer.

    void updateMeterLength();

public:

    ray(double x01 = 0, double y01 = 0, double x02 = 0, double y02 = 0, double tetai = 0, int indWall = 0);
    ~ray(void);

    // Getters && Setters

    // void updateLength(double length_inWall);
    double getCoefficient()const;
    int getWallInd()const;
    void setCoefficient(double iAngle, Wall inWall);
    double getTetai()const;
    void setTetai(double tetai);
    double getTheta()const;
    double getMeterLength()const;
    int getIndWall()const;

};

#endif // RAY_H
