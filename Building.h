#ifndef BUILDING_H
#define BUILDING_H

#include <QRectF>
#include <QVector>
#include <QPointF>
#include <QGraphicsRectItem>
#include "Wall.h"
//#include "Visualizer.h"
#include <QGraphicsScene>

class Building: public QRectF
{
public:
    Building(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, QGraphicsScene *scene);
    Building(const QPointF &p1, const QPointF &p3, QGraphicsScene *scene);

private:
    Wall *m_walls[4]; // Array of pointers.
    QPointF m_p1;
    QPointF m_p2;
    QPointF m_p3;
    QPointF m_p4;
    //Visualizer *m_view;
    QGraphicsScene *m_scene;
};

#endif // BUILDING_H
