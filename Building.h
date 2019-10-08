#ifndef BUILDING_H
#define BUILDING_H

#include <QVector>
#include <QPointF>
#include "Wall.h"

class Building
{
public:
    Building(int x1, int y1,int x2, int y2,int x3, int y3,int x4, int y4);
    Building(const QPointF &p1,const QPointF &p2);
};

#endif // BUILDING_H
