#ifndef ANTENAIMAGE_H
#define ANTENAIMAGE_H

#include <QPointF>
#include <QLineF>
#include <QPolygonF>

#include "Line.h"
#include "ReceiverObserver.h"
#include "AbstractAntena.h"
#include "ray.h"

using namespace std;

class AntenaImage : public QPointF, public ReceiverObserver, public AbstractAntena
{
public:
    AntenaImage( const Line &wall, AbstractAntena *parent);
    ~AntenaImage(void);
    QPolygonF getIlluminationZone()const override;
    QPolygonF getIlluminationZone(const QRectF &rect)const override;
    void setIlluminatedZone(const QPolygonF &zone) override;
    void notifyObserver(const QPointF &pos) override;
    void notifyParent(const QPointF &point, vector<ray>* wholeRay) override;
    QPointF getPosition() const override;
    QPolygonF getIlluminatedZone()const override;
    void setBuilding(Building *building);
    void setSceneBoundary(const QRectF &rect);
    QPointF sceneRectIntersection(const QRectF &rect, const QLineF  &line)const;
    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const;


private:
    Line m_wall;
    QPolygonF m_zone;
    AbstractAntena *m_parent;
    QRectF m_sceneBoundary;
};

#endif // ANTENAIMAGE_H
