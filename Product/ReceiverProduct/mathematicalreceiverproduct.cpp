#include "mathematicalreceiverproduct.h"

MathematicalReceiverProduct::MathematicalReceiverProduct(int posX, int posY)
{
    setX(posX);
    setY(posY);
}

MathematicalReceiverProduct::~MathematicalReceiverProduct(){

}

void MathematicalReceiverProduct::update(QGraphicsItem* graphic){
    setX(graphic->scenePos().x());
    setY(graphic->scenePos().y());
}

void MathematicalReceiverProduct::attachObserver(ProductObserver *productObserver){
    m_observers.push_back(productObserver);
}
