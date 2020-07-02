#include "mathematicalreceiverproduct.h"

MathematicalReceiverProduct::MathematicalReceiverProduct(int posX, int posY): QPointF(posX,posY)
{
    m_type = "Receiver";
    m_power = 0.0;
    m_e_field = 0.0;
    // Enable the setters of position. Can mathematical product move ?
    enable = true;
}

MathematicalReceiverProduct::~MathematicalReceiverProduct(){

}

// From ReceiverProduct
int MathematicalReceiverProduct::getPosX(){return x();}
int MathematicalReceiverProduct::getPosY(){return y();}
double MathematicalReceiverProduct::getPower() {return m_power;}
complex <double> MathematicalReceiverProduct::getEField() {return m_e_field;}
bool MathematicalReceiverProduct::getEnable() {return enable;}

void MathematicalReceiverProduct::setPosX(int posX) {setX(posX);}
void MathematicalReceiverProduct::setPosY(int posY) {setY(posY);}
void MathematicalReceiverProduct::setPower(double p) {m_power = p;}
void MathematicalReceiverProduct::setEField(complex<double> e) {m_e_field = e;}
void MathematicalReceiverProduct::setEnable(bool enable) {this->enable = enable;}

void MathematicalReceiverProduct::newProperties(){
    m_graphic->notifyToGraphic(this);
}

// From MathematicalProduct
void MathematicalReceiverProduct::openDialog(){
    new DialogReceiverProduct(this);
}

void MathematicalReceiverProduct::update(QGraphicsItem* graphic){
    setX(graphic->scenePos().x());
    setY(graphic->scenePos().y());
    notifyObservers();
}

// From ProductObservable
void MathematicalReceiverProduct::attachObserver(ProductObserver *productObserver){
    //cout<<"Observevr attached"<<endl;
    m_observers.push_back(productObserver);
}

void MathematicalReceiverProduct::notifyObservers(){

//    foreach(ProductObserver* observer, m_observers){
//        observer->notify(this,m_speed,m_orientation);
//    }

    for(int i = 0;i<m_observers.size();i++){
        m_observers.at(i)->update(this,m_speed,m_orientation);
    }

//    for(int i = m_observers.size()-1;i>=0;i--){
//        cout<<"Observer notified 1"<<endl;
//        m_observers.at(i)->notify(*this);
//        cout<<"Observer notified 2"<<endl;
//    }
}

void MathematicalReceiverProduct::notify(){
    notifyObservers();
}

void MathematicalReceiverProduct::notify(double &power, std::vector<double> *powers, std::complex<double> &EMfiled){

}

void MathematicalReceiverProduct::answer(ProductObserver *observer, double &power, std::vector<double> *powers, std::complex<double> &EMfield){
    m_e_field += EMfield;
    if(m_power < power && observer != m_transmitter){
        m_power = power;
        if(m_transmitter!=nullptr){
            m_transmitter->drawRays(this,false);
        }
        m_transmitter = observer;
        m_transmitter->drawRays(this,true);
    }
    else{
        m_power = power;
        if(m_transmitter != 0){
            m_transmitter->drawRays(this,true);
        }
        else{
            m_transmitter = observer;
        }
    }

}

QPointF* MathematicalReceiverProduct::getPos(){
    return this;
}
