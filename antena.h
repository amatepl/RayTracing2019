#ifndef ANTENA_H
#define ANTENA_H
//#include "room.h"
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QPolygonF>
#include <iostream>
#include <QLineF>
#include <AbstractAntena.h>

using namespace std;
//class room;
//class QPen;

//class QBrush;

class antena: public QGraphicsEllipseItem,public AbstractAntena/*, public QPointF*/
{
public:
    antena(/*room *scene = 0,*/ QPointF p = QPointF() , int type = 0);
    ~antena();
    int getPosX();
    int getPosY();
    QPointF getPos()const;
    void setPosi(QPointF posi);
    QPolygonF getIlluminationZone(const QRectF &rect)const override;

    QPointF sceneRectIntersection(const QRectF &rect, const QLineF &line)const;
    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const;
    void notifyParent(const QPointF &point) override;
    QPointF getPosition()const override;
    QPolygonF getIlluminationZone()const override;
    void setSceneBoundary(const QRectF &rect);
    void setIlluminatedZone(const QPolygonF &zone) override;
    QPolygonF getIlluminatedZone()const override;

private:
    //room *myRoom;
    QPointF pos;
    int antenaType;
    QPen setColor();
    QPointF m_vector;
    QRectF m_sceneBoundary;
    QPolygonF m_zone;
};

#endif // ANTENA_H
