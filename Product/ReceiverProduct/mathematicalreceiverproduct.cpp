#include "mathematicalreceiverproduct.h"

MathematicalReceiverProduct::MathematicalReceiverProduct(ReceiverProduct* graphic, MathematicalFactory* factory)
{
    setReceiverProduct(graphic);
    m_mathematicalfactory = factory;
}

MathematicalReceiverProduct::~MathematicalReceiverProduct(){

}

void MathematicalReceiverProduct::newProperties(){
    m_mathematicalfactory->receiveReceiverProduct(this,m_graphic);
}

int MathematicalReceiverProduct::getPosX(){
    return m_posx;
}

int MathematicalReceiverProduct::getPosY(){
    return m_posy;
}

double MathematicalReceiverProduct::getPower(){
    return m_power;
}
unsigned long MathematicalReceiverProduct::getFrequency(){
    return m_frequency;
}

ReceiverProduct* MathematicalReceiverProduct::getReceiverProduct(){
    return m_graphic;
}

void MathematicalReceiverProduct::setPosX(int posX){
    m_posx = posX;
    setX(m_posx);
}

void MathematicalReceiverProduct::setPosY(int posY){
    m_posy = posY;
    setY(m_posy);
}

void MathematicalReceiverProduct::setFrequency(unsigned long frequency){
    m_frequency = frequency;
}

void MathematicalReceiverProduct::setReceiverProduct(ReceiverProduct* graphic){
    m_graphic = graphic;
    setPosX(graphic->getPosX());
    setPosY(graphic->getPosY());
    setFrequency(graphic->getFrequency());
}
