#include "transmitterimage.h"

TransmitterImage::TransmitterImage(const Line &wall, AbstractAntena *parent):
    QPointF(),m_wall(wall),m_parent(parent),m_radius(500)
{
    QPointF pos = m_wall.symetricalPoint(parent->getPosition());
    setX(pos.x()); setY(pos.y());
    m_zone = buildCoverage();
}

QPointF TransmitterImage::sceneRectIntersection(const QRectF &rect, const QLineF  &line)const{
    /*
     * This function takes a bounding ray (line) of the illumination zone and gives its intersection
     * with the scene boundaries.
     */

    QLineF boundary1(rect.topLeft(),rect.bottomLeft()),
            boundary2(rect.bottomLeft(),rect.bottomRight()),
            boundary3(rect.bottomRight(),rect.topRight()),
            boundary4(rect.topRight(),rect.topLeft());

    QPointF intersectionPoint;

    if(line.intersect(boundary1,&intersectionPoint) == 1){}
    else if(line.intersect(boundary2,&intersectionPoint) == 1){}
    else if(line.intersect(boundary3,&intersectionPoint) == 1){}
    else if(line.intersect(boundary4,&intersectionPoint) == 1){}
    return intersectionPoint;
}

vector <QPointF> TransmitterImage::boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const{
    /*
     * Gives the corners of the scene bounding rectangle that lie in the ubounded illumination zone.
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

//void TransmitterImage::setBuilding(MathematicalBuildingProduct *building){
//    m_building = building;
//}

void TransmitterImage::setSceneBoundary(const QRectF &rect){
    m_sceneBoundary = rect;
}

QPolygonF TransmitterImage::buildCoverage(){
    QPolygonF coverage;
    QLineF line = m_wall;
    line.setLength(line.length()/2);
//    for(int i=0;i<16;i++){
//        coverage<<QPointF(x()+m_radius*cos(M_PI*i/8),y()+m_radius*sin(M_PI*i/8));
//    }

    for(int i=0;i<16;i++){
        coverage<<QPointF(line.p2().x()+m_radius*cos(M_PI*i/8),line.p2().y()+m_radius*sin(M_PI*i/8));
    }
    return coverage;
}

QPolygonF TransmitterImage::getIlluminationZone() const
{
    QPolygonF zone;
    QLineF line1(*this,m_wall.p2());
    line1.setLength(50000);
    QLineF line2(*this,m_wall.p1());
    line2.setLength(50000);
    zone<<m_wall.p2()<<line1.p2()<<line2.p2()<<m_wall.p1();
//    return zone.intersected(m_sceneBoundary);
    return zone.intersected(m_zone);
    //return m_zone;
}

QPolygonF TransmitterImage::getIlluminationZone(const QRectF &rect)const {
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

void TransmitterImage::update(ProductObservable *productObservable, QLineF const movement){


    if(m_zone.containsPoint(*productObservable->getPos(),Qt::OddEvenFill)){
        vector<MathematicalRayProduct*> *wholeRay = new vector<MathematicalRayProduct*>;
        QLineF line(*this,*productObservable->getPos());
        QPointF reflectionPoint;
        m_wall.intersect(line,&reflectionPoint);

//        MathematicalRayProduct newRay(reflectionPoint,pos,line.angleTo(m_wall));
        MathematicalRayProduct ray(*m_rayFactory->createRay(reflectionPoint,
                                                            *productObservable->getPos(),
                                                            line.angleTo(m_wall)));

//        cout<<"Reflected ray: "<<ray.p1().x()<<", "<<ray.p1().y()
//             <<" and p2 = "<<ray.p2().x()<<", "<<ray.p2().y()<<endl;

        wholeRay->push_back(m_rayFactory->createRay(reflectionPoint,
                                                    *productObservable->getPos(),
                                                    line.angleTo(m_wall)));

        m_parent->notifyParent(productObservable,m_movement, reflectionPoint,wholeRay);
    }
}

void TransmitterImage::attachObservable(ProductObservable* productObservable){
    m_observable.push_back(productObservable);
}

void TransmitterImage::notifyParent(ProductObservable *productObservable,
                                    QLineF const movement, const QPointF &point,
                                    vector<MathematicalRayProduct*> *wholeRay)
{
    QLineF line(*this,point);
    QPointF reflectionPoint;
    m_wall.intersect(line,&reflectionPoint);
//    MathematicalRayProduct newRay(reflectionPoint,point,line.angleTo(m_wall));
//    wholeRay->push_back(newRay);
    wholeRay->push_back(m_rayFactory->createRay(reflectionPoint,point,line.angleTo(m_wall)));
    QPointF p0 = m_movement.p1();
    QPointF p1 = m_movement.p2();
    QPointF p0_prime = movement.p1();
    QPointF p1_prime = movement.p2();
    if (m_wallType == Wall::front) {
        m_movement = QLineF(p0,p1_prime-p1);
    } else if (m_wallType == Wall::back) {
        m_movement = QLineF(p0,p1_prime+p1);
    }

    m_parent->notifyParent(productObservable,m_movement ,reflectionPoint,wholeRay);
}

QPointF TransmitterImage::getPosition() const {
    return *this;
}
