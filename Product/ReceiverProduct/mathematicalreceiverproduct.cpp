#include "mathematicalreceiverproduct.h"

#include <algorithm>

MathematicalReceiverProduct::MathematicalReceiverProduct(int posX, int posY):
    QPointF(posX,posY)
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

MathematicalReceiverProduct::MathematicalReceiverProduct(MathematicalReceiverProduct* receiver):
    QPointF(receiver->getPosX(),receiver->getPosY())
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

MathematicalReceiverProduct::~MathematicalReceiverProduct()
{
    cout << "Mathematical Receiver Product Deleted." << endl;
    delete m_dialog;
}

void MathematicalReceiverProduct::clearObeservers()
{
    m_observers.clear();
}

void MathematicalReceiverProduct::clearData()
{
    m_power = 0;
    m_e_field = 0;
}

double MathematicalReceiverProduct::inputNoise()
{
    return 10 * log10(kb * To * m_transmitterbandwidth);
}

void MathematicalReceiverProduct::computeMinPrx()
{
    min_prx = m_target_snr + m_noise_figure + inputNoise() + m_interferencemargin + 30; // [dBm]
}


void MathematicalReceiverProduct::computeSnr()
{
    if (m_power != 0.0){
        snr_received = (m_power - 30) - m_noise_figure - inputNoise(); // [dB]
    }
}


void MathematicalReceiverProduct::computeDelaySpread()
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


void MathematicalReceiverProduct::coherenceBandwidth()
{
    coherence_bandwidth = 1e3 / delay_spread; //MHz
}


void MathematicalReceiverProduct::attachTransmitter(ProductObserver *transmitter)
{
    m_transmitters.push_back(transmitter);
}


void MathematicalReceiverProduct::extractChData()
{
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

    for (double &prx: pas) {
        prx = 20*log10(prx);
    }

//    cout<<"Tmp prx [dB]: " <<20*log10(tmpPrx)<<", tmp prx: "<<tmpPrx<<", "<<m_power << endl;

//    for (complex<double> &ang: angular_distr) {
//        ang = 20*log10(abs(ang));
//    }

    angular_spread = m_chData->angularSpred;
    doppler_spread = m_chData->dopplerSpread;
    u = QVector<double>(m_chData->u.begin(), m_chData->u.end());
    w = QVector<double>(m_chData->w.begin(), m_chData->w.end());
}


void MathematicalReceiverProduct::save(string path)
{
//    cout << "/Users/amate/Documents/Polytech/Thesis/powerTest.csv" <<endl;

//    std::ofstream ofs (path);
    std::ofstream ofs;
    ofs.open(path, std::ios_base::app | std::ios_base::out);

    vector<unsigned> vectorSizes;

    vectorSizes.push_back(path_loss.size());
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
        if (n < path_loss.size()) {
            ofs << path_loss[n]<<";" ;
        } else {
            ofs << ";" ;
        }

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


void MathematicalReceiverProduct::record()
{
    std::ofstream ofs;
//    ofs.open("/Users/amate/Documents/Polytech/Thesis/power.csv", std::ios_base::app | std::ios_base::out);

//    ofs<<m_power<<";"<<endl;

//    ofs.close();
}

void MathematicalReceiverProduct::riceFactor(double rice)
{
    rice_factor = rice;
    if (isnan(rice_factor) || isinf(rice_factor)){
        rice_factor = 1e-300;
    }
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 1. Path Loss Computation:

void MathematicalReceiverProduct::computePathLossFading()
{
    path_loss.resize(m_pathloss.size());
    fading.resize(m_pathloss.size());
    friis_loss.resize(m_pathloss.size());
    linearRegressionPathLoss();
    for (unsigned long i=0; i<m_pathloss.size(); i++){
            path_loss[i] = m*logD[i]+b;
            fading[i] = Prx[i]-path_loss[i];
            friis_loss[i] = -20*logD[i] + m_pathloss[1.0];
    }
    fading_variability = standardDeviation();
}

void MathematicalReceiverProduct::linearRegressionPathLoss()
{
    /*
    *   b = output intercept
    *   m  = output slope
    *   r = output correlation coefficient (can be NULL if you don't want it)
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
    double L_fading_model;
    for (int i=0; i<lengthData; ++i){
        logD_model[i] = minDist + i*step;
        D_model[i] = pow(10, logD_model[i]);
        path_loss_model[i] =  m*logD_model[i] + b;
        L_fading_model = distribution(generator);
        Prx_model[i] = path_loss_model[i] + L_fading_model;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 2. Impulse Resoonse and TDL Computation:
void MathematicalReceiverProduct::computeImpulseTDL(){
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
    for(const auto &imp : m_impulse){
        // Compute attenuation factor
        tmpPrx += pow(abs(imp.second), 2);
        h[i] = 20*log10(abs(imp.second));
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
    for (unsigned long i=0; i<indepentant_rays; ++i){
        map_tau_tdl[x.at(i)] += y[i];
    }
    h_tdl.clear();
    tau_tdl.clear();
    h_tdl.resize(map_tau_tdl.size());
    tau_tdl.resize(map_tau_tdl.size());
    i = 0;
    for (const auto &tdl : map_tau_tdl){
        h_tdl[i] = 20*log10(abs(tdl.second));
        tau_tdl[i] = tdl.first;
        i++;
    }


}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 3. Cell Range Computation:
void MathematicalReceiverProduct::cellRange()
{
    // minPrx = <Prx> - L_fading
    // <Prx> = mx + b; where x = log10(d)
    // Pr[L_fading<gamma] = 1 - 1/2* erfc(gamma/(fadingVariability * sqrt(2)))

    // Sweep gamma [0; 3*fadingVariability] => Compute probability Pr[L_fading<gamma] for each gamma
    // => Compute R such that minPrx> = <Prx(R)> - gamma
    int lengthData = 100;
    double step = (3*fading_variability)/lengthData;
    double gamma;
    probability.resize(lengthData);
    cell_range.resize(lengthData);
    for (int i=0; i<lengthData; ++i){
        gamma = i*step;
        probability[i] = 1 - 0.5*erfc(gamma/(fading_variability * sqrt(2)));// Pr[L_fading<gamma]

        // minPrx = mx + b - gamma[dBm] => x = (minPrx + gamma - b)/m
        // => log10(d) = (-102 + gamma - b)/m => d = 10((minPrx + gamma - b)/m)
        cell_range[i] = pow(10,(min_prx + gamma - b)/m);
    }
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 4. Doppler:
void MathematicalReceiverProduct::dopplerSpectrum()
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

void MathematicalReceiverProduct::sendInterferencePattern(){
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
    for (int i = -40; i<40; i++)
    {
        for (int j = -40; j<40; j++)
        {
            local_region.setP2(QPointF(-i*0.05*lambda,-j*0.05*lambda));
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
        rice_distribution.push_back(imp.first/pow(sigma,2)
                                    * exp(-pow(imp.first,2)/(2*pow(sigma,2)))
                                    * exp(-pow(10,rice_factor/10)));
//                                    * cyl_bessel_k(0.0,imp.first*sqrt(2*pow(10,rice_factor/10))/sigma));
    }
    m_dialog->setDistributionInterference(distribution,rice_distribution);
}

// From ReceiverProduct
float MathematicalReceiverProduct::getSpeed(){return m_movement.length();}
float MathematicalReceiverProduct::getOrientation(){return m_movement.angle();}
QLineF MathematicalReceiverProduct::movement() const {return m_movement;}
int MathematicalReceiverProduct::getPosX(){return x();}
int MathematicalReceiverProduct::getPosY(){return y();}
double MathematicalReceiverProduct::getPower() {return m_power;}
complex <double> MathematicalReceiverProduct::getEField() {return m_e_field;}
bool MathematicalReceiverProduct::getEnable() {return enable;}

void MathematicalReceiverProduct::setSpeed(float speed){
    if (m_movement.length() == 0.0){m_movement = QLineF(0,0,0,50);}
    m_movement.setLength(speed);
}

void MathematicalReceiverProduct::setOrientation(float orientation){
    m_movement.setAngle(orientation);
}

void MathematicalReceiverProduct::setMovement(const QLineF movement){
    m_movement = movement;
}

void MathematicalReceiverProduct::setPosX(int posX) {
    clearData();
    setX(posX);
    if (m_graphic != nullptr){
        m_graphic->notifyToGraphic(this, m_power);
    }
    notifyObservers();
}
void MathematicalReceiverProduct::setPosY(int posY) {
    clearData();
    setY(posY);
    if (m_graphic != nullptr){
        m_graphic->notifyToGraphic(this);
    }
    notifyObservers();
}
void MathematicalReceiverProduct::setPower(double p) {m_power = p;}
void MathematicalReceiverProduct::setEField(complex<double> e) {m_e_field = e;}
void MathematicalReceiverProduct::setEnable(bool enable) {this->enable = enable;}

void MathematicalReceiverProduct::newProperties(){
    computeMinPrx();
    if (m_graphic != nullptr){
        m_graphic->notifyToGraphic(this,getOrientation());
    }
}

// From MathematicalProduct
void MathematicalReceiverProduct::openDialog(){
    for (unsigned i = 0; i < m_transmitters.size(); i++) {
        notifyObserversPathLoss(m_transmitters.at(i));
    }
    m_dialog = new DialogReceiverProduct(this);
    for (unsigned i = 0; i < m_transmitters.size(); i++) {
        m_dialog->shadowing(notifyObservervesShadowing(m_transmitters.at(i)));
    }
    connect(m_dialog, &DialogReceiverProduct::save,
            this, &MathematicalReceiverProduct::save);
    connect(m_dialog,&DialogReceiverProduct::interferenceActivated,this,&MathematicalReceiverProduct::sendInterferencePattern);
}

void MathematicalReceiverProduct::update(QGraphicsItem* graphic){
    setX(graphic->scenePos().x());
    setY(graphic->scenePos().y());
    notifyObservers();
}

void MathematicalReceiverProduct::attachObservable(GraphicsProduct *graphic){
    m_graphic = graphic;
    m_graphic->notifyToGraphic(this,m_power);
}

void MathematicalReceiverProduct::updateInformation(){
    m_info_widget->changePower(m_power);
    m_info_widget->changeDistance(m_transmitter_distance);
    m_info_widget->changeSnr(snr_received);
    m_info_widget->changeDelaySpread(delay_spread);
    m_info_widget->changeRiceFactor(rice_factor);
    m_info_widget->changeCoherenceBandwidth(coherence_bandwidth);
    m_info_widget->changeAngularSpread(angular_spread);
}

// From ProductObservable
void MathematicalReceiverProduct::attachObserver(ProductObserver *productObserver){
//    cout<<"Observevr attached"<<endl;
    m_observers.push_back(productObserver);
}

void MathematicalReceiverProduct::notifyObservers()
{
    m_impulse.clear();
    m_doppler.clear();
    for (unsigned i = 0; i < m_transmitters.size(); i++) {
        m_transmitters.at(i)->update(this, m_movement);
        }

    for (unsigned int i = 0; i < m_observers.size(); i++) {
        m_observers.at(i)->update(this,m_movement);
    }

    for (unsigned i = 0; i < m_transmitters.size(); i++) {
        m_transmitters.at(i)->compute(this);
        m_impulse = m_transmitters.at(i)->receiverImpulse(this);
        m_doppler = m_transmitters.at(i)->receiverDoppler(this);
        riceFactor(m_transmitters.at(i)->riceFactor(this));
        m_chData = m_transmitters.at(i)->getChData(this);

        computeImpulseTDL();
        computeDelaySpread();
        coherenceBandwidth();
//        dopplerSpectrum();

        extractChData();
    }

}

void MathematicalReceiverProduct::notifyObserversPathLoss(ProductObserver* transmitter)
{
    vector<QPointF> pl_points = transmitter->pathLossPoints();
                                // get the path loss (pl) points of the transmitter
    MathematicalReceiverProduct* copy_receiver = new MathematicalReceiverProduct(this);
                                // copy a receiver to compute power
    std::map<double /*distance*/, double /*power sum*/> sum_power;
                                // sum of power
    std::map<double /*distance*/, int /*counter*/> counter;
                                // counter to compute average
    QPointF* tx_pos = dynamic_cast<QPointF*>(transmitter);
    for(unsigned i = 0; i <= pl_points.size(); i++)
    {
        if (i == pl_points.size()){
            copy_receiver->setX(tx_pos->x()+1.0/px_to_meter);
            copy_receiver->setY(tx_pos->y());
        }
        else {
            copy_receiver->setX(pl_points.at(i).x());
            copy_receiver->setY(pl_points.at(i).y());
        }
        transmitter->update(copy_receiver, m_movement);
        for (unsigned int l = 0; l < m_observers.size(); l++)
        {
            m_observers.at(l)->update(copy_receiver,m_movement);
        }
        double power = transmitter->computePathLossPower(copy_receiver);
        QLineF line(*tx_pos,*static_cast<QPointF*>(copy_receiver));
        if (i == pl_points.size()){
            counter[1.0] +=1;
            sum_power[1.0] += power;
        }
        if (!isinf(power) && line.length()*px_to_meter >= 1.0)
        {
            counter[line.length()*px_to_meter] +=1;
            sum_power[line.length()*px_to_meter] += power;
        }
    }
    m_pathloss.clear();
    m_pathloss = averageOnMap(sum_power,counter);
    computePathLossFading();
    modelPathLoss();
    cellRange();
    computeMinPrx();
    delete copy_receiver;
}

map<double,double>
MathematicalReceiverProduct::notifyObservervesShadowing(ProductObserver* tx)
{
    vector<QPointF> points = circlePoints(*dynamic_cast<QPointF*>(tx),100,1);
    MathematicalReceiverProduct* copy_receiver = new MathematicalReceiverProduct(this);
    map <double /*angle*/,double /*power*/> shadow;
    for(unsigned i = 0; i < points.size(); i++)
    {
        copy_receiver->setX(points.at(i).x());
        copy_receiver->setY(points.at(i).y());
        tx->update(copy_receiver, m_movement);
        for (unsigned int l = 0; l < m_observers.size(); l++)
        {
            m_observers.at(l)->update(copy_receiver,m_movement);
        }
        double power = tx->computePathLossPower(copy_receiver);
        QLineF line(*dynamic_cast<QPointF*>(tx),*copy_receiver);
        if (!isinf(power) && line.length()*px_to_meter >= 1.0)
        {
            shadow[line.angle()*M_PI/180.0] = power;
        }
    }
    delete copy_receiver;
    return shadow;
}

vector<QPointF>
MathematicalReceiverProduct::circlePoints(QPointF center, double radius, int rpd)
{
    vector<QPointF> points;
    QPointF point;
    double range = 1.0/rpd;
    for (double theta = 0; theta < 360; theta += range){
        point.setX(radius*cos(theta*M_PI/180.0));
        point.setY(radius*sin(theta*M_PI/180.0));
        points.push_back(center+point);
    }
    return points;
}

std::map<double,double>
MathematicalReceiverProduct::averageOnMap(std::map<double, double> values,
                                          std::map<double, int> counter) const
{
    std::map<double,double> average_map;
    for(const auto &value: values){
        average_map[value.first] = value.second/counter[value.first];
    }
    return average_map;
}

complex<double> MathematicalReceiverProduct::notifyObserversInterference(QLineF local_region)
{
    complex<double> impulse_r;
    for (unsigned i = 0; i < m_transmitters.size(); i++)
    {
        impulse_r = m_transmitters.at(i)->computeInterference(this, local_region);
    }
    return impulse_r;
}

void MathematicalReceiverProduct::detachObservers() {
    for (unsigned int i = 0; i < m_observers.size(); i++) {
        delete m_observers.at(i);
    }
    m_observers.clear();
    m_transmitters.clear();
}

void MathematicalReceiverProduct::notify(){
    notifyObservers();
}


void MathematicalReceiverProduct::notify(double &/*power*/,
                                         std::vector<double> */*powers*/,
                                         std::complex<double> &/*EMfiled*/)
{

}


void MathematicalReceiverProduct::answer(ProductObserver *observer, double frequency,
                                         double bandwidth, double &power,
                                         std::complex<double> &EMfield)
{
    m_e_field += EMfield;
    m_power = power;
//    record();
//    save("/Users/amate/Documents/Polytech/Thesis/dataOnlyBetweenCar.csv");
    m_transmitterbandwidth = bandwidth;
    m_transmitterfrequency = frequency;
    if (m_graphic != nullptr){
        m_graphic->notifyToGraphic(this,m_power);

        m_transmitter = observer;
//        m_transmitters.at(0)->drawRays(this, true);

        for(unsigned i = 0; i < m_transmitters.size(); i++) {
            m_transmitters.at(i)->drawRays(this, true);
        }

        computeSnr();

    }
//    if(m_power < power - 20 && observer != m_transmitter){
//        m_power = power;
//        m_graphic->notifyToGraphic(this,m_power);
////        if(m_transmitter!=nullptr){
////            //m_transmitter->drawRays(this,false);
////        }
//        m_transmitter = observer;
//        m_transmitter->drawRays(this,true);
//    }
//    else{
//        m_power = power;
//        m_graphic->notifyToGraphic(this,m_power);
//        if(m_transmitter != 0){
//            m_transmitter->drawRays(this,true);
//        }
//        else{
//            m_transmitter = observer;
//        }
//    }

}


const QPointF * MathematicalReceiverProduct::getPos() const
{
    return this ;
}
