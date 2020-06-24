#include "mathematicalreceiverproduct.h"

MathematicalReceiverProduct::MathematicalReceiverProduct(int posX, int posY)
{
    setX(posX);
    setY(posY);
    m_type = "Receiver";
}

MathematicalReceiverProduct::~MathematicalReceiverProduct(){

}

void MathematicalReceiverProduct::update(QGraphicsItem* graphic){
    setX(graphic->scenePos().x());
    setY(graphic->scenePos().y());
    notifyObservers();
}

void MathematicalReceiverProduct::attachObserver(ProductObserver *productObserver){
    cout<<"Observevr attached"<<endl;
    m_observers.push_back(productObserver);
}

void MathematicalReceiverProduct::notifyObservers(){
    cout<<m_observers.size()<<endl;
    foreach(ProductObserver* observer, m_observers){
        cout<<"Observer not yet notified"<<endl;
        observer->notify(*this);
        cout<<"Observer notified"<<endl;
    }
}
