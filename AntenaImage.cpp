#include "AntenaImage.h"

AntenaImage::AntenaImage(const Line &wall, AbstractAntena *parent):
    QPointF(),m_wall(wall),m_parent(parent)
{
    QPointF pos = m_wall.symetricalPoint(parent->getPosition());
    setX(pos.x()); setY(pos.y());
    //QPointF(m_wall.symetricalPoint(parent->getPosition()));
}

QPolygonF AntenaImage::getIlluminationZone() const
{
    QPolygonF zone;
    QLineF line1(*this,m_wall.p2());
    line1.setLength(50000);
    QLineF line2(*this,m_wall.p1());
    line2.setLength(50000);
    zone<<m_wall.p2()<<line1.p2()<<line2.p2()<<m_wall.p1();
    return zone.intersected(m_sceneBoundary);
}

QPolygonF AntenaImage::getIlluminationZone(const QRectF &rect)const {
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
QPolygonF AntenaImage::getIlluminatedZone()const{
    return m_zone;
}

void AntenaImage::setIlluminatedZone(const QPolygonF &zone){
    m_zone = zone;
}

void AntenaImage::notifyObserver(const QPointF &pos){

}

void AntenaImage::notifyParent(const QPointF &point){

}

QPointF AntenaImage::getPosition() const {
    return *this;
}

void AntenaImage::setBuilding(Building *building){
    m_building = building;
}

void AntenaImage::setSceneBoundary(const QRectF &rect){
    m_sceneBoundary = rect;
}

QPointF AntenaImage::sceneRectIntersection(const QRectF &rect, const QLineF  &line)const{
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

vector <QPointF> AntenaImage::boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const{
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
