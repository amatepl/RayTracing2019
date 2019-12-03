#ifndef ANTENADIFFRACTION_H
#define ANTENADIFFRACTION_H

#include "AbstractAntena.h"
#include "ReceiverObserver.h"
#include "ray.h"

class AntenaDiffraction: public QPointF, public ReceiverObserver, public AbstractAntena
{
public:
    AntenaDiffraction(const QPointF &pos, const QPointF &p1, QPointF &p2, AbstractAntena* parent, QRectF sceneBoundary);
    //QPolygonF getIlluminationZone(QPointF &p1, QPointF &p2);
    void setSceneBoundary(const QRectF &rect);
    void buildIlluminationZone(const QPointF &p1, const QPointF &p2);
    // Overrides from AbstractAntena
    virtual void notifyParent(const QPointF &point, vector<ray>* wholeRay) override;
    virtual QPointF getPosition()const override;
    virtual QPolygonF getIlluminationZone()const override;
    virtual QPolygonF getIlluminationZone(const QRectF &rect)const override;
    virtual QPolygonF getIlluminatedZone()const override;
    virtual void setIlluminatedZone(const QPolygonF &zone) override;

    // Overrides from ReceiverObserver
    virtual void notifyObserver(const QPointF &pos) override;

private:
    AbstractAntena *m_parent;
    QPolygonF m_zone;
    QRectF m_sceneBoundary;
};

#endif // ANTENADIFFRACTION_H
