#ifndef ABSTRACTANTENA_H
#define ABSTRACTANTENA_H

#include <QPolygonF>
#include <QLineF>

using namespace std;

class QPointF;
class QPolygonF;
class  MathematicalBuildingProduct;
class MathematicalRayProduct;
class AbstractRayFactory;
class ProductObservable;

class AbstractAntena
{
public:
    virtual void notifyParent(ProductObservable *receiver,const float speed, const float direction, const QPointF &point, vector<MathematicalRayProduct*> *wholeRay) = 0;
    virtual QPointF getPosition()const = 0;
    virtual QPolygonF getIlluminationZone()const = 0;
    virtual QPolygonF getIlluminationZone(const QRectF &rect)const = 0;
    virtual QPolygonF getIlluminatedZone()const{return m_zone;};
    virtual void setIlluminatedZone(const QPolygonF &zone){m_zone = zone;};
    virtual void setRayFactory(AbstractRayFactory* rayFactory){m_rayFactory = rayFactory;};
    virtual MathematicalBuildingProduct* getBuilding()const{return m_building;};
    virtual void setBuilding(MathematicalBuildingProduct* building){m_building = building;}
    //virtual QPolygonF getIluminationZone(const QRectF &rect)const = 0;

protected:
    MathematicalBuildingProduct *m_building;
    QPolygonF m_zone;
    AbstractRayFactory *m_rayFactory;


};

#endif // ABSTRACTANTENA_H
