#ifndef ABSTRACTANTENA_H
#define ABSTRACTANTENA_H

#include <QPolygonF>
#include <QLineF>

class QPointF;
class QPolygonF;
class  Building;

class AbstractAntena
{
public:
    virtual void notifyParent(const QPointF &point) = 0;
    virtual QPointF getPosition()const = 0;
    virtual QPolygonF getIlluminationZone()const = 0;
    virtual QPolygonF getIlluminationZone(const QRectF &rect)const = 0;
    virtual QPolygonF getIlluminatedZone()const = 0;
    virtual void setIlluminatedZone(const QPolygonF &zone) = 0;
    virtual Building* getBuilding()const;
    //virtual QPolygonF getIluminationZone(const QRectF &rect)const = 0;

protected:
    Building *m_building;

};

#endif // ABSTRACTANTENA_H
