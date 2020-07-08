#include "mathematicalreceiverproduct.h"

MathematicalReceiverProduct::MathematicalReceiverProduct(int posX, int posY): QPointF(posX,posY)
{
    m_type = "Receiver";
    m_power = 0.0;
    m_e_field = 0.0;
    // Enable the setters of position. Can mathematical product move ?
    enable = true;
    m_target_snr = 8; // [dB]
    m_noise_figure = 10; // [dB]
    m_interferencemargin = 6; // [dB]
    computeMinPrx();
}

MathematicalReceiverProduct::~MathematicalReceiverProduct(){

}

void MathematicalReceiverProduct::clearData(){
    m_power = 0;
    m_e_field = 0;
}

double MathematicalReceiverProduct::inputNoise(){
    return 10*log10(kb*To*m_transmitterbandwidth);
}

void MathematicalReceiverProduct::computeMinPrx(){
    min_prx = m_target_snr + m_noise_figure + inputNoise() + m_interferencemargin + 30; // [dBm]
}

// 1. Path Loss Computation:
void MathematicalReceiverProduct::setPathLoss(std::map<double, double> pathloss){
    m_pathloss = pathloss;
    computePathLossFading();
    modelPathLoss();
}

void MathematicalReceiverProduct::computePathLossFading(){
    path_loss.resize(m_pathloss.size());
    fading.resize(m_pathloss.size());
    linearRegressionPathLoss();
    for (unsigned long i=0; i<(m_pathloss.size()); ++i){
        path_loss[i] = m*logD[i]+b;
        fading[i] = Prx[i]-path_loss[i];
    }
    fading_variability = standardDeviation();
}

void MathematicalReceiverProduct::linearRegressionPathLoss(){
/*
*b = output intercept
*m  = output slope
*r = output correlation coefficient (can be NULL if you don't want it)
*/
    logD.resize(m_pathloss.size());
    Prx.resize(m_pathloss.size());
    D.resize(m_pathloss.size());
    int i = 0;
    for(const auto &path : m_pathloss){
        D[i] = path.first;
        logD[i] = log10(D[i]);
        Prx[i] = path.second;
        i++;
    }

    double   sumx = 0.0;                      /* sum of x     */
    double   sumx2 = 0.0;                     /* sum of x**2  */
    double   sumxy = 0.0;                     /* sum of x * y */
    double   sumy = 0.0;                      /* sum of y     */
    double   sumy2 = 0.0;                     /* sum of y**2  */

    for (unsigned long i=0;i<m_pathloss.size();i++){
        sumx  += logD[i];
        sumx2 += pow(logD[i],2);
        sumxy += logD[i] * Prx[i];
        sumy  += Prx[i];
        sumy2 += pow(Prx[i],2);
    }

    double denom = (m_pathloss.size() * sumx2 - pow(sumx,2));
    if (denom == 0) {
        // singular matrix. can't solve the problem.
        m = 0;
        b = 0;
        if (r) r = 0;
    }
    else{
        m = (m_pathloss.size() * sumxy  -  sumx * sumy) / denom;
        b = (sumy * sumx2  -  sumx * sumxy) / denom;
        if (r != 0.0) {
            r = (sumxy - sumx * sumy / m_pathloss.size()) /    /* compute correlation coeff */
            sqrt((sumx2 - pow(sumx,2)/m_pathloss.size()) *
            (sumy2 - pow(sumy,2)/m_pathloss.size()));
        }
    }
}

double MathematicalReceiverProduct::standardDeviation(){
    double sum = 0.0, sDeviation = 0.0, mean;
    int count = fading.size();
    int i;
    for(i = 0; i < count; i++) {
        sum += fading[i];
    }
    // Calculating mean
    mean = sum/count;
    for(i = 0; i < count; ++i) {
        sDeviation += pow(fading[i] - mean, 2);
    }
    double res = sqrt(sDeviation/count);
    if(res<1e-5){res = 0;}
    return res;
}

void MathematicalReceiverProduct::modelPathLoss(){
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, fading_variability);
    double minDist = log10(10); //10m
    double maxDist = log10(5000);// 5km
    double step = 0.01;
    int lengthData = (maxDist-minDist)/step;
    D_model.resize(lengthData);
    logD_model.resize(lengthData);
    Prx_model.resize(lengthData);
    path_loss_model.resize(lengthData);
    //threshold(lengthData);
    double L_fading_model;
    for (int i=0; i<lengthData; ++i){
        logD_model[i] = minDist + i*step;
        D_model[i] = pow(10, logD_model[i]);
        path_loss_model[i] =  m*logD_model[i] + b;
        L_fading_model = distribution(generator);
        Prx_model[i] = path_loss_model[i] + L_fading_model;
        //threshold[i] = minPrx;
    }
}


// From ReceiverProduct
int MathematicalReceiverProduct::getPosX(){return x();}
int MathematicalReceiverProduct::getPosY(){return y();}
double MathematicalReceiverProduct::getPower() {return m_power;}
complex <double> MathematicalReceiverProduct::getEField() {return m_e_field;}
bool MathematicalReceiverProduct::getEnable() {return enable;}

void MathematicalReceiverProduct::setPosX(int posX) {
    clearData();
    setX(posX);
    m_graphic->notifyToGraphic(this, m_power);
    notifyObservers();
}
void MathematicalReceiverProduct::setPosY(int posY) {
    clearData();
    setY(posY);
    m_graphic->notifyToGraphic(this);
    notifyObservers();
}
void MathematicalReceiverProduct::setPower(double p) {m_power = p;}
void MathematicalReceiverProduct::setEField(complex<double> e) {m_e_field = e;}
void MathematicalReceiverProduct::setEnable(bool enable) {this->enable = enable;}

void MathematicalReceiverProduct::newProperties(){
    computeMinPrx();
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

//    cout<< "MathRec number of observers: "<< m_observers.size()<<endl;
    for(int i = 0;i<m_observers.size();i++){
//        cout<< "MathRec position: "<<x()<<", "<<y()<<endl;
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
    if(m_power < power - 20 && observer != m_transmitter){
        m_power = power;
        m_graphic->notifyToGraphic(this,m_power);
        if(m_transmitter!=nullptr){
            m_transmitter->drawRays(this,false);
        }
        m_transmitter = observer;
        m_transmitter->drawRays(this,true);
    }
    else{
        m_power = power;
        m_graphic->notifyToGraphic(this,m_power);
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
