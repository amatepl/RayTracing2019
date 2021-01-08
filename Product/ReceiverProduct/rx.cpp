#include "rx.h"

#include <algorithm>
#include "Share/physics.h"
#include <FFT>

Rx::Rx(int posX, int posY): QPointF(posX,posY)
{
    m_type                  = "Receiver";
    m_power                 = 0.0;
    m_e_field               = 0.0;
    m_ind_voltage           = 0.0;
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
    m_ind_voltage = 0;
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
    double pdp;
    double P = 0, tau_m = 0, sigma_tau = 0;
    if (m_chData != nullptr) {
        for (auto imp: m_chData->impulseResp) {
            pdp = norm(imp.second);
            P += pdp;
            tau_m += imp.first*pdp;
            sigma_tau +=  pow(imp.first,2)*pdp;
        }
        tau_m = tau_m/P;
        delay_spread = sqrt(sigma_tau/P-pow(tau_m,2));

        if (delay_spread < 1e-20){
            delay_spread = 0.0;
        }
    }
    else{
        delay_spread = 0.0;
    }
}


void Rx::coherenceBandwidth()
{
    coherence_bandwidth = 1e3 / (2*M_PI*delay_spread); //MHz
}


void Rx::attachTransmitter(ProductObserver *transmitter)
{
    m_transmitters.push_back(transmitter);
}


void Rx::extractChData()
{

    angular_distr.clear();
    doppler_distr.clear();
    m_impulse = m_chData->impulseResp;
//    m_doppler = m_chData->dopplerSpctr;

//    for (const auto e: m_doppler) {
//        doppler.push_back(abs(e.second));
//        omega.push_back(e.first);
//    }

    riceFactor(10*log10(m_chData->losFactor/m_chData->nlosFactor));

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

    pas.clear();
    pds.clear();
    u.clear();
    w.clear();

    map<double, double> localPAS = m_chData->prxAngularSpctrMap;
    for (const auto &e: localPAS) {
        pas.push_back(e.second);
        u.push_back(e.first);
    }

    map<double, double> localPDS = m_chData->prxDopplerSpctrMap;
    for (const auto &e: localPDS) {
        pds.push_back(e.second);
        w.push_back(e.first);
    }

//    if (m_chData->prxAngularSpctr.size() > 0) {
//        vector<double> pasLocal = m_chData->prxAngularSpctr;
//        pas = QVector<double>(pasLocal.begin(), pasLocal.end());
//        vector<double> pdsLocal = m_chData->prxDopplerSpctr;
//        pds = QVector<double>(pdsLocal.begin(), pdsLocal.end());
//    }

    dBm<QVector<double>>(pas);
    dBm<QVector<double>>(pds);
//    dB(pds);

//    cout<<"Tmp prx [dB]: " <<20*log10(tmpPrx)<<", tmp prx: "<<tmpPrx<<", "<<m_power << endl;

//    for (complex<double> &ang: angular_distr) {
//        ang = 20*log10(abs(ang));
//    }


//    angular_spread = m_chData->angularSpred;
//    doppler_spread = m_chData->dopplerSpread;

//    u = QVector<double>(m_chData->u.begin(), m_chData->u.end());
//    w = QVector<double>(m_chData->w.begin(), m_chData->w.end());
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
    vectorSizes.push_back(m_chData->dopplerSpctr.size());
    vectorSizes.push_back(m_chData->prxAngularSpctrMap.size());
    vectorSizes.push_back(m_chData->prxDopplerSpctrMap.size());

    vector<double> doppler;
    for (const auto &e: m_chData->dopplerSpctr) {
        doppler.push_back(abs(e.second));
    }

    sort(vectorSizes.begin(), vectorSizes.end());


//    ofs << "Path loss"
    ofs <<"Impulse reponse"
        <<";tau"
        <<";h_tdl"
        <<";tau_tdl"
        <<";logD"
        <<";fading"
        <<";logD_model"
        <<";Doppler shift"
        <<";u"
        <<";PAS"
        <<";w"
        <<";PDS"
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
            ofs << logD_model[n]<<";";
        } else {
            ofs << ";" ;
        }

        if (n < m_chData->dopplerSpctr.size()) {
            ofs << doppler[n]<<";";
        } else {
            ofs << ";" ;
        }

        if (n < m_chData->prxAngularSpctrMap.size()) {
            ofs << u[n]<<";" <<pas[n]<<";";
        } else {
            ofs << ";" ;
        }

        if (n < pds.size()) {
            ofs << w[n] <<";" <<pds[n];
        } /*else {
            ofs << ";" ;
        }*/

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

    for (unsigned i=0; i<indepentant_rays; ++i){
        h[i] = h[i]/max_h;
        m_tdl[x[i]] += y[i];
    }
    h_tdl.clear();
    tau_tdl.clear();
    h_tdl.resize(m_tdl.size());
    tau_tdl.resize(m_tdl.size());
    i = 0;
    double max_tdl = 0;
    for (const auto &tdl : m_tdl){
//        h_tdl[i] = 20*log10(abs(tdl.second));
//        h_tdl[i] = (abs(tdl.second) / abs(map_tau_tdl.begin()->second));
        h_tdl[i] = abs(tdl.second);
        if (max_tdl <h_tdl[i]) max_tdl = h_tdl[i];
        tau_tdl[i] = tdl.first;
        i++;
    }

    for (int i=0; i<h_tdl.size(); ++i){
        h_tdl[i] = h_tdl[i]/max_tdl;
    }

    max_voltage = max_h;
    max_voltage_tdl = max_tdl;
}

// Frequency Response
vector<double> Rx::fqResp() const
{
    vector<double> res;
    if (m_chData != nullptr && m_chData->impulseResp.size() != 0){
        vector<complex<double>> h;
        vector<double> t;
        for (const auto &tdl : m_tdl) {
            h.push_back(tdl.second);
            t.push_back(tdl.first);
        }
//        for (auto e: m_chData->impulseResp) {
//            t.push_back(e.first);
//            h.push_back(abs(e.second));
//        }
        double step = 1/(2*m_chData->bw)*1e9;
        vector<complex<double>> uph = ph::upsample<double, complex<double>>(t, h, 0, t.back(), step);
        vector<complex<double>> fqResp = ph::dft(uph);
//        vector<complex<double>> fqResp ;

//        Eigen::FFT<double> fft;
//        fft.fwd(fqResp, uph);
        double fpos = 0.0;
        double fneg = 0.0;
        double length = fqResp.size();
        res.resize(length);
        for (const auto &e: fqResp) {
            if (fpos < length/2) {
                res.at(fpos+length/2) = 20*log10(round(abs(e)*1e6)/1e6);
                m_chData->fqResp[fpos/(uph.size()*step*1e-9)] = e;
                fpos++;
            }
            else {
                res.at(fneg) = 20*log10(round(abs(e)*1e6)/1e6);
                m_chData->fqResp[(-length/2+fneg)/(uph.size()*step*1e-9)] = e;
                fneg ++;
            }
        }
//        for (const auto e: m_chData->fqResp) {
//            res.push_back(abs(e.second));
//        }
    }
    return res;
}

vector<double> Rx::fq() const
{
    vector<double> res;
    double fq = 0.0;
    vector<double> h;
    vector<double> t;
    if (m_chData != nullptr) {
        for (const auto &e: m_chData->fqResp) {
            fq = e.first/*-m_chData->fqResp.size()/2)/(uph.size()*step*1e-9)*/;
            res.push_back(fq);
        }
    }
    return res;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 4. Doppler:
void Rx::dopplerSpectrum()
{
//    omega.clear();
//    doppler.clear();
//    omega.resize(m_doppler.size());
//    doppler.resize(m_doppler.size());
//    int i = 0;
//    for(const auto &dop : m_doppler){
//        omega[i] = dop.first;
//        doppler[i] = 20*log10(abs(dop.second));
//        i++;
//    }
}

void Rx::sendInterferencePattern()
{
    if (m_chData != nullptr) {
        if(m_chData->intPattern.size()>0){
            complex<double> i_comp(0,1);
            vector<double> impulse_r(320*320);
            vector<double> tmp_vect_h(320*320);
            QVector<double> rice_distribution;
            double lambda = c/m_chData->fq;
            int k = 0;
            double min = -0.0;
            double max = -150.0;
            double max_h = -150.0;
            double impulse_db = 0.0;
            QLineF local_region(QPointF(.0,.0),QPointF(.1,.1));
            for (int i = -160; i < 160; i++)
            {
                for (int j = -160; j < 160; j++)
                {
                    local_region.setP2(QPointF(i * 0.1 * lambda,j * 0.1 * lambda));
                    complex<double> impulse = 0.0;
                    for (auto &pattern: m_chData->intPattern){
                        double angleMPC = pattern.first;
                        QLineF beta(QPointF(.0,.0),QPointF(2*M_PI*cos(angleMPC*M_PI/180)/lambda,2*M_PI*sin(angleMPC*M_PI/180)/lambda));
                        double scalar_product = beta.p2().x()*local_region.p2().x() + beta.p2().y()*local_region.p2().y();
                        double indVolt_real = round(pattern.second.real()*1e5)/1e5;
                        double indVolt_imag = round(pattern.second.imag()*1e5)/1e5;
                        complex<double> indVolt(indVolt_real,indVolt_imag);
                        impulse += indVolt*exp(-i_comp*scalar_product);
                        if (i == -20 && j == -40){
//                            cout << "induced voltage LOS (-lambda,-2lambda): " << pattern.second << endl;
//                            cout << "impulse LOS: (-lambda,-2lambda):" << indVolt*exp(-i_comp*scalar_product) << endl;
                        }
                        if (i == 20 && j == 20){
//                            cout << "induced voltage LOS (lambda,lambda): " << pattern.second << endl;
//                            cout << "impulse LOS: (lambda,lambda):" << indVolt*exp(-i_comp*scalar_product) << endl;
                        }
                    }
                    if (m_chData->indVoltageGnd != 0.0){
                        double angleGroundX = m_chData->angleGroundX;
                        double angleGroundZ = m_chData->angleGroundZ;
                        QLineF beta(QPointF(.0,.0),QPointF(2*M_PI*cos(angleGroundZ*M_PI/180)*cos(angleGroundX*M_PI/180)/lambda,2*M_PI*cos(angleGroundZ*M_PI/180)*sin(angleGroundX*M_PI/180)/lambda));
                        double scalar_product = beta.p2().x()*local_region.p2().x() + beta.p2().y()*local_region.p2().y();
                        double indVolt_real = round(m_chData->indVoltageGnd.real()*1e5)/1e5;
                        double indVolt_imag = round(m_chData->indVoltageGnd.imag()*1e5)/1e5;
                        complex<double> indVolt(indVolt_real,indVolt_imag);
                        impulse += indVolt*exp(-i_comp*scalar_product);
                        if (i == -20 && j == -40){
//                            cout << "induced voltage GND (-lambda,-2lambda): " << m_chData->indVoltageGnd << endl;
//                            cout << "impulse GND: (-lambda,-2lambda):" << indVolt*exp(-i_comp*scalar_product) << endl;
                        }
                        if (i == 20 && j == 20){
//                            cout << "induced voltage GND (lambda,lambda): " << m_chData->indVoltageGnd << endl;
//                            cout << "impulse GND: (lambda,lambda):" << indVolt*exp(-i_comp*scalar_product) << endl;
                        }
                    }
                    impulse_db = 20*log10(abs(impulse));
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
    //        map <double,double> distribution;
    //        double sigma = 0.0;
    //        for (int i = 0; i < 80*80; i++)
    //        {
    //            tmp_vect_h[i] = round(tmp_vect_h[i]/max_h * 1e2) / 1e2;
    //            distribution[tmp_vect_h[i]] += 1.0/(80.0*80.0);
    //            if (sigma < tmp_vect_h[i])
    //            {
    //                sigma = tmp_vect_h[i];
    //            }
    //        }
    //        for (auto const &imp: distribution)
    //        {
    //            rice_distribution.push_back(imp.first / pow(sigma, 2)
    //                                        * exp(-pow(imp.first,2)/(2*pow(sigma,2)))
    //                                        * exp(-pow(10,rice_factor/10))
    //                                        /** cyl_bessel_k(0.0,imp.first*sqrt(2*pow(10,rice_factor/10))/sigma)*/);
    //        }
    //        m_dialog->setDistributionInterference(distribution ,rice_distribution);
        }
    }
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

double Rx::getCoherenceDist()
{
    if (m_chData){
        spaceCrltn();
        return ph::firstMinIdx(m_chData->spaceCrltnMap); // cm
    } else return 0;
}

double Rx::getCoherenceBw()
{
    return coherence_bandwidth;
}

double Rx::getCoherenceTm()
{
    if (m_chData){
        timeCrltn();
        return ph::firstMinIdx(m_chData->timeCrltnMap)*10000; // us
    } else return 0;
//    return 0;
}

double Rx::getAngSprd()
{
    if (m_chData && m_chData->prxAngularSpctrMap.size()){
        return ph::spread(m_chData->prxAngularSpctrMap);
    } else return 0;
//    return angular_spread;
}

double Rx::getDopplerSprd()
{
    if (m_chData && m_chData->prxDopplerSpctrMap.size()) {
        return ph::spread(m_chData->prxDopplerSpctrMap);
    } else return 0;
//    return doppler_spread;
}
complex <double> Rx::getEField() {return m_e_field;}
complex <double> Rx::getVoltage() {return m_ind_voltage;}
bool Rx::getEnable() {return enable;}


vector<double> Rx::getDoppler()
{
    vector<double> doppler;
    if (m_chData != nullptr) {
        for (auto e: m_chData->dopplerSpctr) {
            doppler.push_back(abs(e.second));
        }
    }
    return doppler;
}

vector<double> Rx::getOmega()
{
    vector<double> omega;
    if (m_chData != nullptr) {
        for (auto e: m_chData->dopplerSpctr) {
            omega.push_back(e.first);
        }
    }
    return omega;
}

vector<double> Rx::getPDP(){
    vector<double> pdp;
    double P;
    if (m_chData != nullptr) {
        for (auto imp: m_chData->impulseResp) {
            P = 10*log10(norm(imp.second));
            pdp.push_back(P);
        }
    }
    return pdp;
}

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
    vector<double> sc;
    if (m_chData != nullptr && m_chData->prxAngularSpctrMap.size()){
        vector<double> pas;
        vector<double> u;
        for (auto e: m_chData->prxAngularSpctrMap) {
            u.push_back(e.first);
            pas.push_back(e.second);
        }
        double wvNbr = 2. * M_PI * m_chData->fq / c;
        vector<double> upPAS = ph::upsample<double, double>(u, pas, -wvNbr, wvNbr, 1);
        vector<complex<double>> compUpPAS;
        for (double &e: upPAS) {
            compUpPAS.push_back(complex<double>(e, 0));
        }

        int nifft = pow(2, 17);
        vector<complex<double>> fqResp;
        fqResp = compUpPAS;
        fqResp.resize(nifft);
        ph::fft(fqResp, true);

        m_chData->spaceCrltnMap.clear();
        m_chData->deltaZ.clear();
        double deltaZ = 0;
        for (const auto &e: fqResp) {
            m_chData->spaceCrltnMap[deltaZ * 2 * M_PI * 100 / nifft] = round(abs(e / (2*M_PI))*1e16)/1e16; // /*abs(e/*.real()*/)*/ ;
            m_chData->deltaZ.push_back(deltaZ * 2 * M_PI * 100 / nifft);
            sc.push_back(round(abs(e / (2*M_PI))*1e16)/1e16 /*e.real()*/);
            deltaZ++;
        }

//        sc = m_chData->spaceCrltn;
        double max = *sc.begin();
        for (auto &d: sc){
            d = d / max;
        }
    }
    return sc;
}

vector<double> Rx::deltaZ()
{
    vector<double> dz;
    if (m_chData != nullptr) dz = m_chData->deltaZ;
    return dz;
}

vector<double> Rx::timeCrltn() const
{
    m_chData->timeCrltnMap.clear();
    m_chData->deltaT.clear();
    double speed = m_chData->maxSpeed;
    vector<double> tc;
    if (m_chData != nullptr && m_chData->prxDopplerSpctrMap.size() > 1 ){
        vector<complex<double>> pds;
        vector<double> w;
        for (auto e: m_chData->prxDopplerSpctrMap) {
            w.push_back(e.first);
            pds.push_back(round(e.second));
        }
        double wvNbr = 2. * M_PI * m_chData->fq / c;
        vector<complex<double>> upPDS = ph::upsample<double, complex<double>>(w, pds, -wvNbr*speed, wvNbr*speed, 1);
//        vector<complex<double>> fqResp = ph::idft(upPDS);

//        vector<complex<double>> complexPDS;
//        for (const auto &e: upPDS) {
//            complexPDS.push_back(e);
//        }
        int nifft = pow(2, 17);
//        Eigen::FFT<double> fft;
        vector<complex<double>> ifftPDS = upPDS;
        ifftPDS.resize(nifft);
//        fft.inv(ifftPDS, complexPDS);
//        fft.inv(ifftPDS, upPDS, pow(2, 14));

        ph::fft(ifftPDS, true);

        double deltaT = 0;
        for (const auto &e: ifftPDS) {
            m_chData->timeCrltnMap[deltaT * 100 * 2 * M_PI / nifft] = abs(e / (2*M_PI));
            m_chData->deltaT.push_back(deltaT * 100 * 2 * M_PI / nifft);
            tc.push_back(abs(e / (2*M_PI)));
            deltaT++;
        }

//        sc = m_chData->spaceCrltn;
        double max = *tc.begin();
        for (auto &d: tc){
            d = d / max;
        }
    }
    return tc;
}

vector<double> Rx::timeCrltnT() const
{
    vector<double> t;
    if (m_chData && m_chData->timeCrltnMap.size() && m_chData->maxSpeed) {
        for (const auto &e: m_chData->timeCrltnMap) {
            t.push_back(e.first);
        }
    }
    return t;
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
void Rx::openDialog(QWidget */*parent*/)
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
    m_tdl.clear();
    angular_distr.clear();
    doppler_distr.clear();

    for (unsigned i = 0; i < m_transmitters.size(); i++) {
        // Here must be the choice of transmitter and the different
        // physical results. Not totally optimal for the moment.
        m_chData = m_transmitters.at(i)->update(this, m_movement);
        // Voltage:
        m_ind_voltage = m_chData->indVoltage;
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
    if (m_dialog != nullptr) {
        m_dialog->update();
        sendInterferencePattern();
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
