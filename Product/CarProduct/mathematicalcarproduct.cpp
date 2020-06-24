#include "mathematicalcarproduct.h"

MathematicalCarProduct::MathematicalCarProduct(int posX, int posY): QRectF(0,0,posX,posY)
{

}

MathematicalCarProduct::~MathematicalCarProduct(){
    //m_mathematicalfactory->receiveCarProduct(this,m_graphic);
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

}
