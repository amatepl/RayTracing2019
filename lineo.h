#ifndef LINEO_H
#define LINEO_H

//#include "room.h"

#include <QGraphicsLineItem>
#include <QGraphicsScene>

class room;

class lineo: public QGraphicsLineItem
{
public:
    lineo(int x01 = 0, int y01 = 0, int x02 = 0, int y02 = 0 , room *scene = NULL);
    void show_line(int a);
    double getLength();
    int vectX();
    int vectY();
    double getSlope();
    double getYorigin();
    void setSlope(double slope);
    void setAngle(double angle);
    int getX1();
    int getY1();
    int getX2();
    int getY2();
    void setX1(double x01);
    void setY1(double y01);
    void setX2(double x02);
    void setY2(double y02);
    double getAngle();

protected:
    room *myRoom;
    double x1;
    double y1;
    double x2;
    double y2;
    double angle;

    double a;
    int b;

    double d; // Total distance of the segment

    void def_Slope(qreal x01, qreal y01, qreal x02, qreal y02);
    void def_YOrigin(qreal x01, qreal y01);
    void setLength();

};

#endif // LINEO_H
