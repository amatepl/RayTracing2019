#ifndef WALL_H
#define WALL_H

#include "lineo.h"

class lineo;

class wall: public lineo
{
public:
    wall(room *scene = 0,qreal x01 = 0 , qreal y01 = 0, qreal x02 = 0, qreal y02 = 0, double thickness = 0.0, double relEps = 0.0, double sig = 0.0, int listInd = 0);
    double getThick();
    double getSigma();
    double getEpsilon();
    int getIndWall();

private:
    /*
     * if the line equation is written y = ax + b, where a is the slope and b is the origin y position
     */
    double thick;
    double epsilon;
    double sigma;
    int indWall;
};

#endif // WALL_H
