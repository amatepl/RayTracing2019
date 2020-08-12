#ifndef TRANSMITTERIMAGE_H
#define TRANSMITTERIMAGE_H

#include <QPointF>
#include <QLineF>

#include "Observer/productobserver.h"
#include "Observer/productobservable.h"
#include "Product/abstractantena.h"
#include "Product/RayProduct/mathematicalrayproduct.h"  // Should probably be deleted
#include "Share/wall.h"
#include "Abstract_Factory/abstractrayfactory.h"
#include "Product/CarProduct/mathematicalcarproduct.h"


using namespace std;

class TransmitterImage: public QPointF, public ProductObserver,
                        public AbstractAntena
{
public:
    TransmitterImage(const Line &wall, AbstractAntena *parent);
    ~TransmitterImage() override;
    QPointF sceneRectIntersection(const QRectF &rect, const QLineF  &line) const;
    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone) const;
    //void setBuilding(MathematicalBuildingProduct *building);
    void setSceneBoundary(const QRectF &rect);
    QPolygonF buildCoverage();
//    bool inIlluminatedCars(MathematicalCarProduct *car, int *idx);

    //AbstractAntena
    void notifyParent(ProductObservable *productObservable, QLineF const movement,
                      const QPointF &point, vector<MathematicalRayProduct *> *wholeRay) override;
    void notifyCarDetected() override;
    QPolygonF getIlluminationZone() const override;
    QPolygonF getIlluminationZone(const QRectF &) const override;
    QPointF getPosition() const override;


    //ProductObserver
    void update(ProductObservable *productObservable, QLineF const) override;
//    void updateCarPos(ProductObservable *productObservable) override;
    void attachObservable(ProductObservable *productObservable) override;

private:
    Line m_wall;
    AbstractAntena *m_parent;
    QRectF m_sceneBoundary;
    vector<ProductObservable *> m_observable;
    int m_radius;

public slots:
    void carMoved(MathematicalCarProduct *car, int, int, double) override;


};

#endif // TRANSMITTERIMAGE_H
