#ifndef TXIMG_H
#define TXIMG_H

#include <QPointF>
#include <QLineF>

#include "Observer/productobserver.h"
#include "Observer/productobservable.h"
#include "Product/abstractantena.h"
#include "Product/RayProduct/ray.h"  // Should probably be deleted
#include "Share/wall.h"
#include "Abstract_Factory/abstractrayfactory.h"
#include "Product/CarProduct/car.h"

struct Data;

using namespace std;

class TxImg: public QPointF, public ProductObserver,
                        public AbstractAntena
{
public:
    TxImg(const Line &wall, AbstractAntena *parent, const double epsilonWall = 5);
    ~TxImg() override;
    QPointF sceneRectIntersection(const QRectF &rect, const QLineF  &line) const;
    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone) const;
    //void setBuilding(Building *building);
    void setSceneBoundary(const QRectF &rect);
    QPolygonF buildCoverage();
//    bool inIlluminatedCars(Car *car, int *idx);

    //AbstractAntena
    void notifyParent(QPointF *productObservable, double speed,
                      const QPointF &point, WholeRay *wholeRay) override;
    void notifyCarDetected() override;
    QPolygonF getIlluminationZone() const override;
    QPolygonF getIlluminationZone(const QRectF &) const override;
    QPointF getPosition() const override;


    //ProductObserver
    Data *update(QPointF *productObservable, QLineF const) override;
//    void updateCarPos(QPointF *productObservable) override;
    void attachObservable(QPointF *productObservable) override;

private:
    Line m_wall;
    AbstractAntena *m_parent;
    QRectF m_sceneBoundary;
    vector<QPointF *> m_observable;
    int m_radius;
    double m_epsilonWall;

public slots:
    void carMoved(Car *car, int, int, double) override;


};

#endif // TXIMG_H
