#include "tximg.h"

TxImg::TxImg(const Line &wall, AbstractAntena *parent, const double epsilonWall):
      QPointF(),m_wall(wall),m_parent(parent),m_radius(500), m_epsilonWall(epsilonWall)
{
    QPointF pos = m_wall.symetricalPoint(parent->getPosition());
    setX(pos.x()); setY(pos.y());
    m_zone = buildCoverage();
}
TxImg::~TxImg(){
//    cout << "Transmitter Image Deleted." << endl;
}


QPointF TxImg::sceneRectIntersection(const QRectF &rect, const QLineF  &line) const
{
    /*
     * This function takes a bounding ray (line) of the illumination zone and gives
     * its intersection with the scene boundaries.
     */

    QLineF boundary1(rect.topLeft(),rect.bottomLeft()),
            boundary2(rect.bottomLeft(),rect.bottomRight()),
            boundary3(rect.bottomRight(),rect.topRight()),
            boundary4(rect.topRight(),rect.topLeft());

    QPointF intersectionPoint;

    if (line.intersects(boundary1, &intersectionPoint) == 1) {
    } else if (line.intersects(boundary2, &intersectionPoint) == 1) {
    } else if (line.intersects(boundary3, &intersectionPoint) == 1) {
    } else if (line.intersects(boundary4, &intersectionPoint) == 1) {
    }

    return intersectionPoint;
}


vector <QPointF> TxImg::boundaryCorners(const QRectF &rect,
                                                  const QPolygonF &unboundedZone) const
{
    /*
     * Gives the corners of the scene bounding rectangle that lie in the ubounded
     * illumination zone.
     * It is used to complete the bounded illumination zone polygone.
     */

    vector <QPointF> points;
    if(unboundedZone.containsPoint(rect.topLeft(),Qt::OddEvenFill)){
        points.push_back(rect.topLeft());
    }
    if(unboundedZone.containsPoint(rect.bottomLeft(),Qt::OddEvenFill)){
        points.push_back(rect.bottomLeft());
    }
    if(unboundedZone.containsPoint(rect.bottomRight(),Qt::OddEvenFill)){
        points.push_back(rect.bottomRight());
    }
    if(unboundedZone.containsPoint(rect.topRight(),Qt::OddEvenFill)){
        points.push_back(rect.topRight());
    }
    return points;
}

//void TxImg::setBuilding(Building *building){
//    m_building = building;
//}

void TxImg::setSceneBoundary(const QRectF &rect){
    m_sceneBoundary = rect;
}


QPolygonF TxImg::buildCoverage(){
    QPolygonF coverage;
    QLineF line = m_wall;
    line.setLength(line.length()/2);
//    for(int i=0;i<16;i++){
//        coverage<<QPointF(x()+m_radius*cos(M_PI*i/8),y()+m_radius*sin(M_PI*i/8));
//    }

    for(int i=0;i<16;i++){
        coverage<<QPointF(round(line.p2().x()+m_radius*cos(M_PI*i/8)),
                            round(line.p2().y()+m_radius*sin(M_PI*i/8)));
    }
    return coverage;
}

QPolygonF TxImg::getIlluminationZone() const
{
    QPolygonF zone;
    QLineF line1(*this, m_wall.p2());
    line1.setLength(50000);
    QLineF line2(*this, m_wall.p1());
    line2.setLength(50000);
    zone<<m_wall.p2()<<line1.p2()<<line2.p2()<<m_wall.p1();
//    return zone.intersected(m_sceneBoundary);
    return zone.intersected(m_zone);
    //return m_zone;
}

QPolygonF TxImg::getIlluminationZone(const QRectF & /*rect*/) const
{
    /*
     * For the moment it's exactly the same as the one above.
     */


    QPolygonF zone;
    QLineF line1(*this,m_wall.p2());
    line1.setLength(50000);
    line1.setP1(m_wall.p2());
    QLineF line2(*this,m_wall.p1());
    line2.setLength(50000);
    line1.setP2(m_wall.p1());

    QPolygonF unboundedZone;
    unboundedZone<<m_wall.p2()<<line1.p2()<<line2.p2()<<m_wall.p1();

    zone<<m_wall.p2()<<sceneRectIntersection(m_sceneBoundary,line1);


    for (QPointF p: boundaryCorners(m_sceneBoundary,unboundedZone)) {
        zone<<p;
    }

    zone<<sceneRectIntersection(m_sceneBoundary,line2)
       <<m_wall.p1();
    return zone;
}

Data *TxImg::update(QPointF *productObservable, QLineF const /*movement*/)
{

    if(m_zone.containsPoint(*productObservable,Qt::OddEvenFill)){

        WholeRay *wholeRay = new WholeRay;
        QLineF line(*this,*productObservable);
        QPointF reflectionPoint;
        m_wall.intersects(line, &reflectionPoint);

//        Ray ray(*m_rayFactory->createRay(reflectionPoint, *productObservable->getPos(),
//                                                            line.angleTo(m_wall)));

        double angle = m_movement.angleTo(QLineF(reflectionPoint,*productObservable));
        double speed = m_movement.length()*cos(angle*M_PI/180.0);

        wholeRay->push_back(m_rayFactory->createRay(reflectionPoint,
                                                    *productObservable,
                                                    line.angleTo(m_wall),
                                                    m_epsilonWall));

        m_parent->notifyParent(productObservable, speed, reflectionPoint, wholeRay);
    }

    return nullptr;
}


//void TxImg::updateCarPos(QPointF *productObservable)
//{
//    MathematicalCarProduct *car = dynamic_cast<MathematicalCarProduct *>(productObservable);

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


void TxImg::attachObservable(QPointF* productObservable){
    m_observable.push_back(productObservable);
}


void TxImg::notifyParent(QPointF *productObservable,
                                    double speed, const QPointF &point,
                                    WholeRay *wholeRay)
{
    QLineF line(*this,point);
    QPointF reflectionPoint;

    m_wall.intersects(line, &reflectionPoint);

    wholeRay->push_back(m_rayFactory->createRay(reflectionPoint, point, line.angleTo(m_wall), m_epsilonWall));
    double this_speed = speed;
    if (m_movement.length() != 0.0){
        double angle = m_movement.angleTo(QLineF(reflectionPoint,point));
        this_speed += m_movement.length()*cos(angle*M_PI/180.0);
    }

    m_parent->notifyParent(productObservable,this_speed ,reflectionPoint,wholeRay);
}

QPointF TxImg::getPosition() const {
    return *this;
}


void TxImg::notifyCarDetected()
{
    m_parent->notifyCarDetected();
}


//bool TxImg::inIlluminatedCars(MathematicalCarProduct *car, int *idx)
//{
//    for (unsigned i = 0; i < m_illuminatedCars.size(); i++) {
//        if (m_illuminatedCars.at(i) == car) {
//            *idx = i;
//            return true;
//        }
//    }
//    return false;
//}


void TxImg::carMoved(MathematicalCarProduct *car, int /*x*/, int /*y*/, double /*orientation*/)
{
    int idx = 0;
    if (m_zone.intersects(*car)) {

        m_illuminatedCars.push_back(car);
        m_parent->notifyCarDetected();

    } else if (inIlluminatedCars(car, &idx)) {

        m_illuminatedCars.erase(m_illuminatedCars.begin() + idx);
        m_parent->notifyCarDetected();
    }
}
