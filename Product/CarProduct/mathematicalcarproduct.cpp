#include "mathematicalcarproduct.h"

MathematicalCarProduct::MathematicalCarProduct(QPolygonF rect, QPointF center): MathematicalBuildingProduct(rect),
    m_center(center)
{
    //setRect(round(rect.topLeft().x()),round(rect.topLeft().y()),rect.width(),rect.height());
    m_type = "Car";
    m_walls.at(0)->setWallType(Wall::back);
    m_walls.at(0)->setSpeed(m_speed);
    m_walls.at(0)->setOrientation(m_orientation);

    m_walls.at(2)->setWallType(Wall::front);
    m_walls.at(2)->setSpeed(m_speed);
    m_walls.at(2)->setOrientation(m_orientation);
//    cout<<"Size of car: "<<this->size()<<endl;
//    cout<<"Number of walls: "<<m_walls.size()<<endl;
//    cout<<"First wall point: "<< m_walls.at(0)->p1().x()<<", "<< m_walls.at(0)->p1().y()<<endl;
}

MathematicalCarProduct::~MathematicalCarProduct(){

}


void MathematicalCarProduct::moveCar(){
    //while(true){
//    cout<<m_street.dx()/m_street.length()<<endl;
        setPosX(getPosX() + 1);//m_street.dx()/m_street.length());
        setPosY(getPosY() + m_street.dy()/m_street.length());
//        this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout<<getPosX()<<", "<<getPosY()<<endl;
        //m_graphic->notifyToGraphic(this,getPosX(),getPosY(),m_orientation);
        //emit positionChanged(this,getPosX(),getPosY(),m_orientation);
        //emit signal();
    //}
}

void MathematicalCarProduct::setRoad(QLineF &road){
    m_street = road;
}


void MathematicalCarProduct::setMovement(QLineF( &vect))
{
    m_movement = vect;
    m_speed = vect.length();
    m_orientation = vect.angle();
    m_walls.at(0)->setSpeed(m_speed);
    m_walls.at(0)->setOrientation(m_orientation);

    m_walls.at(2)->setSpeed(m_speed);
    m_walls.at(2)->setOrientation(m_orientation);
}


QLineF MathematicalCarProduct::getMovement()
{
    return m_movement;
}


void MathematicalCarProduct::attachObservable(GraphicsProduct *graphic){
    m_graphic = graphic;
//    QObject::connect(dynamic_cast<QObject*>(this),
//                     SIGNAL(&MathematicalCarProduct::positionChanged),
//                     dynamic_cast<QObject*>(m_graphic),
//                     SLOT(&GraphicsProduct::notifyToGraphicSig),Qt::QueuedConnection);
}


double MathematicalCarProduct::getSpeed(){
    return m_speed;
}


double MathematicalCarProduct::getOrientation(){
    return m_orientation;

}


void MathematicalCarProduct::setSpeed(double speed){
    m_speed = speed;
}


int MathematicalCarProduct::getPosX(){
    return m_center.x();
}


int MathematicalCarProduct::getPosY(){
    return m_center.y();
}


void MathematicalCarProduct::setOrientation(double orientation){
    m_orientation = orientation;
}


void MathematicalCarProduct::setPosX(int posX){
    QPointF offset = QPointF(posX,getPosY()) - m_center;
    m_center.setX(posX);
    translate(offset);
}


void MathematicalCarProduct::setPosY(int posY){
    QPointF offset = QPointF(getPosX(),posY) - m_center;
    m_center.setY(posY);
    translate(offset);
}


void MathematicalCarProduct::update(QGraphicsItem *graphic){
    //QRectF rect = graphic->sceneBoundingRect();
//    QPolygonF polyRect = QPolygonF(rect);
//    swap(polyRect);
//    m_extremities = polyRect;
//    m_center = graphic->pos();
}


void MathematicalCarProduct::openDialog(){
    new DialogCarProduct(this);
}


void MathematicalCarProduct::newProperties(){
    m_graphic->notifyToGraphicSig(this, getPosX(), getPosY(),getOrientation());
}
