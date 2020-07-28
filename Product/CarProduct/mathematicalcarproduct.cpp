#include "mathematicalcarproduct.h"

MathematicalCarProduct::MathematicalCarProduct(QPolygonF rect, QPointF center):
    MathematicalBuildingProduct(rect), m_center(center)
{
    //setRect(round(rect.topLeft().x()),round(rect.topLeft().y()),rect.width(),rect.height());
    m_type = "Car";
    m_walls.at(0)->setWallType(Wall::back);
    m_walls.at(0)->setMovement(m_movement);

    m_walls.at(2)->setWallType(Wall::front);
    m_walls.at(2)->setMovement(m_movement);

}

MathematicalCarProduct::~MathematicalCarProduct(){
    cout << "Mathematical Car Product Deleted." << endl;
}


void MathematicalCarProduct::runCar()
{
    std::thread *thread_obj = new std::thread (&MathematicalCarProduct::moveCar);
}


void MathematicalCarProduct::moveCar(){
    while(true){
//    cout<<m_street.dx()/m_street.length()<<endl;
//        setPosX(getPosX() + m_street.dx()/m_street.length());
//        setPosY(getPosY() + m_street.dy()/m_street.length());
//        this_thread::sleep_for(std::chrono::milliseconds(1000));
//        cout<<getPosX()<<", "<<getPosY()<<endl;
        //m_graphic->notifyToGraphic(this,getPosX(),getPosY(),m_orientation);
        //emit positionChanged(this,getPosX(),getPosY(),m_orientation);
        //emit signal();
    }
}

void MathematicalCarProduct::setRoad(QLineF &road){
    m_street = road;
}


void MathematicalCarProduct::setMovement(QLineF( &vect))
{
    m_movement = vect;
    m_walls.at(0)->setMovement(m_movement);

    m_walls.at(2)->setMovement(m_movement);
    newProperties();
}


QLineF MathematicalCarProduct::getMovement()
{
    return m_movement;
}

void MathematicalCarProduct::setPos(QPointF pos)
{
    QPointF offset = pos - m_center;
    m_center = pos;
    translate(offset);
    moveWalls(offset);
    emit positionChanged(this,getPosX(),getPosY(),getOrientation());
}

QPointF MathematicalCarProduct::getPos() const
{
    return m_center;
}

void MathematicalCarProduct::attachObservable(GraphicsProduct *graphic)
{
    m_graphic = graphic;
    QObject::connect(this,
                     &MathematicalCarProduct::positionChanged,
                     dynamic_cast<MoveableGraphics *>(m_graphic),
                     &MoveableGraphics::notifyToGraphicSig,Qt::QueuedConnection);
}


double MathematicalCarProduct::getSpeed(){
    return m_movement.length();
}


double MathematicalCarProduct::getOrientation(){
    return m_movement.angle();

}


void MathematicalCarProduct::setSpeed(double speed){
    m_movement.setLength(speed);
    setMovement(m_movement);
}


int MathematicalCarProduct::getPosX(){
    return m_center.x();
}


int MathematicalCarProduct::getPosY(){
    return m_center.y();
}


void MathematicalCarProduct::setOrientation(double orientation){
    QLineF tmpLine(QPointF(0.0,0.0),QPointF(22.0,0.0));
    tmpLine.setAngle(orientation);
    tmpLine.translate(m_center-tmpLine.center());
    m_movement.setAngle(orientation);
    QLineF normal = tmpLine.normalVector();
    normal.setLength(11);

    QPolygonF carContour;
    carContour << normal.p2();
    normal.translate(normal.p1() - normal.p2());
    carContour << normal.p1();
    normal.translate(tmpLine.p2() - tmpLine.p1());
    carContour << normal.p1();
    normal.translate(normal.p2() - normal.p1());
    carContour << normal.p2();
    carContour<< carContour.at(0);

    swap(carContour);
    for(int i =0; i<size()-1;i++){
        m_walls.at(i)->setPoints(this->at(i),this->at(i+1));
    }
    m_walls.at(0)->setWallType(Wall::back);
    m_walls.at(0)->setMovement(m_movement);

    m_walls.at(2)->setWallType(Wall::front);
    m_walls.at(2)->setMovement(m_movement);
    emit positionChanged(this,getPosX(),getPosY(),getOrientation());
}


void MathematicalCarProduct::setPosX(int posX){
    QPointF offset = QPointF(posX,getPosY()) - m_center;
    m_center.setX(posX);
    translate(offset);
    moveWalls(offset);
    emit positionChanged(this,getPosX(),getPosY(),getOrientation());
}


void MathematicalCarProduct::setPosY(int posY){
    QPointF offset = QPointF(getPosX(),posY) - m_center;
    m_center.setY(posY);
    translate(offset);
    moveWalls(offset);
    emit positionChanged(this,getPosX(),getPosY(),getOrientation());
}


void MathematicalCarProduct::update(QGraphicsItem *graphic){
    QPointF offset = graphic->scenePos() - m_center;
    translate(offset);
    moveWalls(offset);
    //QRectF rect = graphic->sceneBoundingRect();
//    QPolygonF polyRect = QPolygonF(rect);
//    swap(polyRect);
//    m_extremities = polyRect;
    m_center = graphic->scenePos();
}


void MathematicalCarProduct::openDialog(){
    new DialogCarProduct(this);
}


void MathematicalCarProduct::newProperties(){
    //m_graphic->notifyToGraphic(this, getPosX(), getPosY(), getOrientation());
}
