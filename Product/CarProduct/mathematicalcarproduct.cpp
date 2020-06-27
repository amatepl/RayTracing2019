#include "mathematicalcarproduct.h"

MathematicalCarProduct::MathematicalCarProduct(QPolygonF rect, QPointF center): QPolygonF(rect),
    m_center(center)
{
    //setRect(round(rect.topLeft().x()),round(rect.topLeft().y()),rect.width(),rect.height());
    m_type = "Car";
}

MathematicalCarProduct::~MathematicalCarProduct(){

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
    QRectF rect = graphic->sceneBoundingRect();
    QPolygonF polyRect = QPolygonF(rect);
    swap(polyRect);
    m_center = graphic->pos();
}

void MathematicalCarProduct::openDialog(){
    new DialogCarProduct(this);
}

void MathematicalCarProduct::newProperties(){
    m_graphic->notifyToGraphic(this, getPosX(), getPosY(),getOrientation());
}
