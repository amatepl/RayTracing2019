#ifndef LINEO_H
#define LINEO_H

//#include "room.h"

#include <QGraphicsLineItem>
#include <QGraphicsScene>

class room;

class lineo
{
public:
    lineo(double x01 = 0, double y01 = 0, double x02 = 0, double y02 = 0 );
    ~lineo(void);
    double getLength();
    int vectX();
    int vectY();
    long double getSlope();
    double getYorigin();
    void setSlope(double slope);
    void setAngle(double angle);
    double getX1();
    double getY1();
    double getX2();
    double getY2();
    void setX1(double x01);
    void setY1(double y01);
    void setX2(double x02);
    void setY2(double y02);
    double getAngle();

protected:
    double x1;
    double y1;
    double x2;
    double y2;
    double angle;

    long double a;
    int b;

    double d; // Total distance of the segment

    void def_Slope(double x01, double y01, double x02, double y02);
    void def_YOrigin(double x01, double y01);
    void setLength();

};

#endif // LINEO_H
