#include "mathematicaltreeproduct.h"

MathematicalTreeProduct::MathematicalTreeProduct(TreeProduct* graphic)
//    m_factory(factory)
{
    setTreeProduct(graphic);
}

MathematicalTreeProduct::~MathematicalTreeProduct(){

}

void MathematicalTreeProduct::newProperties(){
    //m_factory->receiveTreeProduct(this,m_graphic);
}

int MathematicalTreeProduct::getPosX(){
    return m_posx;
}

int MathematicalTreeProduct::getPosY(){
    return m_posy;
}

TreeProduct *MathematicalTreeProduct::getTreeProduct(){
    return m_graphic;
}

void MathematicalTreeProduct::setPosX(int posX){
    m_posx = posX;
}

void MathematicalTreeProduct::setPosY(int posY){
    m_posy = posY;
}

void MathematicalTreeProduct::setTreeProduct(TreeProduct* graphic){
    m_graphic = graphic;
    setPosX(graphic->getPosX());
    setPosY(graphic->getPosY());
}

MathematicalComponent* MathematicalTreeProduct::toMathematicalComponent(){
    return this;
}
