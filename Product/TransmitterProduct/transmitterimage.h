#ifndef TRANSMITTERIMAGE_H
#define TRANSMITTERIMAGE_H

#include <QPointF>
#include <QLineF>
#include <QPolygonF>

#include "Share/line.h"
#include "Observer/productobserver.h"
#include "Product/abstractantena.h"
#include "Product/RayProduct/mathematicalrayproduct.h"  // Should probably be deleted
#include "Abstract_Factory/abstractrayfactory.h"

//class MathematicalRayProduct;

using namespace std;

class TransmitterImage: public QPointF, public ProductObserver, public AbstractAntena
{
public:
    TransmitterImage(const Line &wall, AbstractAntena *parent);
    QPointF sceneRectIntersection(const QRectF &rect, const QLineF  &line)const;
    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const;
    //void setBuilding(MathematicalBuildingProduct *building);
    void setSceneBoundary(const QRectF &rect);
    QPolygonF buildCoverage();

    //AbstractAntena
    void notifyParent(const QPointF &point, vector<MathematicalRayProduct> *wholeRay) override;
    QPolygonF getIlluminationZone()const override;
    QPolygonF getIlluminationZone(const QRectF &rect)const override;
    QPointF getPosition()const override;


    //ProductObserver
    void notify(const QPointF &pos) override;
    void attachObservable(ProductObservable* productObservable) override;

private:
    Line m_wall;
    //QPolygonF m_zone;
    AbstractAntena *m_parent;
    QRectF m_sceneBoundary;
    vector<ProductObservable*> m_observable;
    int m_radius;
};

#endif // TRANSMITTERIMAGE_H
