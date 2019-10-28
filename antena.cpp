#include "antena.h"

// Very basic Trasmitter type object

antena::antena(QPointF p, int type):
QGraphicsEllipseItem()/*,QPointF()*/,pos(p),antenaType(type),m_vector(QPointF(1,1))

{
    m_building = nullptr;

    this->setRect(pos.x(),pos.y(),1,1);
    // 0 for output (transmiter) 1 for input (receiver)
    //myRoom = scene;
    QBrush noBrush(Qt::NoBrush);

    this->setBrush(noBrush);
    this->setPen(setColor());

    //myRoom->addItem(this);
}

antena::~antena(){

}


QPen antena::setColor(){

    /*
     * Changes the color according to the Trasmitter type, for more display visibility
     */

    QPen pen;
    if(antenaType == 0){
         QPen outlinePen(Qt::red);
          outlinePen.setWidth(2);
         pen = outlinePen;
    }
    else{
        QPen outlinePen(Qt::blue);
         outlinePen.setWidth(2);
        pen = outlinePen;
    }
    return pen;
}

// --> Getters && Setters

int antena::getPosX(){return pos.x();}
//int Trasmitter::getPosX(){return this->x();}
int antena::getPosY(){return pos.y();}
QPointF antena::getPos()const{return pos;}

void antena::setPosi(QPointF posi){this->pos = posi;
            this->setRect(posi.x(),posi.y(),1,1);
            }

QPolygonF antena::getIlluminationZone(const QRectF &rect)const{
    QPolygonF iluminationZone;
    QPolygonF unboundedZone;
    // Roation matrix is applied for 60 deg.
    QPointF point2((0.5*m_vector.x() - 0.866*m_vector.y())*5000,(0.5*m_vector.y() + 0.866*m_vector.x())*5000);
    QPointF point3((0.5*m_vector.x() + 0.866*m_vector.y())*5000,(0.5*m_vector.y() - 0.866*m_vector.x())*5000);

    cout<<"Rect bottom right: " <<rect.bottomRight().x()<<", "<<rect.bottomRight().y()<<endl;
    cout<<"Rect top left: " <<rect.topLeft().x()<<", "<<rect.topLeft().y()<<endl;

    unboundedZone<<pos<<point2+pos<<point3+pos;

    iluminationZone<<pos
                  << sceneRectIntersection(rect,QLineF(pos,pos+point2));

    for (QPointF p: boundaryCorners(rect,unboundedZone)) {
        iluminationZone<<p;
    }

    iluminationZone<<sceneRectIntersection(rect,QLineF(pos,pos+point3));

    return iluminationZone;
}

QPolygonF antena::getIlluminationZone()const{

    /*
     * This method is used right now in the code BUT we've got to make sure that the user don't add
     * any element to the scene once the antena is set.
     */

    QPolygonF iluminationZone;
    QPolygonF unboundedZone;
    // Roation matrix is applied for 60 deg.
    QPointF point2((0.5*m_vector.x() - 0.866*m_vector.y())*5000,(0.5*m_vector.y() + 0.866*m_vector.x())*5000);
    QPointF point3((0.5*m_vector.x() + 0.866*m_vector.y())*5000,(0.5*m_vector.y() - 0.866*m_vector.x())*5000);

    //cout<<"Rect bottom right: " <<m_sceneBoundary.bottomRight().x()<<", "<<m_sceneBoundary.bottomRight().y()<<endl;
    //cout<<"Rect top left: " <<m_sceneBoundary.topLeft().x()<<", "<<m_sceneBoundary.topLeft().y()<<endl;

    unboundedZone<<pos<<point2+pos<<point3+pos;

    iluminationZone<<pos
                  << sceneRectIntersection(m_sceneBoundary,QLineF(pos,pos+point2));

    for (QPointF p: boundaryCorners(m_sceneBoundary,unboundedZone)) {
        iluminationZone<<p;
    }

    iluminationZone<<sceneRectIntersection(m_sceneBoundary,QLineF(pos,pos+point3));

    return iluminationZone;
}

QPolygonF antena::getIlluminatedZone()const{
    return m_zone;
}


void antena::setSceneBoundary(const QRectF &rect){
    m_sceneBoundary = rect;
}

QPointF antena::sceneRectIntersection(const QRectF &rect, const QLineF  &line)const{
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

vector <QPointF> antena::boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const{
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

void antena::notifyParent(const QPointF &point) {}

QPointF antena::getPosition()const {
    return getPos();
}

void antena::setIlluminatedZone(const QPolygonF &zone){
    m_zone = zone;
}
