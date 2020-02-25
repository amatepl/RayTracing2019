#include "mathematicalcarproduct.h"

MathematicalCarProduct::MathematicalCarProduct(CarProduct* graphic, MathematicalFactory* factory){
    cout << "New Car" << endl;
    m_mathematicalfactory = factory;
    setCarProduct(graphic);
}

MathematicalCarProduct::~MathematicalCarProduct(){
    m_mathematicalfactory->receiveCarProduct(this,m_graphic);
}

void MathematicalCarProduct::newProperties(){

}

int MathematicalCarProduct::getPosX(){
    return m_posx;
}

int MathematicalCarProduct::getPosY(){
    return m_posy;
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

void MathematicalCarProduct::setPosX(int posX){
    m_posx = posX;
    setX(posX);
}

void MathematicalCarProduct::setPosY(int posY){
    m_posy = posY;
    setY(posY);
}

void MathematicalCarProduct::setSpeed(double speed){
    m_speed = speed;
}

void MathematicalCarProduct::setOrientation(double orientation){
    m_orientation = orientation;
}

void MathematicalCarProduct::setCarProduct(CarProduct* graphic){
    cout << "I have changed" << endl;
    m_graphic = graphic;
    setPosX(graphic->getPosX());
    setPosY(graphic->getPosY());
    setOrientation(graphic->getOrientation());
    setSpeed(graphic->getSpeed());
}
