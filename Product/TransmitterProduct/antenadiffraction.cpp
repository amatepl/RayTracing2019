#include "antenadiffraction.h"

AntenaDiffraction::AntenaDiffraction(const QPointF &pos, const QPointF &p1, QPointF &p2,
                                     AbstractAntena *parent, QRectF sceneBoundary)
    : QPointF(pos), m_parent(parent), m_sceneBoundary(sceneBoundary), m_radius(500)
{
 buildIlluminationZone(p1, p2);
 //m_zone = buildCoverage();
}


AntenaDiffraction::AntenaDiffraction(const QPointF &pos, const QPointF &p1,
                                     QPointF &p2, AbstractAntena *parent)
    : QPointF(pos), m_parent(parent), m_radius(500)
{
 buildIlluminationZone(p1, p2);
}


AntenaDiffraction::~AntenaDiffraction()
{

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
    m_tmpZone = m_zone;
//    if(m_zone.size()>0){
//        cout<<"The first point of the illumination zone is the position of the corner: "
//            << (m_zone.at(0)==*this)<<endl;
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


QPolygonF AntenaDiffraction::getIlluminationZone(const QRectF &/*rect*/) const
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
    m_tmpZone = zone;
}


Data *AntenaDiffraction::update(QPointF *productObservable, QLineF const /*movement*/)
{
    if (m_zone.containsPoint(*productObservable, Qt::OddEvenFill)) {
        WholeRay *wholeRay = new WholeRay;
        QLineF line(*this, *productObservable);

        //ray newRay(*this,pos);
        unique_ptr<Ray> newRay = m_rayFactory->createRay(*this, *productObservable);
        newRay->setDiffracted(true);
        wholeRay->push_back(move(newRay));
        m_parent->notifyParent(productObservable,0.0 , *this, wholeRay);
    }
    return nullptr;
}

//void AntenaDiffraction::updateCarPos(QPointF *productObservable)
//{
//    Car *car = dynamic_cast<Car *>(productObservable);

//    int idx = 0;
//    if (carInIlluminatedCars(car, &idx)) {

//        if (!m_zone.intersects(*car)) {
//            m_illuminatedCars.erase(m_illuminatedCars.begin() + idx);
//        }

//    } else {

//        if (m_zone.intersects(*car)) {
//            m_illuminatedCars.push_back(car);
//        }
//    }
//}


void AntenaDiffraction::notifyParent(QPointF *productObservable,
                                     double speed,
                                     const QPointF &point, WholeRay *wholeRay)
{
    QLineF line(*this, point);
    //ray newRay(*this,point);
    unique_ptr<Ray> newRay = m_rayFactory->createRay(*this, point);
    newRay->setDiffracted(true);
    wholeRay->push_back(move(newRay));
    m_parent->notifyParent(productObservable, speed, *this, wholeRay);
}


QPointF AntenaDiffraction::getPosition() const
{
    return *this;
}


void AntenaDiffraction::attachObservable(QPointF *productObservable)
{
    m_observable.push_back(productObservable);
}


void AntenaDiffraction::carMoved(Car *car, int /*x*/, int /*y*/, double /*orientation*/)
{
    int idx = 0;
    if (m_zone.intersects(*car)) {

        m_illuminatedCars.push_back(car);

        m_zone = m_tmpZone.subtracted(car->shadow(*this));

    } else if (inIlluminatedCars(car, &idx)) {

        m_zone = m_tmpZone;

        m_illuminatedCars.erase(m_illuminatedCars.begin() + idx);
    }
}

//bool AntenaDiffraction::inIlluminatedCars(Car *car, int *idx)
//{
//    for (unsigned i = 0; i < m_illuminatedCars.size(); i++) {
//        if (m_illuminatedCars.at(i) == car) {
//            *idx = i;
//            return true;
//        }
//    }
//    return false;
//}
