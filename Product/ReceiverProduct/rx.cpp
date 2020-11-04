#include "rx.h"

#include <algorithm>
#include "Share/physics.h"

Rx::Rx(int posX, int posY): QPointF(posX,posY)
{
    m_type                  = "Receiver";
    m_power                 = 0.0;
    m_e_field               = 0.0;
    m_transmitter_distance  = 0.0;
    snr_received            = 0.0;
    delay_spread            = 0.0;
    // Enable the setters of position. Can mathematical product move ?
    enable = true;
    m_target_snr            = 8;    // [dB]
    m_noise_figure          = 10;   // [dB]
    m_interferencemargin    = 6;    // [dB]

    computeMinPrx();
}

Rx::Rx(Rx* receiver): QPointF(receiver->getPosX(),receiver->getPosY())
{
    m_type = "Receiver";
    m_power = receiver->getPower();
    m_e_field = receiver->getEField();
    // Enable the setters of position. Can mathematical product move ?
    enable = receiver->getEnable();
    m_target_snr = receiver->targetSNR(); // [dB]
    m_noise_figure = receiver->noiseFigure(); // [dB]
    m_interferencemargin = receiver->interFerenceMargin(); // [dB]
    m_observers = receiver->m_observers;
    m_transmitters = receiver->m_transmitters;
    m_movement = receiver->m_movement;
    computeMinPrx();
}

Rx::~Rx()
{
    cout << "Mathematical Receiver Product Deleted." << endl;
    delete m_dialog;
}

void Rx::clearObeservers()
{
    m_observers.clear();
}

void Rx::clearData()
{
    m_power = 0;
    m_e_field = 0;
}

double Rx::inputNoise()
{
    return 10 * log10(k_b * t_0 * m_transmitterbandwidth);
}

void Rx::computeMinPrx()
{
    min_prx = m_target_snr + m_noise_figure + inputNoise() + m_interferencemargin + 30; // [dBm]
}


void Rx::computeSnr()
{
    if (m_power != 0.0){
        snr_received = (m_power - 30) - m_noise_figure - inputNoise(); // [dB]
    }
}


void Rx::computeDelaySpread()
{
    double min_tau, max_tau, t;
    int i = 0;
    for (const auto &imp: m_impulse) {
        t = imp.first;
        if (i == 0) {
            min_tau = t;
            max_tau = t;
        }
        else {
            if(t < min_tau){
                min_tau = t;
            }
            else if (t > max_tau) {
                max_tau = t;
            }
        }
        i++;
    }

    delay_spread = abs(max_tau-min_tau);

    if (delay_spread < 1e-20){
        delay_spread = 0.0;
    }
}


void Rx::coherenceBandwidth()
{
    coherence_bandwidth = 1e3 / delay_spread; //MHz
}


void Rx::attachTransmitter(ProductObserver *transmitter)
{
    m_transmitters.push_back(transmitter);
}


void Rx::extractChData()
{

    m_impulse = m_chData->impulseResp;
    m_doppler = m_chData->dopplerSpctr;
    riceFactor(m_chData->riceFactor);

    for (vector<complex<double>>::iterator ang = m_chData->angularDistr.begin();
         ang != m_chData->angularDistr.end();
         ang++) {
//        angular_distr[ang - m_chData->angularDistr.begin()] = 20*log10(abs(*ang));
        angular_distr.push_back(-20*log10(abs(*ang)));
    }
    if (m_movement.length() > 0){
        for (vector<complex<double>>::iterator dop = m_chData->dopplerDistr.begin();
             dop != m_chData->dopplerDistr.end();
             dop++) {
             doppler_distr.push_back(20*log10(abs(*dop)));
        }
    }
//    if (m_chData->angularDistr.size() > 0){
//        angular_distr = QVector<complex<double>>(m_chData->angularDistr.begin(), m_chData->angularDistr.end());
//    }

    if (m_chData->prxAngularSpctr.size() > 0) {
        pas = QVector<double>(m_chData->prxAngularSpctr.begin(), m_chData->prxAngularSpctr.end());
        pds = QVector<double>(m_chData->prxDopplerSpctr.begin(), m_chData->prxDopplerSpctr.end());
    }

    dB(pas);
//    dB(pds);

//    cout<<"Tmp prx [dB]: " <<20*log10(tmpPrx)<<", tmp prx: "<<tmpPrx<<", "<<m_power << endl;

//    for (complex<double> &ang: angular_distr) {
//        ang = 20*log10(abs(ang));
//    }

    angular_spread = m_chData->angularSpred;
    doppler_spread = m_chData->dopplerSpread;
    u = QVector<double>(m_chData->u.begin(), m_chData->u.end());
    w = QVector<double>(m_chData->w.begin(), m_chData->w.end());
}


void Rx::save(string path)
{
//    cout << "/Users/amate/Documents/Polytech/Thesis/powerTest.csv" <<endl;

//    std::ofstream ofs (path);
    std::ofstream ofs;
    ofs.open(path, std::ios_base::app | std::ios_base::out);

    vector<unsigned> vectorSizes;

//    vectorSizes.push_back(path_loss.size());
    vectorSizes.push_back(h.size());
    vectorSizes.push_back(tau.size());
    vectorSizes.push_back(h_tdl.size());
    vectorSizes.push_back(tau_tdl.size());
    vectorSizes.push_back(logD.size());
    vectorSizes.push_back(fading.size());
    vectorSizes.push_back(logD_model.size());
    vectorSizes.push_back(doppler.size());

    sort(vectorSizes.begin(), vectorSizes.end());


    ofs << "Path loss"
        <<";Impulse reponse"
        <<";tau"
        <<";h_tdl"
        <<";tau_tdl"
        <<";logD"
        <<";fading"
        <<";logD_model"
        <<";Doppler shift"
        << endl;

    int vsize = vectorSizes.back();
    for (int n = 0; n < vsize; n++)
    {
//        if (n < path_loss.size()) {
//            ofs << path_loss[n]<<";" ;
//        } else {
//            ofs << ";" ;
//        }

        if (n < h.size()) {
            ofs << h[n]<<";" ;
        } else {
            ofs << ";" ;
        }

        if (n < tau.size()) {
            ofs << tau[n]<<";" ;
        } else {
            ofs << ";" ;
        }

        if (n < h_tdl.size()) {
            ofs << h_tdl[n]<<";" ;
        } else {
            ofs << ";" ;
        }

        if (n < tau_tdl.size()) {
            ofs << tau_tdl[n]<<";" ;
        } else {
            ofs << ";" ;
        }

        if (n < logD.size()) {
            ofs << logD[n]<<";" ;
        } else {
            ofs << ";" ;
        }

        if (n < fading.size()) {
            ofs << fading[n]<<";" ;
        } else {
            ofs << ";" ;
        }

        if (n < logD_model.size()) {
            ofs << logD_model[n];
        } else {
            ofs << ";" ;
        }

        if (n < doppler.size()) {
            ofs << doppler[n];
        } else {
            ofs << ";" ;
        }

        ofs << endl;

    }
    ofs.close();
}


void Rx::record()
{
    std::ofstream ofs;
//    ofs.open("/Users/amate/Documents/Polytech/Thesis/power.csv", std::ios_base::app | std::ios_base::out);

//    ofs<<m_power<<";"<<endl;

//    ofs.close();
}

void Rx::riceFactor(double rice)
{
    rice_factor = rice;
    if (isnan(rice_factor) || isinf(rice_factor)){
        rice_factor = 1e-300;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 2. Impulse Resoonse and TDL Computation:
void Rx::computeImpulseTDL()
{
   // Number of rays = Number of powers received:
    unsigned long indepentant_rays = m_impulse.size();
    // Creation of two vectors (impusle) and time of each impulse
    h.clear();
    tau.clear();
    h.resize(indepentant_rays);
    tau.resize(indepentant_rays);

    // Creation of TDL delay
    double deltaTau = 1.0e9/(2.0*double(m_transmitterbandwidth)); // [ns]
    std::vector<double> x(indepentant_rays);
    std::vector <std::complex <double>> y(indepentant_rays);

    // loop over all rays

    double tmpPrx = 0;
    int i = 0;
    cout << "New TDL: " << endl;
    double max_h = abs(m_impulse.begin()->second);
    for(const auto &imp : m_impulse){
        // Compute attenuation factor
        tmpPrx += pow(abs(imp.second), 2);
//        double s = 20*log10(abs(m_impulse.begin()->second));
//        double s1 =20*log10(abs(imp.second)) ;
//        h[i] = 1 + 20*log10(abs(imp.second) / abs(m_impulse.begin()->second));
//        h[i] = (abs(imp.second) / abs(m_impulse.begin()->second));
//        h[i] = abs(imp.second)/abs(m_impulse.begin()->second);
        h[i] = abs(imp.second);
        if (max_h < h[i]) max_h = h[i];
        // Compute time of arrival in ns
        tau[i] = imp.first; // tau

        int l = 0;
        while(!(l*deltaTau<=tau[i] && tau[i]<l*deltaTau+deltaTau)){
            l++;
         }
        x[i] = (l+1)*deltaTau;
        y[i] = imp.second;
        i++;
    }


    std::map<double,std::complex<double>> map_tau_tdl;
    double max_tdl = abs(y[0]);
    for (unsigned long i=0; i<indepentant_rays; ++i){
        h[i] = h[i]/max_h;
        map_tau_tdl[x.at(i)] += y[i];
        if (max_tdl < abs(map_tau_tdl[x.at(i)])) {
            max_tdl = abs(map_tau_tdl[x.at(i)]);
        }
    }
    h_tdl.clear();
    tau_tdl.clear();
    h_tdl.resize(map_tau_tdl.size());
    tau_tdl.resize(map_tau_tdl.size());
    i = 0;
    for (const auto &tdl : map_tau_tdl){
//        h_tdl[i] = 20*log10(abs(tdl.second));
//        h_tdl[i] = (abs(tdl.second) / abs(map_tau_tdl.begin()->second));
        h_tdl[i] = abs(tdl.second)/max_tdl;
        cout << "Maximum tdl: " << max_tdl << endl;
        cout << "h_TDL: " << h_tdl[i] << endl;
        tau_tdl[i] = tdl.first;
        i++;
    }


}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 4. Doppler:
void Rx::dopplerSpectrum()
{
    omega.clear();
    doppler.clear();
    omega.resize(m_doppler.size());
    doppler.resize(m_doppler.size());
    int i = 0;
    for(const auto &dop : m_doppler){
        omega[i] = dop.first;
        doppler[i] = 20*log10(abs(dop.second));
        i++;
    }
}

void Rx::sendInterferencePattern()
{
    vector<double> impulse_r(80*80);
    vector<double> tmp_vect_h(80*80);
    QVector<double> rice_distribution;
    double lambda = c/frequency();
    int k = 0;
    double min = -0.0;
    double max = -150.0;
    double max_h = -150.0;
    double impulse_db = 0.0;
    QLineF local_region(QPointF(.0,.0),QPointF(.1,.1));
    for (int i = -40; i < 40; i++)
    {
        for (int j = -40; j < 40; j++)
        {
            local_region.setP2(QPointF(-i * 0.05 * lambda,-j * 0.05 * lambda));
            complex<double> impulse = notifyObserversInterference(local_region);
            impulse_db = 20*log(abs(impulse));
            impulse_r[k] = impulse_db;
            tmp_vect_h[k] = abs(impulse);
            if(impulse_db < min)
            {
                min = impulse_db;
            }
            if(impulse_db>max){
                max = impulse_db;
                max_h = abs(impulse);
            }
            k++;
        }
    }
    m_dialog->setInterferencePattern(impulse_r,min,max);
    map <double,double> distribution;
    double sigma = 0.0;
    for (int i = 0; i < 80*80; i++)
    {
        tmp_vect_h[i] = round(tmp_vect_h[i]/max_h * 1e2) / 1e2;
        distribution[tmp_vect_h[i]] += 1.0/(80.0*80.0);
        if (sigma < tmp_vect_h[i])
        {
            sigma = tmp_vect_h[i];
        }
    }
    for (auto const &imp: distribution)
    {
        rice_distribution.push_back(imp.first / pow(sigma, 2)
                                    * exp(-pow(imp.first,2)/(2*pow(sigma,2)))
                                    * exp(-pow(10,rice_factor/10))
                                    * cyl_bessel_k(0.0,imp.first*sqrt(2*pow(10,rice_factor/10))/sigma));
    }
    m_dialog->setDistributionInterference(distribution ,rice_distribution);
}

// From ReceiverProduct
float Rx::getSpeed(){return m_movement.length();}
float Rx::getOrientation(){return m_movement.angle();}
QLineF Rx::movement() const {return m_movement;}
int Rx::getPosX(){return x();}
int Rx::getPosY(){return y();}
double Rx::getPower() {return m_power;}

double Rx::getDstnc()
{
    if (m_chData != nullptr) return m_chData->dstnc;
    else return 0;
}

double Rx::getDlySprd()
{
    return delay_spread;
}

double Rx::getRiceFctr()
{
    return rice_factor;
}

double Rx::getCoherenceBw()
{
    return coherence_bandwidth;
}

double Rx::getCoherenceTm()
{
    return 0;
}

double Rx::getAngSprd()
{
    return angular_spread;
}

double Rx::getDopplerSprd()
{
    return doppler_spread;
}
complex <double> Rx::getEField() {return m_e_field;}
bool Rx::getEnable() {return enable;}

void Rx::setSpeed(float speed)
{
    if (m_movement.length() == 0.0){m_movement = QLineF(0,0,0,50);}
    m_movement.setLength(speed);
}

void Rx::setOrientation(float orientation)
{
    m_movement.setAngle(orientation);
}

void Rx::setMovement(const QLineF movement)
{
    m_movement = movement;
}

void Rx::setPosX(int posX)
{
    clearData();
    setX(posX);
    if (m_graphic != nullptr){
        m_graphic->notifyToGraphic(this, m_power);
    }
    notifyObservers();
}
void Rx::setPosY(int posY)
{
    clearData();
    setY(posY);
    if (m_graphic != nullptr){
        m_graphic->notifyToGraphic(this);
    }
    notifyObservers();
}
void Rx::setPower(double p) {m_power = p;}
void Rx::setEField(complex<double> e) {m_e_field = e;}
void Rx::setEnable(bool enable) {this->enable = enable;}

vector<double> Rx::spaceCrltn()
{
    vector<double> sc = m_chData->spaceCrltn;
    double max = *sc.begin();
    for (auto &d: sc){
        d = d / max;
    }
    return sc;
}

void Rx::newProperties()
{
    computeMinPrx();
    if (m_graphic != nullptr){
        m_graphic->notifyToGraphic(this,getOrientation());
    }
}

void Rx::dialogDeleted()
{
    m_dialog = nullptr;
}

// From MathematicalProduct
void Rx::openDialog(QWidget *parent)
{
//    for (unsigned i = 0; i < m_transmitters.size(); i++) {
//        notifyObserversPathLoss(m_transmitters.at(i));
//    }
    m_dialog = new DialogRx(this/*, parent*/);
//    for (unsigned i = 0; i < m_transmitters.size(); i++) {
//        m_dialog->shadowing(notifyObservervesShadowing(m_transmitters.at(i)));
//    }
    connect(m_dialog, &DialogRx::save, this, &Rx::save);
    connect(m_dialog, &DialogRx::interferenceActivated, this, &Rx::sendInterferencePattern);
}

void Rx::update(QGraphicsItem* graphic)
{
    setX(graphic->scenePos().x());
    setY(graphic->scenePos().y());
    notifyObservers();
    if (m_dialog != nullptr) {
        m_dialog->update();
    }
}

void Rx::attachObservable(GraphicsProduct *graphic)
{
    m_graphic = graphic;
    m_graphic->notifyToGraphic(this,m_power);
}

void Rx::updateInformation()
{
//    m_info_widget->changePower(m_power);
//    m_info_widget->changeDistance(m_transmitter_distance);
//    m_info_widget->changeSnr(snr_received);
//    m_info_widget->changeDelaySpread(delay_spread);
//    m_info_widget->changeRiceFactor(rice_factor);
//    m_info_widget->changeCoherenceBandwidth(coherence_bandwidth);
//    m_info_widget->changeAngularSpread(angular_spread);
//    m_info_widget->changeDopplerSpread(doppler_spread);

}

// From ProductObservable
void Rx::attachObserver(ProductObserver *productObserver)
{
//    cout<<"Observevr attached"<<endl;
    m_observers.push_back(productObserver);
}

void Rx::notifyObservers()
{
    m_impulse.clear();
    m_doppler.clear();
    angular_distr.clear();
    doppler_distr.clear();

    for (unsigned i = 0; i < m_transmitters.size(); i++) {
        m_chData = m_transmitters.at(i)->update(this, m_movement);
        m_e_field += m_chData->eField;
        m_power = m_chData->prx;
        m_transmitterbandwidth = m_chData->bw;
        m_transmitterfrequency = m_chData->fq;

        if (m_graphic != nullptr){
            m_graphic->notifyToGraphic(this,m_power);

            m_transmitter = m_transmitters.at(i);
    //        m_transmitters.at(0)->drawRays(this, true);

            for(unsigned i = 0; i < m_transmitters.size(); i++) {
                m_transmitters.at(i)->drawRays(this, true);
            }
            computeSnr();
    }
}

//    for (unsigned int i = 0; i < m_observers.size(); i++) {
//        m_observers.at(i)->update(this,m_movement);
//    }

    for (unsigned i = 0; i < m_transmitters.size(); i++) {
//        m_transmitters.at(i)->compute(this);
//        m_impulse = m_transmitters.at(i)->receiverImpulse(this);
//        m_doppler = m_transmitters.at(i)->receiverDoppler(this);
//        riceFactor(m_transmitters.at(i)->riceFactor(this));
//        m_chData = m_transmitters.at(i)->getChData(this);

        extractChData();
        computeImpulseTDL();
        computeDelaySpread();
        coherenceBandwidth();
////        dopplerSpectrum();

    }

}

complex<double> Rx::notifyObserversInterference(QLineF local_region)
{
//    complex<double> impulse_r;
//    for (unsigned i = 0; i < m_transmitters.size(); i++)
//    {
//        impulse_r = m_transmitters.at(i)->computeInterference(this, local_region);
//    }
//    return impulse_r;
}

void Rx::detachObservers()
{
    for (unsigned int i = 0; i < m_observers.size(); i++) {
        delete m_observers.at(i);
    }
    m_observers.clear();
    m_transmitters.clear();
}

void Rx::notify()
{
    notifyObservers();
}


void Rx::notify(double &/*power*/, std::vector<double> */*powers*/, std::complex<double> &/*EMfiled*/)
{

}


const QPointF * Rx::getPos() const
{
    return this ;
}
