#ifndef ABSTRACTANTENA_H
#define ABSTRACTANTENA_H

#include <iostream>

#include <QPolygonF>
#include <QLineF>
#include <QObject>

/* Project Specific */

#include "Share/wholeray.h"

using namespace std;

class QPointF;
class QPolygonF;
class  Building;
class Ray;
class AbstractRayFactory;
class ProductObservable;
class MathematicalCarProduct;

class AbstractAntena: public QObject
{
    Q_OBJECT

public:
    virtual ~AbstractAntena(){};
    virtual void notifyParent(QPointF *receiver,double speed,
                              const QPointF &point, WholeRay *wholeRay) = 0;
    virtual void notifyCarDetected() = 0;

    enum typeWall {wall, front, back};
    virtual QPointF getPosition() const = 0;
    virtual QPolygonF getIlluminationZone() const = 0;
    virtual QPolygonF getIlluminationZone(const QRectF &rect) const = 0;
    virtual QPolygonF getIlluminatedZone() const;
    virtual void setIlluminatedZone(const QPolygonF &zone);
    virtual void setRayFactory(AbstractRayFactory *rayFactory);
    virtual Building *getBuilding() const;
    virtual void setBuilding(Building *building);

    virtual void setWallType(int type);

    virtual QLineF movement() const;
    virtual void setMovement(QLineF const movement);
    bool carInIlluminatedCars(MathematicalCarProduct *car, int *idx);
    bool inIlluminatedCars(MathematicalCarProduct *car, int *idx);


    //virtual QPolygonF getIluminationZone(const QRectF &rect)const = 0;

protected:

    Building *m_building;
    QPolygonF m_zone;
    QPolygonF m_tmpZone;
    vector<MathematicalCarProduct *> m_illuminatedCars;
    AbstractRayFactory *m_rayFactory = nullptr;
    QLineF m_movement {QLineF(.0,.0,.0,.0)};
    int m_wallType{wall};


public slots:
    virtual void carMoved(MathematicalCarProduct *car, int x, int y, double orientation) = 0;

signals:
    void detectsCar(AbstractAntena *tx);

};

#endif // ABSTRACTANTENA_H
