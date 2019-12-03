#include "AntenaDiffraction.h"

AntenaDiffraction::AntenaDiffraction(const QPointF &pos,const QPointF &p1, QPointF &p2, AbstractAntena* parent, QRectF sceneBoundary)
    :QPointF(pos),m_parent(parent),m_sceneBoundary(sceneBoundary)
{
 buildIlluminationZone(p1,p2);
}

void AntenaDiffraction::buildIlluminationZone(const QPointF &p1,const QPointF &p2){
    QPolygonF illuminationZone;
    QLineF line1(*this,p2);
    line1.setLength(50000);
    QLineF line2(*this,p1);
    line2.setLength(50000);
    illuminationZone<<*this << line1.p2()<<line2.p2();
    m_zone = illuminationZone.intersected(m_sceneBoundary);

}

void AntenaDiffraction::setSceneBoundary(const QRectF &rect){
    m_sceneBoundary = rect;
}


QPolygonF AntenaDiffraction::getIlluminationZone() const
{
    return m_zone;
}

QPolygonF AntenaDiffraction::getIlluminationZone(const QRectF &rect)const {
    /*
     * For the moment it's exactly the same as the one above.
     */

    return m_zone;
}
QPolygonF AntenaDiffraction::getIlluminatedZone()const{
    return m_zone;
}

void AntenaDiffraction::setIlluminatedZone(const QPolygonF &zone){
    m_zone = zone;
}

void AntenaDiffraction::notifyObserver(const QPointF &pos){
    if(m_zone.containsPoint(pos,Qt::OddEvenFill)){
        vector<ray> *wholeRay = new vector<ray>;
        QLineF line(*this,pos);

        ray newRay(*this,pos);
        newRay.setDiffracted(true);
        wholeRay->push_back(newRay);
        m_parent->notifyParent(*this,wholeRay);
    }
}

void AntenaDiffraction::notifyParent(const QPointF &point, vector<ray> *wholeRay){
    QLineF line(*this,point);
    ray newRay(*this,point);
    wholeRay->push_back(newRay);
    m_parent->notifyParent(*this,wholeRay);
}

QPointF AntenaDiffraction::getPosition() const {
    return *this;
}
