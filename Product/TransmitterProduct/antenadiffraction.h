#ifndef ANTENADIFFRACTION_H
#define ANTENADIFFRACTION_H

#include "Product/abstractantena.h"
#include "Observer/productobserver.h"
#include "Observer/productobservable.h"
#include "Product/RayProduct/mathematicalrayproduct.h"
#include "Abstract_Factory/abstractrayfactory.h"
#include "Product/CarProduct/mathematicalcarproduct.h"

class AntenaDiffraction: public QPointF, public ProductObserver, public AbstractAntena
{
public:
    AntenaDiffraction(const QPointF &pos, const QPointF &p1, QPointF &p2,
                      AbstractAntena* parent, QRectF sceneBoundary);
    AntenaDiffraction(const QPointF &pos, const QPointF &p1, QPointF &p2,
                      AbstractAntena* parent);
    ~AntenaDiffraction() override;
    //QPolygonF getIlluminationZone(QPointF &p1, QPointF &p2);
    void setSceneBoundary(const QRectF &rect);
    void buildIlluminationZone(const QPointF &p1, const QPointF &p2);
    QPolygonF buildCoverage();
//    bool inIlluminatedCars(MathematicalCarProduct *car, int *idx);

    // Overrides from AbstractAntena
    virtual void notifyParent(ProductObservable *productObservable, QLineF const movement,
                              const QPointF &point, vector<MathematicalRayProduct *> *wholeRay) override;
    virtual QPointF getPosition() const override;
    virtual QPolygonF getIlluminationZone() const override;
    virtual QPolygonF getIlluminationZone(const QRectF &rect) const override;
    virtual QPolygonF getIlluminatedZone() const override;
    virtual void setIlluminatedZone(const QPolygonF &zone) override;

    // Overrides from ProductObserver
    virtual void update(ProductObservable *productObservable, QLineF const movement) override;
    void notifyCarDetected() override {};
//    void updateCarPos(ProductObservable *productObservable) override;
    void attachObservable(ProductObservable *productObservable) override;

private:
    AbstractAntena *m_parent;
    QPolygonF m_zone;
    QRectF m_sceneBoundary;
    vector<ProductObservable *> m_observable;
    int m_radius;

public slots:

    void carMoved(MathematicalCarProduct *car, int x, int y, double orientation) override;
};

#endif // ANTENADIFFRACTION_H
