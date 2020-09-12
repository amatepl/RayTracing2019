#include "physics.h"

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
    return ampu * sqrt(1 - pow(u/ampu, 2)) * norm(angDistr) / (2 * M_PI);
}


std::complex<double> ph::angDistrMPC(const std::complex<double> &h, const double theta, const double spectrum)
{
    return 2 * M_PI * h / (spectrum * sin(theta * M_PI / 180.0)/ cos(theta * M_PI / 180));
}


double ph::angularSpread(const vector<double> &prxAngularSpread, const vector<double> &u)
{
    double prx = 0;
    double variance = 0;
    double mean = 0;

    for (unsigned i = 0; i < prxAngularSpread.size(); i++) {
        prx += prxAngularSpread.at(i);      // Has to be modified maybe give norm u as parameter.
        variance += pow(u.at(i), 2) * prxAngularSpread.at(i);
        mean += u.at(i) * prxAngularSpread.at(i);
    }

    return sqrt(variance/prx - pow(mean, 2));
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
    double lambda = C/fq;

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
    double lambda = C/txParams.fq;

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
    double lambda = C / fq;

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
    double lambda = C / txParams.fq;

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

    return (abs(sin(thetaI)) - sqrt(epsilonR) * sqrt(1 - (1 / epsilonR) * pow(cos(thetaI), 2))) /
               (abs(sin(thetaI)) + sqrt(epsilonR) * sqrt(1 - (1 / epsilonR) * pow(cos(thetaI), 2)));
}


double ph::computeR(WholeRay *wholeRay)
{
    double R = 1;
//    for (WholeRay::iterator ray = wholeRay->begin(); ray != wholeRay->end() - 1; ray++ ) {
    for (WholeRay::iterator ray = wholeRay->begin(); ray != wholeRay->end() - 1; ray++){

        double thetaI = abs((*ray)->getTetai());
        double epsilonWallRel = (*ray)->getEpsilon();
        R *= ph::computeReflexionPer(thetaI, epsilonWallRel);
    }
    return R;
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
    double totalLength = rayLine->totalLength();
    double R = ph::computeR(rayLine);
    complex <double> Efield = 0.0;

    // Angle in degrees
    double angle_transmitter = rayLine->angleTx();
    complex<double> array_fctr = ph::totaleArrayFactor(angle_transmitter, 90, wvNbr * C / (2 * M_PI),
                                                   antOrien, beam, std::get<0>(antArry), std::get<1>(antArry),
                                                   txType);
    double Ia = sqrt(2.0 * power / (std::get<0>(antArry) * std::get<1>(antArry) * r_a)); // Ia could be changed for Beamforming application (add exp)
    complex<double> a = R * array_fctr * exp(-i * wvNbr * totalLength) / totalLength;

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
    complex<double> a = R * array_fctr * exp(-i * 2.0 * M_PI * txParams.fq * totalLength / C) / totalLength;

    Efield = - i * ((z_0 * Ia) * a / (2.0 * M_PI));

    return Efield;
}

