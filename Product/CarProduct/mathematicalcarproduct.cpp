#include "mathematicalcarproduct.h"

MathematicalCarProduct::MathematicalCarProduct(QRectF rect)
{
    setRect(rect.topLeft().x(),rect.topLeft().y(),rect.width(),rect.height());
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

CarProduct* MathematicalCarProduct::getCarProduct(){
    return m_graphic;
}

void MathematicalCarProduct::setSpeed(double speed){
    m_speed = speed;
}

void MathematicalCarProduct::setOrientation(double orientation){
    m_orientation = orientation;
}

void MathematicalCarProduct::update(QGraphicsItem *graphic){
    setX(graphic->x());
    setY(graphic->y());
}

void MathematicalCarProduct::openDialog(){

}
