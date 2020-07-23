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
    virtual void notifyParent(ProductObservable *receiver,QLineF const movement,
                              const QPointF &point, vector<MathematicalRayProduct*> *wholeRay) = 0;

    enum typeWall {wall, front, back};
    virtual QPointF getPosition()const = 0;
    virtual QPolygonF getIlluminationZone()const = 0;
    virtual QPolygonF getIlluminationZone(const QRectF &rect)const = 0;
    virtual QPolygonF getIlluminatedZone()const{return m_zone;};
    virtual void setIlluminatedZone(const QPolygonF &zone){m_zone = zone;};
    virtual void setRayFactory(AbstractRayFactory* rayFactory){m_rayFactory = rayFactory;};
    virtual MathematicalBuildingProduct* getBuilding()const{return m_building;};
    virtual void setBuilding(MathematicalBuildingProduct* building){m_building = building;}

    virtual void setWallType(int type)
    {
        m_wallType = type;
    }

    virtual QLineF movement() const {return m_movement;}
    virtual void setMovement(QLineF const movement) {m_movement = movement;}


    //virtual QPolygonF getIluminationZone(const QRectF &rect)const = 0;

protected:

    MathematicalBuildingProduct *m_building;
    QPolygonF m_zone;
    AbstractRayFactory *m_rayFactory;
    QLineF m_movement {QLineF(.0,.0,.0,.0)};
    //double m_speed {0};
    //double m_orientation{0};
    int m_wallType{wall};

};

#endif // ABSTRACTANTENA_H
