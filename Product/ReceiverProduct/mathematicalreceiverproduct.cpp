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
    //cout<<"Observevr attached"<<endl;
    m_observers.push_back(productObserver);
}

void MathematicalReceiverProduct::notifyObservers(){

    foreach(ProductObserver* observer, m_observers){
        observer->notify(*this);
    }

    for(int i = 0;i<m_observers.size();i++){
        m_observers.at(i)->notify(*this);
    }

//    for(int i = m_observers.size()-1;i>=0;i--){
//        cout<<"Observer notified 1"<<endl;
//        m_observers.at(i)->notify(*this);
//        cout<<"Observer notified 2"<<endl;
//    }
}

void MathematicalReceiverProduct::openDialog(){

}

void MathematicalReceiverProduct::notify(){
    notifyObservers();
}
