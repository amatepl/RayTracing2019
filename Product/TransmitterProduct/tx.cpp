#include "tx.h"
#include <chrono>
#include <FFT>
#include <Core>
//#include "Share/physics.h"

Tx::Tx(int posX, int posY) : QPointF(posX, posY)
{
    m_type              = "Transmitter";
    m_zone              = buildCoverage();
    m_frequency         = 26e9;
    m_bandwidth         = 100e6;
    m_row               = 1;
    m_column            = 1;
    m_orientation       = 0;
    m_pr_orientation    = 0;
    lambda              = c / m_frequency;
    wvNbr               = 2.0 * M_PI / lambda;
    epsilonWallRel      = 4.5;
}

Tx::~Tx()
{
    cout << "Mathematical Transmitter Product Deleted." << endl;
}


void Tx::appendTree(MathematicalTreeProduct *tree)
{
    m_trees.push_back(tree);
}


void Tx::drawRays()
{

}


QPolygonF Tx::buildCoverage() const
{
    QPolygonF coverage;
    for (int i = 0; i < 16; i++) {
        coverage << QPointF(round(x() + m_radius * cos(M_PI * i / 8)), round(y() + m_radius * sin(M_PI * i / 8)));
    }
    return coverage;
}

//complex<double>
//Tx::computeImpulseReflection(WholeRay *ray_line, QLineF local_region)
//{
//    complex <double> i(0.0, 1.0);
////    int amountSegment = ray_line->size();
////    double completeLength = 0.0;
////    double R = 1;
////    Ray *current_ray;

////    for (int i = 0; i < amountSegment; i++) {
////        current_ray = ray_line->at(i);
////        if (i != amountSegment - 1) {
////            double thetaI = abs(current_ray->getTetai());
////            R *= computeReflexionPer(thetaI * 2 * M_PI / 180, epsilonWallRel);
////        }
////        completeLength += current_ray->getMeterLength();
////    }
//    double completeLength = ray_line->totalLength();
//    double R = ph::computeR(ray_line);
//    double a = R / completeLength;

//    // Angle in degrees
//    double angle_transmitter = ray_line->back()->angle();
//    double angle_receiver = ray_line->front()->angle();
//    QLineF beta(QPointF(.0,.0),QPointF(2.0 * M_PI / lambda,.0));
//    beta.setAngle(angle_receiver);
//    double scalar_beta_r = beta.p2().x()*local_region.p2().x() + beta.p2().y()*local_region.p2().y();
//    complex<double> array_factor = ph::totaleArrayFactor(angle_transmitter, 90,
//                                                         m_frequency, m_orientation,
//                                                         m_pr_orientation, m_column,
//                                                         m_row, static_cast<ph::TxType>(m_kind));
//    double tau = completeLength/c;

//    complex<double> impulse_r = a * array_factor
//                                * exp(-i * scalar_beta_r)
//                                * exp(-i * 2.0*M_PI * std::complex<double>(m_frequency * tau));
//    return impulse_r;
//}


void Tx::estimateCh(QPointF *rx, complex <double> field, WholeRay *ray)
{
    m_chsData.at(rx).dstnc = QLineF(*this, *rx).length()*px_to_meter;
    m_los_factor[rx] = 0;
    QLineF receiver_speed = receivers_speed[rx];
    QLineF beta(QPointF(.0, .0), QPointF(2.0 * M_PI / lambda, 0.0));

    const double completeLength = ray->totalLength();
    const double angleRx = ray->angleRx();

    Data &chData = m_chsData.at(rx);

    // Tau
    double tau = completeLength * 1e9/c; // [ns]
    tau = round(tau * 1e4) / 1e4; // [precision of 0.1 ps]

    // Impulse response
    complex <double> voltage = ph::inducedVoltage(field,M_PI/2,lambda);
//    cout << "Induced voltage for reflections" << voltage << endl;
    chData.indVoltage += voltage;
    chData.impulseResp[tau] += voltage;
    chData.intPattern[angleRx-180] += voltage;

    if (ray->size() == 1) chData.losFactor = norm(voltage);
    else chData.nlosFactor += norm(voltage);

    beta.setAngle(angleRx);
//        beta.setAngle(angleRx + 180); ???

    double theta = angleRx;
    if (receiver_speed.length() > 0.0){
        theta = beta.angleTo(receiver_speed);
    }

    if (m_chsData[rx].maxSpeed < (abs(rays_speed[ray]) + receiver_speed.length())) {
        m_chsData[rx].maxSpeed = abs(rays_speed[ray]) + receiver_speed.length();
    }
    double u = ph::uMPC(wvNbr, theta);
    double w = rays_speed[ray]*wvNbr + receiver_speed.length()*u;

    complex<double> angularDistr = ph::angDistrMPC(voltage, theta, u);
    complex<double> dopplerDistr = ph::angDistrMPC(voltage, theta, w);
    double prxAngSpctr = ph::prxSpctrMPC(angularDistr, wvNbr, u);
    double prxDopSpctr = ph::prxSpctrMPC(dopplerDistr, wvNbr * receiver_speed.length(), w);

    chData.angularDistrMap[round(u * 1e2)/1e2] += angularDistr;
    chData.dopplerDistrMap[round(w * 1e2)/1e2] += dopplerDistr;

    chData.prxAngularSpctrMap[round(u * 1e2)/1e2] =
        ph::prxSpctrMPC(chData.angularDistrMap[round(u * 1e2)/1e2], wvNbr, u);

    chData.prxDopplerSpctrMap[round(w * 1e2)/1e2] =
        ph::prxSpctrMPC(chData.dopplerDistrMap[round(w * 1e2)/1e2], wvNbr * receiver_speed.length(), w);

    // Save Data
    chData.u.push_back(u);
    chData.w.push_back(w);
    chData.angularDistr.push_back(angularDistr);
    chData.dopplerDistr.push_back(dopplerDistr);
    chData.prxAngularSpctr.push_back(prxAngSpctr);
    chData.prxDopplerSpctr.push_back(prxDopSpctr);

    // receivers_speed.translate(- m_receiver_speed.p1());   Check if necessary
    // m_ray_speed.translate(- m_ray_speed.p1());       Chack if necessary

    // A REVOIRE
//    double angle = receiver_speed.angleTo(*ray->front());
//    rays_speed[ray] += receiver_speed.length()*cos(angle*M_PI/180.0);
    // QLineF resultant_speed(QPointF(0.0, 0.0), m_receiver_speed.p2() - m_ray_speed.p2());
    //double omega = - (beta.p2().x() * resultant_speed.p2().x() + beta.p2().y() * resultant_speed.p2().y());

    double omega = rays_speed[ray]*wvNbr - receiver_speed.length()*u;
    omega = round(omega * 1e4) / 1e4;

    chData.dopplerSpctr[omega] += voltage;

//    normalizePrxSpctr(m_chsData.at(rx).prxDopplerSpctr);

}

QLineF
Tx::vecSpeed(double length, double angle)
{
    QLineF vector(QPointF(0.,0.),QPointF(10.,0.));
    vector.setLength(abs(length));
    if (length > 0){
        vector.setAngle(angle+180);
    }
    else vector.setAngle(angle);
    return vector;
}

QLineF
Tx::resultant(QLineF line1, QLineF line2)
{
    line1.translate(-line1.p1());
    line2.translate(-line2.p1());
    QLineF res(QPointF(.0,.0), line1.p2()+line2.p2());
    return res;
}

//complex <double>
//Tx::computeImpulseGroundReflection(QPointF *copy_receiver,
//                                                               double direction,
//                                                               QLineF local_region)
//{
//    double distance = this->distance(copy_receiver);
//    double thetaG = atan((distance / 2) / ant_hght);
//    double thetaI = M_PI - thetaG;
//    double R = computeReflexionPar(thetaG, epsilonWallRel);
//    double completeLength = sqrt(4*pow(ant_hght,2)+pow(distance,2));
//    complex <double> i(0.0, 1.0);
//    double a = R  / completeLength;
//    complex<double> array_factor = ph::totaleArrayFactor(direction,thetaI*180.0/M_PI,
//                                                         m_frequency, m_orientation,
//                                                         m_pr_orientation, m_column,
//                                                         m_row, static_cast<ph::TxType>(m_kind));

//    double tau = completeLength/c;
//    double local_region_angle = local_region.angle() + 180.0;
//    local_region_angle = fmod(local_region_angle, 360.0);
//    double angle = (direction - local_region_angle)*M_PI/180.0;
//    complex<double> impulse_r = a * array_factor
//                                * exp(-i * (2.0 * M_PI / lambda) * local_region.length() * cos(angle) * cos(M_PI/2-thetaG))
//                                * exp(-i * 2.0*M_PI * std::complex<double>(m_frequency * tau));
//    return impulse_r;
//}

complex <double> Tx::computeEfieldGround(const QPointF *receiver,
                                                                    const double direction,
                                                                    const bool properties)
{
    double pi = acos(0)*2;
    // Compute the electrical field, at the receiver, induced by the ray reflected off the ground.
    double distance = this->distance(receiver); // conversion (1px == 2cm)
//    cout << "Distance in tx.cpp for ground: " << distance << endl;
    double thetaG = atan((distance / 2) / ant_hght);
//    cout << "Theta_ig in tx.cpp for ground: " << thetaG << endl;
    double thetaI = pi - thetaG;
//    cout << "Theta_g in tx.cpp for ground: " << thetaI << endl;
    double R = computeReflexionPar(thetaG, epsilonWallRel);
//    cout << "Gamma_par in tx.cpp for ground: " << R << endl;
    double completeLength = sqrt(4 * pow(ant_hght, 2) + pow(distance, 2)); //distance / sin(thetaG);
//    cout << "d_g in tx.cpp for ground: " << completeLength << endl;
    complex <double> i(0.0, 1.0);

    double Ia = sqrt(2 * m_power / (m_row * m_column * r_a)); // Ia could be changed for Beamforming application
//    cout << "Ia in tx.cpp for ground: " << Ia << endl;
    complex<double> array_factor = ph::totaleArrayFactor(direction, thetaI * 180.0 / pi,
                                                         m_frequency, m_orientation,
                                                         m_pr_orientation, m_column,
                                                         m_row, static_cast<ph::TxType>(m_kind));
//    cout << "AF in tx.cpp for ground: " << array_factor << endl;
    double beta = 2*pi/lambda;
//    cout << "phi in tx.cpp for ground: " << direction << endl;
    complex<double> a = R * array_factor * exp(-i * beta * completeLength) / completeLength;
//    cout << "Beta in tx.cpp for ground: " << beta << endl;
    complex <double> Efield = -i * a * (z_0 * Ia) / (2 * pi);

    QLineF receiver_speed = receivers_speed[receiver];
    QLineF betavec(QPointF(.0, .0), QPointF(2.0 * pi / lambda, 0.0));

    if (properties)
    {
        double tau = completeLength * 1e9/c; // [ns]
        tau = round(tau*1e4)/1e4; // [precision of 0.1 ps]
//        m_receiversImpulse[receiver][tau] += lambda*Efield*cos(M_PI/2*cos(thetaI))/(M_PI*sin(thetaI));
        complex<double> induced_voltage = ph::inducedVoltage(Efield,thetaI,lambda);
        m_chsData[receiver].impulseResp[tau] += induced_voltage;
        m_chsData[receiver].indVoltage += induced_voltage;
        // m_chsData[receiver].intPattern[direction] += induced_voltage*exp(-i*beta*cos(M_PI/2-thetaG));
        m_chsData[receiver].indVoltageGnd = induced_voltage;
        m_chsData[receiver].angleGroundX = direction;
        m_chsData[receiver].angleGroundZ = (M_PI/2-thetaG)*180/M_PI;
//        cout << "Induced voltage for ground: " << induced_voltage << endl;
        m_chsData[receiver].nlosFactor += norm(induced_voltage);
//        double shift = (direction - m_receiver_speed.angle()) * M_PI / 180.0;
//        double omega = -2.0 * M_PI * m_receiver_speed.length() * cos(shift) * cos(M_PI/2-thetaG) / lambda;
//        m_dopplerSpectrum[receiver][omega] += a;
//        m_chsData[receiver].dopplerSpctr[omega] += a;

        double angleRx = 180 + direction;
        Data &chData = m_chsData[receiver];

        betavec.setAngle(angleRx);

        double theta = angleRx;
        if (receiver_speed.length() > 0.0){
            theta = betavec.angleTo(receiver_speed);
        }
        // Put computed data into channels data.
        double u = ph::uMPC(wvNbr, theta);
        double w = receiver_speed.length()*u;

        complex<double> angularDistr = ph::angDistrMPC(induced_voltage, angleRx, u);
        double prxAngSpctr = ph::prxSpctrMPC(angularDistr, wvNbr, u);

        complex<double> dopplerDistr = ph::angDistrMPC(induced_voltage, theta, w);
        double prxDopSpctr = ph::prxSpctrMPC(dopplerDistr, wvNbr * receiver_speed.length(), w);

        // Save Data
        chData.u.push_back(u);
        chData.angularDistr.push_back(angularDistr);

        chData.angularDistrMap[round(u * 1e2)/1e2] += angularDistr;
        chData.dopplerDistrMap[round(w * 1e2)/1e2] += dopplerDistr;

        chData.prxAngularSpctr.push_back(prxAngSpctr);

        chData.prxAngularSpctrMap[round(u * 1e2)/1e2] =
            ph::prxSpctrMPC(chData.angularDistrMap[round(u * 1e2)/1e2], wvNbr, u);

        chData.prxDopplerSpctrMap[round(w * 1e2)/1e2] =
            ph::prxSpctrMPC(chData.dopplerDistrMap[round(w * 1e2)/1e2], wvNbr * receiver_speed.length(), w);

    }

    return Efield;
}

double Tx::distance(const QPointF *receiver)
{

    // ??????
    //  For display, it calcultes the direct Euclidian distance from the receiver
    //  to the emettor, displays the results on the UI
    //

    double x1 = x();
    double y1 = y();
    double x2 = receiver->x();
    double y2 = receiver->y();

    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)) * px_to_meter; // conversion (1px == 1dm)
}

//complex<double>
//Tx::computeImpulseDiffraction(WholeRay *ray_line, QLineF local_region)
//{
//    double direct_dist = sqrt(pow(ray_line->at(1)->p1().x() - ray_line->at(0)->p2().x(), 2)
//                              + pow(ray_line->at(1)->p1().y() - ray_line->at(0)->p2().y(), 2)); //convertir px to cm?
//    complex<double> F = 0.0;
//    complex <double> i(0.0, 1.0);

//    // The length defference between the path going through the tip of the obstacle, and the direct path.
//    double delta_r = (ray_line->at(0)->length() + ray_line->at(1)->length() - direct_dist) * px_to_meter;
//    double nu = sqrt(2 * 2 * M_PI / lambda * delta_r / M_PI);

//    // The ITU's approximation for |F(nu)|^2
//    double absF = pow(10, -6.9 / 40) / sqrt((sqrt(pow(nu - 0.1, 2) + 1) + nu - 0.1));
//    double argF = -M_PI / 4 - pow(nu, 2) * M_PI / 2;
//    F = absF * exp(i * argF);

//    Line directRay(ray_line->at(0)->p2(), ray_line->at(1)->p1());
//    directRay.setScale(px_to_meter);
//    double angle = ray_line->at(1)->angle();
//    QLineF beta(QPointF(.0,.0),QPointF(2.0 * M_PI / lambda,.0));
//    beta.setAngle(ray_line->at(0)->angle());
//    double scalar_beta_r = beta.p2().x()*local_region.p2().x() + beta.p2().y()*local_region.p2().y();
//    double tau = (ray_line->at(0)->getMeterLength()+ray_line->at(1)->getMeterLength())/c;
//    complex<double> array_factor = ph::totaleArrayFactor(angle,90,
//                                                     m_frequency, m_orientation,
//                                                     m_pr_orientation, m_column,
//                                                     m_row, static_cast<ph::TxType>(m_kind));

//    complex<double> impulse_r = array_factor*F
//                                *exp(-i * scalar_beta_r)
//                                *exp(-i * 2.0*M_PI * std::complex<double>(m_frequency * tau))
//                                /directRay.getMeterLength();
//    return impulse_r;
//}

complex<double> Tx::computeDiffractedEfield(QPointF *receiver,
                                                                        WholeRay *rayLine,
                                                                        bool properties)
{

    // Direct distance between the receiver and the transmitter
//    double direct_dist = sqrt(pow(transmitter->getPosition().x()-m_Receiver->getPosX(),2)
//                              + pow(transmitter->getPosition().y()-m_Receiver->getPosY(),2)); //convertir px to cm?

    Line direct_ray(*this,*receiver);
    direct_ray.setScale(px_to_meter);
    double direct_dist = direct_ray.length();// rayLine->directDistance(); convertir px to cm?

    complex<double> Efield = 0.0;
    complex<double> F = 0.0;
    complex <double> i(0.0, 1.0);

    // The length defference between the path going through the tip of the obstacle, and the direct path.
    double d_diff = (rayLine->at(0)->length() + rayLine->at(1)->length())*px_to_meter;
//    cout << "d_diff: " << d_diff << endl;
    double delta_r = d_diff - (direct_dist * px_to_meter);
//    cout << "delta_r: " << delta_r << endl;
    double nu = sqrt(2 * 2 * M_PI / lambda * delta_r / M_PI);
//    cout << "nu: " << nu << endl;
    // The ITU's approximation for |F(nu)|^2

    double absF = pow(10, -6.9 / 40) / sqrt((sqrt(pow(nu - 0.1, 2) + 1) + nu - 0.1));
    double argF = -M_PI / 4 - pow(nu, 2) * M_PI / 2;
    F = absF * exp(i * argF);
//    cout << "F_nu: " << F << endl;

    double angle = rayLine->at(1)->angle();
    double angle_end = rayLine->at(0)->angle();
//    cout << "Phi_diff [rad]: " << angle*M_PI/180 << endl;
    complex<double> array_factor = ph::totaleArrayFactor(angle,90,
                                                     m_frequency, m_orientation,
                                                     m_pr_orientation, m_column,
                                                     m_row, static_cast<ph::TxType>(m_kind));
    direct_ray.setScale(px_to_meter);
    complex<double> a = F * array_factor * (exp(-i * (2.0 * M_PI / lambda) * d_diff)
                        / d_diff);
    double Ia = sqrt(2 * m_power / (m_row*m_column * r_a)); // Ia could be changed for Beamforming application (add exp)
    Efield = -i  * a * ((z_0 * Ia) / (2 * M_PI));
//    cout << "E_diff: " << Efield << endl;
    if (properties){
//        double completeLength = rayLine->at(1)->getMeterLength() + rayLine->at(0)->getMeterLength();
//        double tau = completeLength * 1e9/c; // [ns]
//        tau = round(tau*1e4)/1e4; // [precision of 0.1 ps]
//        complex<double> induced_voltage = ph::inducedVoltage(Efield,M_PI/2,lambda);
//        m_chsData[receiver].impulseResp[tau] += induced_voltage;
//        m_chsData[receiver].impulseResp[angle_end] += induced_voltage;
    }
    return Efield;
}


void Tx::chooseBeam(QPointF *receiver)
{

    double powerAtReceiver = 0;
    complex<double> emField = 0;
    double sumAbsE = 0;
    complex<double> groundField = 0;
    char chosenBeam = -5;

    vector<WholeRay *> wholeRays = m_receiversRays[receiver];

    for (int i = -5; i < 5; i++) {
//        m_pr_orientation = i;
        emField = 0;
        sumAbsE = 0;

        for (unsigned j = 0; j < wholeRays.size(); j++) {
            WholeRay *wholeRay  = wholeRays.at(j);

            if (wholeRay->at(0)->getDiffracted()) {     // The ray is a diffracted one.

                complex<double> e = computeDiffractedEfield(receiver,wholeRay,false);
                emField += e;
                sumAbsE += abs(e);

            } else {                                    // The ray was reflected.

//                complex<double> EMfield = computeEMfield(wholeRay, receiver,false);
                tuple<int, int> arrSize = {m_column, m_row};
                complex<double> EMfield = ph::computeEMfield(wholeRay, arrSize, m_power, wvNbr,
                                                             m_orientation, m_pr_orientation,
                                                             static_cast<ph::TxType>(m_kind));

                if (wholeRay->size() == 1) {
                    // Adding the ground component
                    double angle_transmitter = wholeRay->back()->angle();
                    groundField = computeEfieldGround(receiver,angle_transmitter,false); // Compute the electrical field from the ray reflected off the ground
                }

                emField += EMfield;
                sumAbsE += abs(EMfield);
            }
        }

        if (computePrx(emField,groundField,receiver) > powerAtReceiver) {

            powerAtReceiver = computePrx(emField,groundField,receiver);
            chosenBeam = i;
            m_receiversField[receiver] = emField;
            m_rxsSumAbsE[receiver] = sumAbsE + abs(groundField);
            m_receiversGroundField[receiver] = groundField;

        }
    }

    m_pr_orientation = chosenBeam;
    m_chosenBeams[receiver] = true;
}


void
Tx::comput4FixedBeam(QPointF *receiver)
{
    bool diffracted = false;
    m_receiversField[receiver] = 0;
    m_receiversGroundField[receiver] = 0;
    m_rxsSumAbsE[receiver] = 0;
    complex<double> EMfield;
    for (unsigned i = 0; i < m_receiversRays[receiver].size(); i++)
    {
//        cout << "-------------------------------------------" << endl;
        WholeRay *wholeRay = m_receiversRays[receiver].at(i);

        if (wholeRay->at(0)->getDiffracted())
        {
            map<QPointF *, map<double, double>>::iterator it;
            //m_ray_speed = ray_speeds[wholeRay];
            EMfield = computeDiffractedEfield(receiver,wholeRay,true);
            m_receiversField[receiver] += EMfield;
            m_rxsSumAbsE[receiver] += abs(EMfield);
            diffracted = true;

        } else {
            //m_ray_speed = ray_speeds[wholeRay];
            //m_ray_speed.setLength(m_ray_speed.length()/3.6);

            tuple<int, int> arrSize = {m_column, m_row};
//            double wvNbr = 2.0 * M_PI / lambda;
//            complex<double> EMfield = computeEMfield(wholeRay, receiver,true);
            EMfield = ph::computeEMfield(wholeRay, arrSize, m_power, wvNbr,
                                                     m_orientation, m_pr_orientation,
                                                         static_cast<ph::TxType>(m_kind));
//            cout << "E_o: " << EMfield << endl;

            if (wholeRay->size() == 1) {
                // Adding the ground component
                double angle_transmitter = wholeRay->back()->angle();
                m_receiversGroundField[receiver] = computeEfieldGround(receiver, angle_transmitter, true); // Compute the electrical field from the ray reflected off the ground
//                cout << "E_g: " << m_receiversGroundField[receiver] << endl;
            }
            m_receiversField[receiver] += EMfield;
            m_rxsSumAbsE[receiver] += abs(EMfield);

        }
        estimateCh(receiver,EMfield,wholeRay);
    }


//    ph::normalizeMap<map<double, double>(m_chsData.at(receiver).impulseResp);
}

void Tx::dontChoseBeam(QPointF *receiver)
{
    m_chosenBeams[receiver] = true;
}


void Tx::freazeBeams()
{
    m_beamsFrozen = true;
}


double Tx::computePrx(complex <double> totalEfield, complex<double> groundField, QPointF* receiver)
{
    // Compute the power at the receive antenna with the total electric field induced by all MPC
    double distance = this->distance(receiver);
    double thetaI = atan(ant_hght/(distance/2))+M_PI/2;
    complex <double> Voc = (lambda/M_PI)*(totalEfield + groundField*(cos(M_PI/2*cos(thetaI))/sin(thetaI)));
    double Prx = 1.0 / (8.0 * r_a) * norm(Voc);
    return Prx;
}

double Tx::computePrx(QPointF* receiver)
{
    // Compute the power at the receive antenna with the total electric field induced by all MPC
    complex<double> Voc;
    for (auto &imp: m_chsData[receiver].impulseResp){
        Voc += imp.second;
    }
//    cout << "Voltage: " << Voc << endl;
    double Prx = 1.0 / (8.0 * r_a) * norm(Voc);
//    cout << "Prx: " << Prx << endl;
    return Prx;
}

double Tx::getRxPrx(QPointF *rx)
{
    Tx::EFields fields = computeEFields(rx);
    return computePrx(fields.plainEField, fields.reflEField, rx);
//    return m_chsData[rx].prx;
}

double Tx::dBm(double power)
{
    return 10 * (log10(power/0.001));
}


//double Tx::computeReflexionPer(double thetaI, double epsilonR) const
//{
////    double R = (cos(thetaI) - sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)))
////               /(cos(thetaI) + sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)));

//    //  Now in the code thatai is the angle between the ray and the wall and not between
//    //  the ray and the normal to the wall.
//    //  Basicly thetai = pi/2 - thetai.
//    //  Because of that cos and sin are inverted and we take their absolute value because of the angles given by Qt.

//    double R = (abs(sin(thetaI)) - sqrt(epsilonR) * sqrt(1 - (1 / epsilonR) * pow(cos(thetaI), 2))) /
//               (abs(sin(thetaI)) + sqrt(epsilonR) * sqrt(1 - (1 / epsilonR) * pow(cos(thetaI), 2)));
//    return R;
//}


double Tx::computeReflexionPar(double thetaI, double epsilonR) const
{
    double R = (cos(thetaI) - (1 / sqrt(epsilonR)) * sqrt(1 - (1 / epsilonR) * pow(sin(thetaI), 2))) /
               (cos(thetaI) + (1 / sqrt(epsilonR)) * sqrt(1 - (1 / epsilonR) * pow(sin(thetaI), 2)));
    return R;
}


vector<WholeRay *> Tx::getRays()
{
    // ???
    return m_wholeRays;
}


void Tx::notifyObservables()
{
//    for (unsigned int i = 0; i < m_productObservable.size(); i++) {
//        m_productObservable.at(i)->notify();
//    }
}


void Tx::clearAll(){
    //map<QPointF *,vector<vector<Ray *>*>>::iterator rays;
    vector<WholeRay *> whole_rays;
    WholeRay *tmp;
    for (const auto  &rays: m_receiversRays){
        whole_rays = rays.second;
//        for (unsigned i = 0; i<whole_rays.size(); i++){
//            tmp = whole_rays.at(i);
//            for (unsigned j = 0; j< tmp->size();j ++) {
//                delete tmp->at(j);
//            }
//            delete whole_rays.at(i);
//        }
        for (auto &wholeRay: whole_rays) {
            wholeRay->clear();
        }
        whole_rays.clear();
    }
    m_receiversRays.clear();
    m_txImgs.clear();
}

void Tx::addTxImg(ProductObserver *txImg)
{
    m_txImgs.push_back(txImg);
}

vector<QPointF> Tx::pathLossPoints() const
{
    vector<QPointF> pl_points; // Path loss (pl) points
    QPolygonF coverage = buildCoverage();
    QRectF bounding_rect = coverage.boundingRect();
                               // Bounding rect of the coverage zone
    int width = bounding_rect.width();
    int height = bounding_rect.height();
    QPointF tmp_point = bounding_rect.topLeft();
                               // Starting point
    int num_points = 1000;//px_to_meter;
                               // Number of considered points
    int range_x = width/num_points;
    int range_y = height/num_points;
    for (int i = 0; i <= num_points; i++)
    {
        for (int j = 0; j <= num_points; j++)
        {
            tmp_point = bounding_rect.topLeft() + QPointF(i*range_x,j*range_y);
                                // Scan point inside de bounding rect
            if (m_zone.containsPoint(tmp_point,Qt::OddEvenFill))
            {
                if (tmp_point.x() > 0 && tmp_point.y() > 0){
                                // tmp_point is inside the coverage zone
                    pl_points.push_back(tmp_point);
                                    // add tmp_point inside the pl_points
                }
            }
        }
    }
    return pl_points;
}

bool Tx::detect(const QPointF &p)
{
    return m_zone.containsPoint(p, Qt::OddEvenFill);
}

void Tx::link(const QPointF &p, WholeRay *wholeRay)
{
    wholeRay->push_back(m_rayFactory->createRay(*this, p));
    m_receiversRays[&p].push_back(wholeRay);

}

void Tx::detectAndLink(const QPointF &p)
{
    if(detect(p) && m_rayFactory != nullptr){
        WholeRay *wholeRay = new WholeRay;
        link(p, wholeRay);
    }
}
// ---------------------------------------------------- TxInterface -------------------------------------------------------------------


void Tx::newProperties(QPointF new_position, double orientation)
{
    m_graphic->notifyToGraphic(&new_position, orientation);
}


// ---------------------------------------------------- MathematicalProduct -------------------------------------------------------------------
void Tx::setPosX(int posX) {
    setX(posX);
}
void Tx::setPosY(int posY) {
    setY(posY);
}

void Tx::update(QGraphicsItem *graphic)
{
    QPointF direction(graphic->scenePos().x() - x(), graphic->scenePos().y() - y());
    m_zone.translate(direction);
    setX(graphic->scenePos().x());
    setY(graphic->scenePos().y());
    setOrientation(graphic->rotation());
    notifyObservables();

}


void Tx::openDialog(QWidget *)
{
    new DialogTx(this);
}

void Tx::setScale(float scale)
{
    MathematicalProduct::setScale(scale);
    m_radius = m_radius / px_to_meter;
    m_zone  = buildCoverage();
}

void Tx::clearChData(QPointF *rx)
{
    m_chsData[rx].fq = 0;
    m_chsData[rx].bw = 0;
    m_chsData[rx].prx = 0;
    m_chsData[rx].maxSpeed = 0;
    m_chsData[rx].eField = 0;
    m_chsData[rx].impulseResp.clear();
    m_chsData[rx].indVoltage = 0;
    m_chsData[rx].dopplerSpctr.clear();
    m_chsData[rx].pathLossP = 0;
    m_chsData[rx].interference = 0;
    m_chsData[rx].angularSpred = 0;
    m_chsData[rx].dopplerSpread = 0;
    m_chsData[rx].u.clear();
    m_chsData[rx].angularDistr.clear();
    m_chsData[rx].prxAngularSpctr.clear();
    m_chsData[rx].prxAngularSpctrMap.clear();
    m_chsData[rx].prxDopplerSpctrMap.clear();
    m_chsData[rx].w.clear();
    m_chsData[rx].dopplerDistr.clear();
    m_chsData[rx].prxDopplerSpctr.clear();
    m_chsData[rx].nlosFactor = 0;
    m_chsData[rx].losFactor = 0;
    m_chsData[rx].spaceCrltnMap.clear();
    m_chsData[rx].deltaZ.clear();
    m_chsData[rx].spaceCrltn.clear();
    m_chsData[rx].fqResp.clear();
    m_chsData[rx].intPattern.clear();
    m_chsData[rx].indVoltageGnd = 0.0;
    m_chsData[rx].angleGroundX = 0;
    m_chsData[rx].angleGroundZ = 0;
    m_chsData[rx].angularDistrMap.clear();
    m_chsData[rx].dopplerDistrMap.clear();

}


void Tx::deleteRays(QPointF *rx)
{
    if (m_receiversRays.count(rx)) {
        for (unsigned int i = 0; i < m_receiversRays[rx].size(); i++) {
            delete m_receiversRays[rx].at(i);
        }
        m_receiversRays[rx].clear();
    }
}

// ---------------------------------------------------- ProductObserver -------------------------------------------------------------------


Data *Tx::update(QPointF *receiver, const QLineF movement)
{
    //      The trasnmitter is updated every time an receiver moves

    // Clear data corresponding to the receiver calling the update
    clearChData(receiver);

    m_receiversField[receiver] = 0;
    m_rxsSumAbsE[receiver] = 0;
    m_los_factor[receiver] = 0.0;
    m_nlos_factor[receiver] = 0.0;
    rays_speed.erase(rays_speed.begin(), rays_speed.end());
    m_receiversImpulse.erase(receiver);
    m_dopplerSpectrum.erase(receiver);
    receivers_speed[receiver] = movement;
    receivers_speed[receiver].setLength(movement.length()/3.6);
    //m_ray_speed = QLineF(QPointF(0.0,0.0),QPointF(0.0,0.0));

    m_chosenBeams[receiver] = false;

    if (m_receiversRays.count(receiver)) {
        for (unsigned int i = 0; i < m_receiversRays[receiver].size(); i++) {
//            for (unsigned int j = 0; j < m_receiversRays[receiver].at(i)->size(); j++) {
//                delete m_receiversRays[receiver].at(i)->at(j);
//            }
            delete m_receiversRays[receiver].at(i);
        }
//        for (auto wholeRay: m_receiversRays[receiver]){
//            delete [] wholeRay;
//        }
        m_receiversRays[receiver].erase(m_receiversRays[receiver].begin(),
                                        m_receiversRays[receiver].end());
        m_receiversRays[receiver].shrink_to_fit();
    }


    const QPointF &pos = *receiver;

    detectAndLink(pos);

//    if (m_zone.containsPoint(pos, Qt::OddEvenFill)) {
//        //      The receiver is in the illumination zone

//        WholeRay *wholeRay = new WholeRay;
//        wholeRay->push_back(m_rayFactory->createRay(*this, pos));
//        m_receiversRays[receiver].push_back(wholeRay);
//    }

    notifyObservers(receiver, movement);

    compute(receiver);

    return getChData(receiver);
}

void Tx::notifyObservers(QPointF *rx, const QLineF mvmnt)
{
    for (auto &txImg: m_txImgs) {
        txImg->update(rx, mvmnt);
    }
}

void Tx::attachObservable(QPointF *productObservable)
{
    m_productObservable.push_back(productObservable);
    m_chosenBeams[productObservable] = false;
}


void Tx::drawRays(QPointF *productObservable, bool draw)
{
    if (draw) {
        for (unsigned int i = 0; i < m_receiversRays[productObservable].size(); i++) {
            for (unsigned j = 0 ; j < m_receiversRays[productObservable].at(i)->size(); j++) {
                m_receiversRays[productObservable].at(i)->at(j)->draw();
            }
        }
    } else {
        for (unsigned int i = 0; i < m_receiversRays[productObservable].size(); i++) {
            for (unsigned int j = 0; j < m_receiversRays[productObservable].at(i)->size(); j++) {
                m_receiversRays[productObservable].at(i)->at(j)->erase();
            }
        }
    }
}


Data * Tx::getChData(QPointF *rx)
{
    // Normalize PAS
    map<double, double> testPAS = m_chsData[rx].prxAngularSpctrMap;
    vector<double> testPASVec = m_chsData[rx].prxAngularSpctr;
    for (auto &e: m_chsData[rx].prxAngularSpctrMap) {
        e.second = e.second/m_chsData[rx].prxAngularSpctrMap.size();
    }
    for (auto &e: m_chsData[rx].prxDopplerSpctrMap) {
        e.second = e.second/m_chsData[rx].prxDopplerSpctrMap.size();
    }
//    double max = 0;
//    for (const auto &e: m_chsData[rx].prxAngularSpctrMap){
//        if (max < abs(e.second)) max = abs(e.second);
//    }

//    for (auto &e: m_chsData[rx].prxAngularSpctrMap) {
//        e.second = (e.second / max);
//    }

//    for (double &e: m_chsData[rx].prxAngularSpctr) {
//        e += 1;
//    }

    // Rice Factor
//    m_chsData[rx].riceFactor = 10*log10(m_los_factor[rx]/m_nlos_factor[rx]);

    // Angular Spread
//    m_chsData[rx].angularSpred = ph::angularSpread(m_chsData[rx].prxAngularSpctr, m_chsData[rx].u, wvNbr);

    // Doppler Spread
//    double speed = receivers_speed[rx].length();
//    m_chsData[rx].dopplerSpread = ph::angularSpread(m_chsData[rx].prxDopplerSpctr, m_chsData[rx].w, speed * wvNbr);

//    Eigen::FFT<double> fft;

//    // Frequency response
//    vector<double> h;
//    vector<double> t;
//    for (auto e: m_chsData[rx].impulseResp) {
//        t.push_back(e.first);
//        h.push_back(abs(e.second));
//    }
//    if (t.size()) h = ph::upsample<double, double>(t, h, 0, t.back(), 1);
//    vector<complex<double>> fqResp ;

//    if ( h.size() > 1) fft.fwd(fqResp, h);

//    double fq = 0;
//    for (const auto &e: fqResp) {
//        m_chsData[rx].fqResp[fq] = e;
//        fq++;
//    }

    // FFT
//    vector <complex <double>> test;
//    vector<complex<double>> out;
//    vector <double> out2;

//    vector <double> ulocal;
//    for (auto &key: m_chsData[rx].prxAngularSpctrMap) {
//        test.push_back(key.second);
//        ulocal.push_back(key.first);
//    }

//    vector<complex<double>> upsampledPAS = ph::upsample<double, complex<double>>(ulocal, test, -wvNbr, wvNbr, 1);

//    if (upsampledPAS.size() > 1){
//        fft.inv(out, upsampledPAS);
//    }

//    ph::fft(upsampledPAS, true);
//    vector<complex<double>> out3 = ph::idft(upsampledPAS);
//    vector<complex<double>> out3 = ph::idft(test);

//    for (const auto &e: out) {
//        out2.push_back((float)e.real());
////        out2.push_back((float)abs(e));
//    }

//    vector<double> omega;
//    for (unsigned i = 0; i < out2.size(); i++) {
//        omega.push_back(i);
//    }

//    map<double, double> spaceCorr = ph::correlation(test);

//    cout << "out2 size: " << out2.size() << endl;
//    unsigned f = 0;
//    for (const auto &e: out2){
//        cout << e <<", "<< upsampledPAS.at(f) << endl;
//        f++;
//    }

//    cout << "u ----------" << endl;
//    for (auto &e: ulocal) {
//        cout << e << endl;
//    }

//    int i = 0;
//    for (auto e: out2) {
//        m_chsData[rx].spaceCrltnMap[i] = e;
//        i++;
//    }
//    m_chsData[rx].spaceCrltn = out2;
//    m_chsData[rx].deltaZ = omega;
    return &m_chsData[rx];
}

//void Tx::angularSpread(QPointF *rx)
//{
//    double prx = 0;
//    double variance = 0;
//    double mean = 0;

//    const vector<double> &prxAngularSpread = m_chsData.at(rx).prxAngularSpctr;
//    const vector<double> &u = m_chsData.at(rx).u;

//    for (unsigned i = 0; i < prxAngularSpread.size(); i++) {
//        prx += prxAngularSpread.at(i);
//        variance += pow(u.at(i), 2) * prxAngularSpread.at(i);
//        mean += u.at(i) * prxAngularSpread.at(i);
//    }

//    m_chsData.at(rx).angularSpred = sqrt(variance/prx - pow(mean, 2));
//}

void Tx::compute(QPointF *receiver)
{
    if (!m_beamsFrozen && !m_chosenBeams[receiver]) {

//        chooseBeam(receiver);
        comput4FixedBeam(receiver);

    } else {

        comput4FixedBeam(receiver);
    }

    double totalPower = computePrx(receiver);

    double powerDBm = dBm(totalPower);

    m_chsData[receiver].fq = m_frequency;
    m_chsData[receiver].bw = m_bandwidth;
    m_chsData[receiver].prx = powerDBm;
    m_chsData[receiver].eField = m_receiversField[receiver]+m_receiversGroundField[receiver];

    // m_algorithm->sendData(this, dynamic_cast<MathematicalProduct *>(receiver));
//    receiver->answer(this, m_frequency, m_bandwidth, powerDBm, m_receiversField[receiver]);
}


double Tx::computePathLossPower(QPointF* copy_receiver)
{
    double powerAtReceiver = 0;
    complex<double> emField = 0;
    complex<double> groundField = 0;

    for (unsigned i = 0; i < m_receiversRays[copy_receiver].size(); i++)
    {
        WholeRay *wholeRay = m_receiversRays[copy_receiver].at(i);

        if (wholeRay->at(0)->getDiffracted())
        {
            map<QPointF *, map<double, double>>::iterator it;
            complex<double>EMfield = computeDiffractedEfield(copy_receiver,wholeRay,false);
            emField += EMfield;
        }
        else
        {
//            complex<double> EMfield = computeEMfield(wholeRay, copy_receiver,false);
            tuple<int, int> arrSize = {m_column, m_row};
            complex<double> EMfield = ph::computeEMfield(wholeRay, arrSize, m_power, wvNbr,
                                                         m_orientation, m_pr_orientation,
                                                         static_cast<ph::TxType>(m_kind));
            if (wholeRay->size() == 1) {
                // Adding the ground component
                double angle_transmitter = wholeRay->back()->angle();
                groundField = computeEfieldGround(copy_receiver,angle_transmitter,false); // Compute the electrical field from the ray reflected off the ground
            }
            emField += EMfield;
        }
    }
    double totalPower = computePrx(emField,groundField,copy_receiver);

    powerAtReceiver = dBm(totalPower);

    return powerAtReceiver;
}

complex<double> Tx::computeEField(QPointF *rx)
{
    complex<double> emField = 0;
    complex<double> groundField = 0;

    for (unsigned i = 0; i < m_receiversRays[rx].size(); i++)
    {
        WholeRay *wholeRay = m_receiversRays[rx].at(i);

        if (wholeRay->at(0)->getDiffracted())
        {
            map<QPointF *, map<double, double>>::iterator it;
            complex<double>EMfield = computeDiffractedEfield(rx, wholeRay, false);
            emField += EMfield;
        }
        else
        {
//            complex<double> EMfield = computeEMfield(wholeRay, copy_receiver,false);
            tuple<int, int> arrSize = {m_column, m_row};
            complex<double> EMfield = ph::computeEMfield(wholeRay, arrSize, m_power, wvNbr,
                                                         m_orientation, m_pr_orientation,
                                                         static_cast<ph::TxType>(m_kind));
            if (wholeRay->size() == 1) {
                // Adding the ground component
                double angle_transmitter = wholeRay->back()->angle();
                groundField = computeEfieldGround(rx ,angle_transmitter, false); // Compute the electrical field from the ray reflected off the ground
                emField += groundField;
            }
            emField += EMfield;
        }
    }

    return emField;
}

Tx::EFields Tx::computeEFields(QPointF *rx)
{
    complex<double> emField = 0;
    complex<double> groundField = 0;

    for (unsigned i = 0; i < m_receiversRays[rx].size(); i++)
    {
        WholeRay *wholeRay = m_receiversRays[rx].at(i);

        if (wholeRay->at(0)->getDiffracted())
        {
            map<QPointF *, map<double, double>>::iterator it;
            complex<double>EMfield = computeDiffractedEfield(rx, wholeRay, false);
            emField += EMfield;
        }
        else
        {
            //            complex<double> EMfield = computeEMfield(wholeRay, copy_receiver,false);
            tuple<int, int> arrSize = {m_column, m_row};
            complex<double> EMfield = ph::computeEMfield(wholeRay, arrSize, m_power, wvNbr,
                                                         m_orientation, m_pr_orientation,
                                                         static_cast<ph::TxType>(m_kind));
            if (wholeRay->size() == 1) {
                // Adding the ground component
                double angle_transmitter = wholeRay->back()->angle();
                groundField = computeEfieldGround(rx ,angle_transmitter, false); // Compute the electrical field from the ray reflected off the ground
//                emField += groundField;
            }
            emField += EMfield;
        }
    }

    return {emField, groundField};
}

double Tx::getRxSumAbsE(QPointF *rx)
{
    return m_rxsSumAbsE[rx];
}

//complex<double> Tx::computeInterference(QPointF* copy_receiver,QLineF local_region)
//{
//    complex<double> impulse_r = 0;
//    vector<WholeRay *> wholeRays = m_receiversRays[copy_receiver];

//    for (unsigned j = 0; j < wholeRays.size(); j++)
//    {
//        WholeRay *wholeRay  = wholeRays.at(j);

//        if (wholeRay->at(0)->getDiffracted())
//        {
//            impulse_r += computeImpulseDiffraction(wholeRay, local_region);
//        }
//        else
//        {
//            int amountSegment = wholeRay->size();
//            if (amountSegment == 1)
//            {
//                double angle_transmitter = wholeRay->back()->angle();
//                impulse_r += computeImpulseGroundReflection(copy_receiver, angle_transmitter, local_region);
//            }
//            impulse_r += computeImpulseReflection(wholeRay,local_region);
//        }
//    }
//    return impulse_r;
//}

// ---------------------------------------------------- ModelObserver -------------------------------------------------------------------


void Tx::attachObservable(ModelObservable *modelObservable)
{
    // ????????????
    m_model = modelObservable;
}


// ---------------------------------------------------- AbstractAntenna ---------------------------


void Tx::notifyParent(QPointF *receiver, double speed, const QPointF &point, WholeRay *wholeRay)
{
    //
    //      Called by the transmitter images and the diffraction points.
    //

//    unique_ptr<Ray> newRay(m_rayFactory->createRay(*this, point));
//    wholeRay->push_back(move(newRay));
    wholeRay->push_back(m_rayFactory->createRay(*this, point));
    m_receiversRays[receiver].push_back(wholeRay);
    rays_speed[wholeRay] = speed/3.6;
}


void Tx::notifyCarDetected()
{
    m_txImgs.clear();
    emit detectsCar(this);
}


QPointF Tx::getPosition() const
{
    return *this;
}


QPolygonF Tx::getIlluminationZone(const QRectF &rect) const
{
    return QPolygonF(rect);
}


QPolygonF Tx::getIlluminationZone() const
{
    return m_zone;
}


QPolygonF Tx::getIlluminatedZone() const
{
    return m_zone;
}


void Tx::setIlluminatedZone(const QPolygonF &zone)
{
    m_zone = zone;
}


void Tx::carMoved(Car *car, int /*x*/, int /*y*/, double /*orientation*/)
{
//    cout << "Illuminated cars: " << m_illuminatedCars.size() << endl;
    int idx = 0;
    if (m_zone.intersects(*car)) {
        if (!inIlluminatedCars(car, &idx)) m_illuminatedCars.push_back(car);
        m_txImgs.clear();
        emit detectsCar(this);
    }

    else if (inIlluminatedCars(car, &idx)) {

        m_illuminatedCars.erase(m_illuminatedCars.begin() + idx);
        m_txImgs.clear();
        emit detectsCar(this);
    }
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 1. Path Loss Computation:

void Tx::clearPathLoss()
{
    m_pathloss.clear();
    Prx.clear();
    D.clear();
    logD.clear();
    path_loss.clear();
    friis_loss.clear();
    fading.clear();
    m = 0;
    fading_variability = 0;
    min_prx = 0;
}

void Tx::computePathLossFading()
{
    linearRegressionPathLoss();
    for (unsigned i = 0; i < m_pathloss.size(); i++){
        path_loss.push_back(m * logD[i] + m_pathloss[1]);
        fading.push_back(Prx[i] - path_loss[i]);
        friis_loss.push_back(-20 * logD[i] + m_pathloss[1]);
    }

    fading_variability = standardDeviation();
}

void Tx::linearRegressionPathLoss()
{
    /*
    *   b = output intercept
    *   m  = output slope
    *   r = output correlation coefficient (can be NULL if you don't want it)
    */

    for (auto &path: m_pathloss){
        D.push_back(path.first);
        logD.push_back(log10(path.first));
        Prx.push_back(path.second);
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

double Tx::standardDeviation(){
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

void Tx::notifyObserversPathLoss()
{
    clearPathLoss();
    vector<QPointF> pl_points = pathLossPoints();   // get the path loss (pl) points of the transmitter
    QPointF copy_receiver;   // copy a receiver to compute power
    std::map<double /*distance*/, double /*power sum*/> sum_power;  // sum of power
    std::map<double /*distance*/, int /*counter*/> counter;     // counter to compute average

    for(unsigned i = 0; i <= pl_points.size(); i++)
    {
        if (i == pl_points.size()){
            copy_receiver.setX(this->x()+1.0/px_to_meter);
            copy_receiver.setY(this->y());
        }
        else {
            copy_receiver.setX(pl_points.at(i).x());
            copy_receiver.setY(pl_points.at(i).y());
        }
        clearChData(&copy_receiver);
        if (m_receiversRays.count(&copy_receiver)) {
            for (unsigned int i = 0; i < m_receiversRays[&copy_receiver].size(); i++) {
                delete m_receiversRays[&copy_receiver].at(i);
            }
            m_receiversRays[&copy_receiver].clear();
        }
        detectAndLink(copy_receiver);
        notifyObservers(&copy_receiver, m_movement);

        double power = computePathLossPower(&copy_receiver);
        QLineF line(*this, copy_receiver);
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
//    modelPathLoss();
//    cellRange();
    computeMinPrx();
}

double Tx::inputNoise()
{
    return 10 * log10(k_b * t_0 * m_bandwidth);
}

void Tx::computeMinPrx()
{
    min_prx = m_target_snr + m_noise_figure + inputNoise() + m_interferencemargin + 30; // [dBm]
}


//-----------------------------------------------------------------------------------------------------------
// Shadowing computation

void Tx::clearShadowing()
{

}

map<double,double> Tx::notifyObserversShadowing()
{
//    vector<QPointF> points = circlePoints(*this, 100, 1);
//    QPointF copy_receiver;
//    map <double /*angle*/,double /*power*/> shadow;
//    for(unsigned i = 0; i < points.size(); i++)
//    {
//        copy_receiver.setX(points.at(i).x());
//        copy_receiver.setY(points.at(i).y());

//        clearChData(&copy_receiver);
//        if (m_receiversRays.count(&copy_receiver)) {
//            for (unsigned int i = 0; i < m_receiversRays[&copy_receiver].size(); i++) {
//                delete m_receiversRays[&copy_receiver].at(i);
//            }
//            m_receiversRays[&copy_receiver].clear();
//        }

//        detectAndLink(copy_receiver);
//        notifyObservers(&copy_receiver, m_movement);

//        double power = computePathLossPower(&copy_receiver);
//        QLineF line(*this, copy_receiver);
//        if (!isinf(power) && line.length()*px_to_meter >= 1.0)
//        {
//            shadow[line.angle()*M_PI/180.0] = power;
//        }
//    }
//    return shadow;
    map <double /*distance*/,double /*power_mean*/> shadow;
    vector<double> prx = powerPathLoss();
    vector <double> dpl = distancePathLoss();
    int sample_mean = round(dpl.size()*0.005);
    std::map<double,double>::iterator it;
    double power_mean = 0;
    for (int j = 0; j < prx.size(); j ++){
        if (j >= round(sample_mean/2) && j <= m_pathloss.size()-round(sample_mean/2)){
            for (int i = -round(sample_mean/2) ; i <=round(sample_mean/2) ; i++){
                power_mean += prx[j+i];
            }
            power_mean = power_mean/sample_mean;
            shadow[dpl[j]] = power_mean;
         }
        else {
            shadow[dpl[j]] = prx[j];
        }
    power_mean = 0;
    }
    return shadow;
}

vector<QPointF> Tx::circlePoints(QPointF center, double radius, int rpd)
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

std::map<double,double> Tx::averageOnMap(std::map<double, double> values,
                                          std::map<double, int> counter) const
{
    std::map<double,double> average_map;
    for(const auto &value: values){
        average_map[value.first] = value.second/counter[value.first];
    }
    return average_map;
}
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 3. Cell Range Computation:
void Tx::cellRange()
{
    // minPrx = <Prx> - L_fading
    // <Prx> = mx + b; where x = log10(d)
    // Pr[L_fading<gamma] = 1 - 1/2* erfc(gamma/(fadingVariability * sqrt(2)))

    // Sweep gamma [0; 3*fadingVariability] => Compute probability Pr[L_fading<gamma] for each gamma
    // => Compute R such that minPrx> = <Prx(R)> - gamma
    clearCellRange();
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

void Tx::clearCellRange()
{
    probability.clear();
    cell_range.clear();
}

vector<double> Tx::probabilityConnection()
{
    return probability;
}

vector<double> Tx::cellRangeConnection()
{
    return cell_range;
}
