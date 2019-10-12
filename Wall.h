#ifndef WALL_H
#define WALL_H

#include "Line.h"


class Wall: public Line
{
public:
    Wall(double x01 = 0 , double y01 = 0, double x02 = 0, double y02 = 0, double thickness = 0.0, double relEps = 0.0, double sig = 0.0, int listInd = 0);
    Wall(const QPointF &p1, const QPointF &p2, double thickness = 0.0, double relEps = 0.0, double sig = 0.0, int listInd = 0);
    ~Wall(void);
    double getThick()const;
    double getSigma()const;
    double getEpsilon()const;
    int getIndWall()const;
    QPointF symetricalPoint(const QPointF &point);


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
