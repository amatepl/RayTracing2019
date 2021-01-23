#include "physics.h"
#include <FFT>

using namespace ph;

ph::u ph::uMPC(double wvNbr, angle theta)
{
    // if we choose 0° in -y axe which is not natural
    // double theta = angleRx > 90 ? angleRx - 90: angleRx + 270;

    return wvNbr * cos(theta * M_PI / 180);
}


double ph::omegaMPC(double v, double wvNbr,  angle angleRx)
{
    return v * ph::uMPC(wvNbr, angleRx);
}


double ph::prxSpctrMPC(angle theta, double spectrum)
{
    double max_spectrum = spectrum / cos(theta * M_PI / 180.);
    return 2 * M_PI / (max_spectrum * sqrt(1 - pow(spectrum/max_spectrum, 2)));
}

double ph::prxSpctrMPC(std::complex<double> &angDistr, const double ampu, const ph::u u)
{
//    return 2*M_PI;
//    return 2*M_PI/std::sqrt(pow(ampu, 2) - pow(u, 2));
    return norm(angDistr)/(2 * M_PI);
//    return ampu * sqrt(1 - pow(u/ampu, 2)) * norm(angDistr) / (2 * M_PI);
//    return ampu * sqrt(1 - pow(u/ampu, 2)) * angDistr / (2 * M_PI);
}


std::complex<double> ph::angDistrMPC(const std::complex<double> &h, const double theta, const double spectrum)
{
//    return 2 * M_PI;
    return 2 * M_PI * h;
//    return 2 * M_PI * 1 / (spectrum * sin(theta * M_PI / 180.0)/ cos(theta * M_PI / 180));
}

template <typename T>
void sample(vector<T> &vec, T range){
    T s = -range;
    for (auto &e: vec) {
        while (e > s) {

        }
    }
}

double ph::spread(const vector<double> &psd, const vector<double> &u)
{
    double prx = 0;
    double variance = 0;
    double mean = 0;

    for (unsigned i = 0; i < psd.size(); i++) {
        prx += psd.at(i);
        variance += pow(u.at(i), 2) * psd.at(i);
        mean += u.at(i) * psd.at(i);
    }

    return sqrt(variance/prx - pow(mean/prx, 2));
}

double ph::spread(const map<double, double> &pds)
{
    double prx = 0;
    double variance = 0;
    double mean = 0;
    for (const auto &e: pds) {
        prx += e.second;
        variance += pow(e.first, 2) * e.second;
        mean += e.first * e.second;
    }
    return sqrt(variance/prx - pow(mean/prx, 2));
}

map<double, complex<double>> ph::correlation(const map<double, double> &spctr, const vector<double> &domain)
{
    map <double, complex<double>> out;
    complex<double> j{0,1};
    for (const auto &e: spctr) {
        for (const double d: domain) {
            out[d] += e.second * exp(j * e.first * d) / (2 * M_PI);
        }
    }

    return out;

//    Eigen::FFT<double> fft;
//    fft.inv(out, spctr);

//    map<double, double> corr;
//    unsigned size = out.size();
//    for (unsigned i = 0; i < size; i++) {
//        corr[i] = out[i];
//    }
//    return corr;
}


complex <double> ph::dipoleFactor(double phi)
{
    complex <double> dipolefactor(0.0, 0.0);
    if (phi == 0.0 || phi == 180.0) {
        dipolefactor = 0.0;

    } else {
        dipolefactor = cos(0.5 * M_PI * cos(phi * M_PI / 180)) / sin(phi * M_PI / 180);

    }
    return dipolefactor;
}


complex <double> ph::reflectorFactor(angle theta, angle phi, double fq, angle antOrien){
    complex <double> reflectorfactor(0.0,0.0);
    double lambda = c/fq;

    double d = lambda/4.0;
    double k = 2.0*M_PI/lambda;
    complex <double> i(0.0,1.0);
    double thetaprime = theta + antOrien;
    if (thetaprime < 0.0){
        thetaprime = 360 + thetaprime;
    }
    complex <double> psy = k * d * sin(phi * M_PI / 180) * cos(thetaprime * M_PI / 180);
    if ((thetaprime >= 270 && thetaprime < 360.0) || (thetaprime >=0 && thetaprime < 90.0)) {
        reflectorfactor = 2.0 * i * exp(-i * psy) * sin(psy);
    }
    return reflectorfactor;
}


complex <double> ph::reflectorFactor(angle theta, angle phi, const ph::TxParams &txParams){
    complex <double> reflectorfactor(0.0,0.0);
    double lambda = c/txParams.fq;

    double d = lambda/4.0;
    double k = 2.0*M_PI/lambda;
    complex <double> i(0.0,1.0);
    double thetaprime = theta + txParams.orien;
    if (thetaprime < 0.0){
        thetaprime = 360 + thetaprime;
    }
    complex <double> psy = k * d * sin(phi * M_PI / 180) * cos(thetaprime * M_PI / 180);
    if ((thetaprime >= 270 && thetaprime < 360.0) || (thetaprime >=0 && thetaprime < 90.0)) {
        reflectorfactor = 2.0 * i * exp(-i * psy) * sin(psy);
    }
    return reflectorfactor;
}


complex <double> ph::arrayFactor(angle theta, angle phi,double fq, angle antOrien,
                            char beam, unsigned arrW, unsigned arrH)
{
    complex <double> xarray(0.0,0.0);
    complex <double> yarray(0.0,0.0);
    complex <double> arrayfactor(0.0,0.0);
    complex <double> i(0.0,1.0);
    complex <double> psy(0.0,0.0);
    complex <double> qsy(0.0,0.0);
    double lambda = c / fq;

    double d = lambda * 0.5;
    double k = 2.0 * M_PI / lambda;
    double alpha  = phi * M_PI / 180.0;
    double principal_angle = beam * M_PI / 12; // -5 -4 -3 ... 0 ... 3 4 5
    double beta = (theta + antOrien) * M_PI / 180;
    double alphaprime = M_PI / 2;
    double betaprime = principal_angle;
    double A = sin(alpha) * sin(beta);
    double Aprime = sin(alphaprime) * sin(betaprime);
    double B = sin(alpha) * cos(beta);
    double Bprime = sin(alphaprime) * cos(betaprime);
    psy = i * d * k * (A - Aprime);
    qsy = i * d * k * (B - Bprime);
    double modA = fmod((A - Aprime), 2);
    double modB = fmod((B - Bprime), 2);
    if ((modA == 0) & (modB != 0)){
        yarray = double(arrW) + 0.0 * i;
        xarray = (exp(qsy * double(arrH)) - 1.0) / (exp(qsy) - 1.0);
    }
    else if ((modA != 0) && (modB == 0)){
        yarray = (exp(psy * double(arrW)) - 1.0) / (exp(psy) - 1.0);
        xarray = double(arrH) + 0.0 * i;
    }
    else if ((modA == 0)&& (modB == 0)){
        yarray = double(arrW) + 0.0 * i;
        xarray = double(arrH) + 0.0 * i;
    }
    else {
        yarray = (exp(psy*double(arrW))-1.0)/(exp(psy)-1.0);
        xarray = (exp(qsy*double(arrH))-1.0)/(exp(qsy)-1.0);
    }

    arrayfactor = xarray*yarray;
    return arrayfactor;
}


complex <double> ph::arrayFactor(angle theta, angle phi, const ph::TxParams &txParams)
{
    complex <double> xarray(0.0,0.0);
    complex <double> yarray(0.0,0.0);
    complex <double> arrayfactor(0.0,0.0);
    complex <double> i(0.0,1.0);
    complex <double> psy(0.0,0.0);
    complex <double> qsy(0.0,0.0);
    double lambda = c / txParams.fq;

    double d = lambda * 0.5;
    double k = 2.0 * M_PI / lambda;
    double alpha  = phi * M_PI / 180.0;
    double principal_angle = txParams.beam * M_PI / 12; // -5 -4 -3 ... 0 ... 3 4 5
    double beta = (theta + txParams.orien) * M_PI / 180;
    double alphaprime = M_PI / 2;
    double betaprime = principal_angle;
    double A = sin(alpha) * sin(beta);
    double Aprime = sin(alphaprime) * sin(betaprime);
    double B = sin(alpha) * cos(beta);
    double Bprime = sin(alphaprime) * cos(betaprime);
    psy = i*d*k*(A-Aprime);
    qsy = i*d*k*(B-Bprime);
    double modA = fmod((A-Aprime),2);
    double modB = fmod((B-Bprime),2);
    if ((modA == 0) & (modB != 0)){
        yarray = double(txParams.arrW) + 0.0 * i;
        xarray = (exp(qsy * double(txParams.arrH)) - 1.0) / (exp(qsy) - 1.0);
    }
    else if ((modA != 0) && (modB == 0)){
        yarray = (exp(psy * double(txParams.arrW)) - 1.0) / (exp(psy) - 1.0);
        xarray = double(txParams.arrH) + 0.0 * i;
    }
    else if ((modA == 0)&& (modB == 0)){
        yarray = double(txParams.arrW) + 0.0 * i;
        xarray = double(txParams.arrH) + 0.0 * i;
    }
    else {
        yarray = (exp(psy*double(txParams.arrW))-1.0)/(exp(psy)-1.0);
        xarray = (exp(qsy*double(txParams.arrH))-1.0)/(exp(qsy)-1.0);
    }

    arrayfactor = xarray*yarray;
    return arrayfactor;
}


complex <double> ph::totaleArrayFactor(double theta, double phi, double fq, angle antOrien,
                                  char beam, unsigned arrW, unsigned arrH, ph::TxType type){
    complex <double> arrayfactor = ph::arrayFactor(theta, phi, fq, antOrien, beam, arrW, arrH);
    complex <double> dipolefactor = ph::dipoleFactor(phi);
    complex <double> reflectorfactor = ph::reflectorFactor(theta,phi, fq, antOrien);
    if (type == TxType::dipole){
        return dipolefactor;
    }
    else if (type == TxType::array){
        return dipolefactor*arrayfactor;
    }
    else if (type == TxType::dipoleRefl){
        return dipolefactor*reflectorfactor;
    }
    else if (type == TxType::arrayRefl){
        return dipolefactor*arrayfactor*reflectorfactor;
    }
    return 0;
}

double ph::electricalGain(complex<double> arrayFctr){
    return abs(arrayFctr);
}

double ph::powerGain(complex<double> arrayFctr){
    return 16.0/(3.0*M_PI)*pow(abs(arrayFctr),2);
}

complex <double> ph::totaleArrayFactor(double theta, double phi, const TxParams &txParams){
    complex <double> arrayfactor = ph::arrayFactor(theta, phi, txParams);
    complex <double> dipolefactor = ph::dipoleFactor(phi);
    complex <double> reflectorfactor = ph::reflectorFactor(theta,phi, txParams);
    if (txParams.type == TxType::dipole){
        return dipolefactor;
    }
    else if (txParams.type == TxType::array){
        return dipolefactor*arrayfactor;
    }
    else if (txParams.type == TxType::dipoleRefl){
        return dipolefactor*reflectorfactor;
    }
    else if (txParams.type == TxType::arrayRefl){
        return dipolefactor*arrayfactor*reflectorfactor;
    }
    return 0;
}


double ph::computeReflexionPer(double thetaI, double epsilonR)
{
    //    double R = (cos(thetaI) - sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)))
    //               /(cos(thetaI) + sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)));

    //  Now in the code thatai is the angle between the ray and the wall and not between
    //  the ray and the normal to the wall.
    //  Basicly thetai = pi/2 - thetai.
    //  Because of that cos and sin are inverted and we take their absolute value because of the angles given by Qt.

    return (abs(cos(thetaI)) - sqrt(epsilonR) * sqrt(1 - (1 / epsilonR) * pow(sin(thetaI), 2))) /
               (abs(cos(thetaI)) + sqrt(epsilonR) * sqrt(1 - (1 / epsilonR) * pow(sin(thetaI), 2)));
}


double ph::computeR(WholeRay *wholeRay)
{
    double R = 1;
//    for (WholeRay::iterator ray = wholeRay->begin(); ray != wholeRay->end() - 1; ray++ ) {
    for (WholeRay::iterator ray = wholeRay->begin(); ray != wholeRay->end() - 1; ray++){

        double thetaI = abs((*ray)->getTetai()-90);
//        cout << "thetaI [rad]: " << thetaI*M_PI/180 << endl;
        double epsilonWallRel = (*ray)->getEpsilon();
//        cout << "Initial R: " << ph::computeReflexionPer(thetaI * M_PI / 180 , epsilonWallRel) << endl;
        R *= ph::computeReflexionPer(thetaI * M_PI / 180 , epsilonWallRel);
    }
    return R;
}


double ph::currentTx(const double power, const tuple<width, height> antArry)
{
    return sqrt(2.0 * power / (std::get<0>(antArry) * std::get<1>(antArry) * r_a));
}


std::complex <double> ph::computeEMfield(const gsl::not_null<WholeRay *> rayLine,
                                    const std::tuple<width, height> antArry,
                                    double power,
                                    double wvNbr,
                                    double antOrien,
                                    char beam,
                                    TxType txType)
{
    //  One vector<ray*> is one multi-path componant, the size of the vector determine the n-level
    //  we are in, for each ray only the power in the last ray is transmitted to
    //  the receptor. As seen in the power formula, n rays -> n-1 additions to the power.

    //  This function gives the electrical field, generated by one MPC, at the receiver.
    //  The electric field is // to the dipole antenna since we only consider relections
    //  off the buildings. The electric field is not // for the reflexion with the ground
    //  though. This is taken into account in the function computePrx.

    complex <double> i(0.0, 1.0);
//    cout << "Number of rays in physics.cpp: " << rayLine->size() << endl;
    double totalLength = rayLine->totalLength();
//    cout << "Distance in physics.cpp: " << totalLength << endl;
    double R = ph::computeR(rayLine);
//    cout << "Perpendicular coeff in physics.cpp: " << R << endl;
    complex <double> Efield = 0.0;

    // Angle in degrees
    double angle_transmitter = rayLine->angleTx();
//    cout << "phi in physics.cpp rad: " << angle_transmitter*M_PI/180.0 << endl;
    complex<double> array_fctr = ph::totaleArrayFactor(angle_transmitter, 90, wvNbr * c / (2 * M_PI),
                                                   antOrien, beam, std::get<0>(antArry), std::get<1>(antArry),
                                                   txType);
//    cout << "AF in physics.cpp: " << array_fctr << endl;
    double Ia = currentTx(power, antArry);
//    cout << "Ia in physics.cpp: " << Ia << endl;
    complex<double> a = R * array_fctr * exp(-i * wvNbr * totalLength) / totalLength;
//    cout << "Beta in physics.cpp: " << wvNbr << endl;
    Efield = - i * ((z_0 * Ia) * a / (2.0 * M_PI));

    return Efield;
}


std::complex <double> ph::computeEMfield(const gsl::not_null<WholeRay*> rayLine, const TxParams &txParams)
{
    //  One vector<ray*> is one multi-path componant, the size of the vector determine the n-level
    //  we are in, for each ray only the power in the last ray is transmitted to
    //  the receptor. As seen in the power formula, n rays -> n-1 additions to the power.

    //  This function gives the electrical field, generated by one MPC, at the receiver.
    //  The electric field is // to the dipole antenna since we only consider relections
    //  off the buildings. The electric field is not // for the reflexion with the ground
    //  though. This is taken into account in the function computePrx.

    complex <double> i(0.0, 1.0);
    double totalLength = rayLine->totalLength();
    double R = ph::computeR(rayLine);
    complex <double> Efield = 0.0;

    // Angle in degrees
    double angle_transmitter = rayLine->angleTx();
    complex<double> array_fctr = ph::totaleArrayFactor(angle_transmitter, 90, txParams);
    double Ia = sqrt(2.0 * txParams.prx / (txParams.arrW * txParams.arrH * r_a)); // Ia could be changed for Beamforming application (add exp)
    complex<double> a = R * array_fctr * exp(-i * 2.0 * M_PI * txParams.fq * totalLength / c) / totalLength;

    Efield = - i * ((z_0 * Ia) * a / (2.0 * M_PI));

    return Efield;
}

std::complex <double> ph::inducedVoltage(const std::complex <double> field,
                                         const double anglerx,const double lambda)
{
    complex <double> voltage = lambda/M_PI*field*cos(M_PI/2*cos(anglerx))/sin(anglerx);
    return voltage;
}

double ph::firstMinIdx(const map<double, double> &fct, const double th, const unsigned range)
{

    auto it_max = fct.cend();
    map<double, double>::const_iterator it = fct.cbegin();
    map<double, double>::const_iterator itr_max;
    map<double, double>::const_iterator itr;
    bool found = false;
    double first = it->second;

    while (it != it_max && !found) {
        if (it->second/first <= th) {
            bool higher_than_it = true;
            itr_max = next(it, range + 1);
            itr = it;
            while (higher_than_it && itr != itr_max) {
                higher_than_it = (itr->second >= it->second);
                itr++;
            }
            if (higher_than_it) {
                found = true;
                return it->first;
            } /*else it = itr;*/
        }
        ++it;
    }
    return fct.end()->first;
}

void ph::fft(vector<cd> & a, bool invert) {
    int n = a.size();

    complex<double> comp(0,1);

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * M_PI / len * (invert ? -1 : 1);
//        cd wlen(cos(ang), sin(ang));
        cd wlen = exp(comp * ang);
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
