#include "antenadiffraction.h"

AntenaDiffraction::AntenaDiffraction(const QPointF &pos, const QPointF &p1, QPointF &p2, AbstractAntena *parent, QRectF sceneBoundary)
    : QPointF(pos), m_parent(parent), m_sceneBoundary(sceneBoundary), m_radius(500)
{
 buildIlluminationZone(p1, p2);
 //m_zone = buildCoverage();
}


AntenaDiffraction::AntenaDiffraction(const QPointF &pos, const QPointF &p1, QPointF &p2, AbstractAntena *parent)
    : QPointF(pos), m_parent(parent), m_radius(500)
{
 buildIlluminationZone(p1, p2);
}


void AntenaDiffraction::buildIlluminationZone(const QPointF &p1, const QPointF &p2)
{
    QPolygonF illuminationZone;
    QLineF line1(*this, p2);
    line1.setLength(50000);
    QLineF line2(*this, p1);
    line2.setLength(50000);
    illuminationZone << *this << line1.p2() << line2.p2();
//    m_zone = illuminationZon.e.intersected(m_sceneBoundary);
    m_zone = illuminationZone.intersected(buildCoverage());
//    cout<<"Number of corners of the illumination zone of a diffracted ray: "<<m_zone.size()<<endl;
//    if(m_zone.size()>0){
//        cout<<"The first point of the illumination zone is the position of the corner: "<<(m_zone.at(0)==*this)<<endl;
//    }
    //m_zone = illuminationZone;

}


QPolygonF AntenaDiffraction::buildCoverage()
{
    QPolygonF coverage;
    for (int i = 0; i < 16; i++) {
        coverage << QPointF(x() + m_radius * cos(M_PI * i / 8), y() + m_radius * sin(M_PI * i / 8));
    }
    return coverage;
}


void AntenaDiffraction::setSceneBoundary(const QRectF &rect)
{
    m_sceneBoundary = rect;
}


QPolygonF AntenaDiffraction::getIlluminationZone() const
{
    return m_zone;
}


QPolygonF AntenaDiffraction::getIlluminationZone(const QRectF &rect) const
{
    /*
     * For the moment it's exactly the same as the one above.
     */

    return m_zone;
}


QPolygonF AntenaDiffraction::getIlluminatedZone() const
{
    return m_zone;
}


void AntenaDiffraction::setIlluminatedZone(const QPolygonF &zone)
{
    m_zone = zone;
}


void AntenaDiffraction::update(ProductObservable *productObservable, const float speed, const float direction)
{
    if (m_zone.containsPoint(*productObservable->getPos(), Qt::OddEvenFill)) {
        vector<MathematicalRayProduct *> *wholeRay = new vector<MathematicalRayProduct *>;
        QLineF line(*this, *productObservable->getPos());

        //ray newRay(*this,pos);
        MathematicalRayProduct *newRay = m_rayFactory->createRay(*this, *productObservable->getPos());
        newRay->setDiffracted(true);
        wholeRay->push_back(newRay);
        m_parent->notifyParent(productObservable, speed, direction, *this, wholeRay);
    }
}


void AntenaDiffraction::notifyParent(ProductObservable *productObservable, const float speed, const float direction, const QPointF &point, vector<MathematicalRayProduct *> *wholeRay)
{
    QLineF line(*this, point);
    //ray newRay(*this,point);
    MathematicalRayProduct *newRay = m_rayFactory->createRay(*this, point);
    newRay->setDiffracted(true);
    wholeRay->push_back(newRay);
    m_parent->notifyParent(productObservable, speed, direction, *this, wholeRay);
}


QPointF AntenaDiffraction::getPosition() const
{
    return *this;
}


void AntenaDiffraction::attachObservable(ProductObservable *productObservable)
{
    m_observable.push_back(productObservable);
}
