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
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!                                      !!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!! Relative Permittivity is on the wall !!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!                                      !!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    epsilonWallRel      = 5;
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
        coverage << QPointF(x() + m_radius * cos(M_PI * i / 8), y() + m_radius * sin(M_PI * i / 8));
    }
    return coverage;
}

complex<double>
Tx::computeImpulseReflection(WholeRay *ray_line, QLineF local_region)
{
    complex <double> i(0.0, 1.0);
//    int amountSegment = ray_line->size();
//    double completeLength = 0.0;
//    double R = 1;
//    Ray *current_ray;

//    for (int i = 0; i < amountSegment; i++) {
//        current_ray = ray_line->at(i);
//        if (i != amountSegment - 1) {
//            double thetaI = abs(current_ray->getTetai());
//            R *= computeReflexionPer(thetaI * 2 * M_PI / 180, epsilonWallRel);
//        }
//        completeLength += current_ray->getMeterLength();
//    }
    double completeLength = ray_line->totalLength();
    double R = ph::computeR(ray_line);
    double a = R / completeLength;

    // Angle in degrees
    double angle_transmitter = ray_line->back()->angle();
    double angle_receiver = ray_line->front()->angle();
    QLineF beta(QPointF(.0,.0),QPointF(2.0 * M_PI / lambda,.0));
    beta.setAngle(angle_receiver);
    double scalar_beta_r = beta.p2().x()*local_region.p2().x() + beta.p2().y()*local_region.p2().y();
    complex<double> array_factor = ph::totaleArrayFactor(angle_transmitter, 90,
                                                         m_frequency, m_orientation,
                                                         m_pr_orientation, m_column,
                                                         m_row, static_cast<ph::TxType>(m_kind));
    double tau = completeLength/c;

    complex<double> impulse_r = a * array_factor
                                * exp(-i * scalar_beta_r)
                                * exp(-i * 2.0*M_PI * std::complex<double>(m_frequency * tau));
    return impulse_r;
}


void Tx::estimateCh(ProductObservable *rx)
{
    complex <double> i(0.0, 1.0);
    m_los_factor[rx] = 0;
    double pwr = 0;
    double hMax = 0;
    QLineF receiver_speed = receivers_speed[rx];
    QLineF beta(QPointF(.0, .0), QPointF(2.0 * M_PI / lambda, 0.0));

    for (const auto wholeRay: m_receiversRays[rx]) {

        const double completeLength = wholeRay->totalLength();
        const double angleRx = wholeRay->angleRx();
        const double angleTx = wholeRay->angleTx();
        Data &chData = m_chsData.at(rx);
        complex<double> array_factor = ph::totaleArrayFactor(angleTx, 90,
                                                             m_frequency, m_orientation,
                                                             m_pr_orientation, m_column,
                                                             m_row, static_cast<ph::TxType>(m_kind));
        const double R = ph::computeR(wholeRay);
        complex<double> a =  R * array_factor / completeLength;
        complex<double> h = a * exp(-i * (wvNbr) * completeLength);
        pwr += norm(h);
        hMax = abs(h) > hMax ? abs(h): hMax;

        if (wholeRay->size() == 1) m_los_factor[rx] = norm(h);
        m_nlos_factor[rx] += norm(h);

        // Tau
        double tau = completeLength * 1e9/c; // [ns]
        tau = round(tau * 1e4) / 1e4; // [precision of 0.1 ps]

        // Impulse response
        m_receiversImpulse[rx][tau] += h; // To change
        chData.impulseResp[tau] += h;

        beta.setAngle(angleRx);

//=======
//        beta.setAngle(angleRx + 180);
//>>>>>>> 2559737b96b8d5fcf7922120950f26c76a027b78

        double theta = angleRx;
        if (receiver_speed.length() > 0.0){
            theta = beta.angleTo(receiver_speed);
        }

        double u = ph::uMPC(wvNbr, theta);
        double w = receiver_speed.length()*u;

        complex<double> angularDistr = ph::angDistrMPC(h, theta, u);
        complex<double> dopplerDistr = ph::angDistrMPC(h, theta, w);
        double prxAngSpctr = ph::prxSpctrMPC(angularDistr, wvNbr, u);
        double prxDopSpctr = ph::prxSpctrMPC(dopplerDistr, wvNbr * receiver_speed.length(), w);

        chData.prxAngularSpctrMap[u] += ph::prxSpctrMPC(angularDistr, wvNbr, u);

        // Save Data
        chData.u.push_back(u);
        chData.w.push_back(w);
        chData.angularDistr.push_back(angularDistr);
        chData.dopplerDistr.push_back(dopplerDistr);
        chData.prxAngularSpctr.push_back(prxAngSpctr);
        chData.prxDopplerSpctr.push_back(prxDopSpctr);

        //receivers_speed.translate(- m_receiver_speed.p1());
        // m_ray_speed.translate(- m_ray_speed.p1());
        //QLineF resultant_speed(QPointF(0.0, 0.0), m_receiver_speed.p2() - m_ray_speed.p2());
        //double omega = - (beta.p2().x() * resultant_speed.p2().x() + beta.p2().y() * resultant_speed.p2().y());
        double omega = 2.0 * M_PI / lambda * rays_speed[wholeRay];
        omega = round(omega * 1e4) / 1e4;
        //m_dopplerSpectrum[rx][omega] += h;
        chData.dopplerSpctr[omega] += h;
        //chData.dopplerDistr[omega] += h;

    }

//    normalizePrxSpctr(m_chsData.at(rx).prxAngularSpctr);
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

complex <double>
Tx::computeImpulseGroundReflection(ProductObservable *copy_receiver,
                                                               double direction,
                                                               QLineF local_region)
{
    double distance = this->distance(copy_receiver);
    double thetaG = atan((distance / 2) / ant_hght);
    double thetaI = M_PI - thetaG;
    double R = computeReflexionPar(thetaG, epsilonWallRel);
    double completeLength = sqrt(4*pow(ant_hght,2)+pow(distance,2));
    complex <double> i(0.0, 1.0);
    double a = R  / completeLength;
    complex<double> array_factor = ph::totaleArrayFactor(direction,thetaI*180.0/M_PI,
                                                         m_frequency, m_orientation,
                                                         m_pr_orientation, m_column,
                                                         m_row, static_cast<ph::TxType>(m_kind));
    double tau = completeLength/c;
    double local_region_angle = local_region.angle() + 180.0;
    local_region_angle = fmod(local_region_angle, 360.0);
    double angle = (direction - local_region_angle)*M_PI/180.0;
    complex<double> impulse_r = a * array_factor
                                * exp(-i * (2.0 * M_PI / lambda) * local_region.length() * cos(angle) * cos(M_PI/2-thetaG))
                                * exp(-i * 2.0*M_PI * std::complex<double>(m_frequency * tau));
    return impulse_r;
}

complex <double> Tx::computeEfieldGround(const ProductObservable *receiver,
                                                                    const double direction,
                                                                    const bool properties)
{
    // Compute the electrical field, at the receiver, induced by the ray reflected off the ground.
    // TO DO: check if there is a wall between the TX and RX
    double distance = this->distance(receiver); // conversion (1px == 2cm)
    double thetaG = atan((distance / 2) / ant_hght);
    double thetaI = M_PI - thetaG;
    double R = computeReflexionPar(thetaG, epsilonWallRel);
    double completeLength = sqrt(4 * pow(ant_hght, 2) + pow(distance, 2)); //distance / sin(thetaG);

    complex <double> i(0.0, 1.0);

    double Ia = sqrt(2 * m_power / (m_row * m_column * r_a)); // Ia could be changed for Beamforming application
    complex<double> array_factor = ph::totaleArrayFactor(direction, thetaI * 180.0 / M_PI,
                                                         m_frequency, m_orientation,
                                                         m_pr_orientation, m_column,
                                                         m_row, static_cast<ph::TxType>(m_kind));
    complex<double> a = R * array_factor * exp(-i * (2.0 * M_PI / lambda) * completeLength) / completeLength;
    complex <double> Efield = -i * a * (z_0 * Ia) / (2 * M_PI);

    QLineF receiver_speed = receivers_speed[receiver];
    QLineF beta(QPointF(.0, .0), QPointF(2.0 * M_PI / lambda, 0.0));

    if (properties)
    {
        double tau = completeLength * 1e9/c; // [ns]
        tau = round(tau*1e4)/1e4; // [precision of 0.1 ps]
        m_receiversImpulse[receiver][tau] += a;
        m_chsData[receiver].impulseResp[tau] += a;
        m_nlos_factor[receiver] += pow(abs(a),2);
//        double shift = (direction - m_receiver_speed.angle()) * M_PI / 180.0;
//        double omega = -2.0 * M_PI * m_receiver_speed.length() * cos(shift) * cos(M_PI/2-thetaG) / lambda;
//        m_dopplerSpectrum[receiver][omega] += a;
//        m_chsData[receiver].dopplerSpctr[omega] += a;

        double angleRx = 180 + direction;
        Data &chData = m_chsData[receiver];

        beta.setAngle(angleRx + 180);

        double theta = angleRx;
        if (receiver_speed.length() > 0.0){
            theta = beta.angleTo(receiver_speed);
        }
        // Put computed data into channels data.
        double u = ph::uMPC(wvNbr, angleRx);

        complex<double> angularDistr = ph::angDistrMPC(a, angleRx, u);
        double prxAngSpctr = ph::prxSpctrMPC(angularDistr, wvNbr, u);

        // Save Data
        chData.u.push_back(u);
        chData.angularDistr.push_back(angularDistr);
        chData.prxAngularSpctr.push_back(prxAngSpctr);

    }

    return Efield;
}

double Tx::distance(const ProductObservable *receiver)
{

    // ??????
    //  For display, it calcultes the direct Euclidian distance from the receiver
    //  to the emettor, displays the results on the UI
    //

    double x1 = x();
    double y1 = y();
    double x2 = receiver->getPos()->x();
    double y2 = receiver->getPos()->y();

    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)) * px_to_meter; // conversion (1px == 1dm)
}

complex<double>
Tx::computeImpulseDiffraction(WholeRay *ray_line, QLineF local_region)
{
    double direct_dist = sqrt(pow(ray_line->at(1)->p1().x() - ray_line->at(0)->p2().x(), 2)
                              + pow(ray_line->at(1)->p1().y() - ray_line->at(0)->p2().y(), 2)); //convertir px to cm?
    complex<double> F = 0.0;
    complex <double> i(0.0, 1.0);

    // The length defference between the path going through the tip of the obstacle, and the direct path.
    double delta_r = (ray_line->at(0)->length() + ray_line->at(1)->length() - direct_dist) * px_to_meter;
    double nu = sqrt(2 * 2 * M_PI / lambda * delta_r / M_PI);

    // The ITU's approximation for |F(nu)|^2
    double absF = pow(10, -6.9 / 40) / sqrt((sqrt(pow(nu - 0.1, 2) + 1) + nu - 0.1));
    double argF = -M_PI / 4 - pow(nu, 2) * M_PI / 2;
    F = absF * exp(i * argF);

    Line directRay(ray_line->at(0)->p2(), ray_line->at(1)->p1());
    directRay.setScale(px_to_meter);
    double angle = ray_line->at(1)->angle();
    QLineF beta(QPointF(.0,.0),QPointF(2.0 * M_PI / lambda,.0));
    beta.setAngle(ray_line->at(0)->angle());
    double scalar_beta_r = beta.p2().x()*local_region.p2().x() + beta.p2().y()*local_region.p2().y();
    double tau = (ray_line->at(0)->getMeterLength()+ray_line->at(1)->getMeterLength())/c;
    complex<double> array_factor = ph::totaleArrayFactor(angle,90,
                                                     m_frequency, m_orientation,
                                                     m_pr_orientation, m_column,
                                                     m_row, static_cast<ph::TxType>(m_kind));

    complex<double> impulse_r = array_factor*F
                                *exp(-i * scalar_beta_r)
                                *exp(-i * 2.0*M_PI * std::complex<double>(m_frequency * tau))
                                /directRay.getMeterLength();
    return impulse_r;
}

complex<double> Tx::computeDiffractedEfield(ProductObservable *receiver,
                                                                        WholeRay *rayLine,
                                                                        bool properties)
{

    // Direct distance between the receiver and the transmitter
//    double direct_dist = sqrt(pow(transmitter->getPosition().x()-m_Receiver->getPosX(),2)
//                              + pow(transmitter->getPosition().y()-m_Receiver->getPosY(),2)); //convertir px to cm?

    double direct_dist = rayLine->directDistance(); //convertir px to cm?

    complex<double> Efield = 0.0;
    complex<double> F = 0.0;
    complex <double> i(0.0, 1.0);

    // The length defference between the path going through the tip of the obstacle, and the direct path.

    double delta_r = (rayLine->at(0)->length() + rayLine->at(1)->length() - direct_dist) * px_to_meter;

    double nu = sqrt(2 * 2 * M_PI / lambda * delta_r / M_PI);
    // The ITU's approximation for |F(nu)|^2

    double absF = pow(10, -6.9 / 40) / sqrt((sqrt(pow(nu - 0.1, 2) + 1) + nu - 0.1));
    double argF = -M_PI / 4 - pow(nu, 2) * M_PI / 2;
    F = absF * exp(i * argF);

    Line directRay(rayLine->at(0)->p2(), rayLine->at(1)->p1());
    double angle = rayLine->at(1)->angle();
    complex<double> array_factor = ph::totaleArrayFactor(angle,90,
                                                     m_frequency, m_orientation,
                                                     m_pr_orientation, m_column,
                                                     m_row, static_cast<ph::TxType>(m_kind));
    directRay.setScale(px_to_meter);
    complex<double> a = F * array_factor * (exp(-i * (2.0 * M_PI / lambda) * directRay.getMeterLength())
                        / directRay.getMeterLength());
    double Ia = sqrt(2 * m_power / (m_row*m_column * r_a)); // Ia could be changed for Beamforming application (add exp)
    Efield = -i  * a * ((z_0 * Ia) / (2 * M_PI));
    if (properties){
        double completeLength = rayLine->at(1)->getMeterLength() + rayLine->at(0)->getMeterLength();
        double tau = completeLength * 1e9/c; // [ns]
        tau = round(tau*1e4)/1e4; // [precision of 0.1 ps]
        m_receiversImpulse[receiver][tau] = a;
        m_chsData[receiver].impulseResp[tau] = a;

    }
    return Efield;
}


void Tx::chooseBeam(ProductObservable *receiver)
{

    double powerAtReceiver = 0;
    complex<double> emField = 0;
    complex<double> groundField = 0;
    char chosenBeam = -5;

    vector<WholeRay *> wholeRays = m_receiversRays[receiver];

    for (int i = -5; i < 5; i++) {
//        m_pr_orientation = i;
        emField = 0;

        for (unsigned j = 0; j < wholeRays.size(); j++) {
            WholeRay *wholeRay  = wholeRays.at(j);

            if (wholeRay->at(0)->getDiffracted()) {     // The ray is a diffracted one.

                emField += computeDiffractedEfield(receiver,wholeRay,false);

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
            }
        }

        if (computePrx(emField,groundField,receiver) > powerAtReceiver) {

            powerAtReceiver = computePrx(emField,groundField,receiver);
            chosenBeam = i;
            m_receiversField[receiver] = emField;
            m_receiversGroundField[receiver] = groundField;

        }
    }

    m_pr_orientation = chosenBeam;
    m_chosenBeams[receiver] = true;
}


void
Tx::comput4FixedBeam(ProductObservable *receiver)
{
    bool diffracted = false;
    m_receiversField[receiver] = 0;
    m_receiversGroundField[receiver] = 0;
    for (unsigned i = 0; i < m_receiversRays[receiver].size(); i++)
    {
        WholeRay *wholeRay = m_receiversRays[receiver].at(i);

        if (wholeRay->at(0)->getDiffracted())
        {
            map<ProductObservable *, map<double, double>>::iterator it;
            //m_ray_speed = ray_speeds[wholeRay];
            complex<double>EMfield = computeDiffractedEfield(receiver,wholeRay,true);
            m_receiversField[receiver] += EMfield;

            diffracted = true;

        } else {
            //m_ray_speed = ray_speeds[wholeRay];
            //m_ray_speed.setLength(m_ray_speed.length()/3.6);

            tuple<int, int> arrSize = {m_column, m_row};
//            double wvNbr = 2.0 * M_PI / lambda;
//            complex<double> EMfield = computeEMfield(wholeRay, receiver,true);
            complex<double> EMfield = ph::computeEMfield(wholeRay, arrSize, m_power, wvNbr,
                                                     m_orientation, m_pr_orientation,
                                                         static_cast<ph::TxType>(m_kind));

            if (wholeRay->size() == 1) {
                // Adding the ground component
                double angle_transmitter = wholeRay->back()->angle();
                m_receiversGroundField[receiver] = computeEfieldGround(receiver, angle_transmitter, true); // Compute the electrical field from the ray reflected off the ground
            }
            m_receiversField[receiver] += EMfield;

        }
    }

    estimateCh(receiver);
}

void Tx::dontChoseBeam(ProductObservable *receiver)
{
    m_chosenBeams[receiver] = true;
}


void Tx::freazeBeams()
{
    m_beamsFrozen = true;
}


double Tx::computePrx(complex <double> totalEfield, complex<double> groundField, ProductObservable* receiver)
{
    // Compute the power at the receive antenna with the total electric field induced by all MPC
    double distance = this->distance(receiver);
    double thetaI = atan(ant_hght/(distance/2))+M_PI/2;
    complex <double> Voc = (lambda/M_PI)*(totalEfield + groundField*(cos(M_PI/2*cos(thetaI))/sin(thetaI)));
    double Prx = 1.0 / (8.0 * r_a) * norm(Voc);
    return Prx;
}


double Tx::dBm(double power)
{
    return 10 * (log10(power)) + 30.0;
}


double Tx::computeReflexionPer(double thetaI, double epsilonR) const
{
//    double R = (cos(thetaI) - sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)))
//               /(cos(thetaI) + sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)));

    //  Now in the code thatai is the angle between the ray and the wall and not between
    //  the ray and the normal to the wall.
    //  Basicly thetai = pi/2 - thetai.
    //  Because of that cos and sin are inverted and we take their absolute value because of the angles given by Qt.

    double R = (abs(sin(thetaI)) - sqrt(epsilonR) * sqrt(1 - (1 / epsilonR) * pow(cos(thetaI), 2))) /
               (abs(sin(thetaI)) + sqrt(epsilonR) * sqrt(1 - (1 / epsilonR) * pow(cos(thetaI), 2)));
    return R;
}


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
    for (unsigned int i = 0; i < m_productObservable.size(); i++) {
        m_productObservable.at(i)->notify();
    }
}


void Tx::clearAll(){
    //map<ProductObservable *,vector<vector<Ray *>*>>::iterator rays;
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
        whole_rays.clear();
    }
    m_receiversRays.clear();
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
    int num_points = 250;//px_to_meter;
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
                                // tmp_point is inside the coverage zone
                pl_points.push_back(tmp_point);
                                // add tmp_point inside the pl_points
            }
        }
    }
    return pl_points;
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


void Tx::openDialog()
{
    new DialogTx(this);
}

void Tx::setScale(float scale)
{
    MathematicalProduct::setScale(scale);
    m_radius = m_radius/px_to_meter;
    m_zone  = buildCoverage();
}

void Tx::clearChData(ProductObservable *rx)
{
    m_chsData[rx].fq = 0;
    m_chsData[rx].bw = 0;
    m_chsData[rx].prx = 0;
    m_chsData[rx].eField = 0;
    m_chsData[rx].impulseResp.clear();
    m_chsData[rx].dopplerSpctr.clear();
    m_chsData[rx].pathLossP = 0;
    m_chsData[rx].interference = 0;
    m_chsData[rx].angularSpred = 0;
    m_chsData[rx].dopplerSpread = 0;
    m_chsData[rx].u.clear();
    m_chsData[rx].angularDistr.clear();
    m_chsData[rx].prxAngularSpctr.clear();
    m_chsData[rx].prxAngularSpctrMap.clear();
    m_chsData[rx].w.clear();
    m_chsData[rx].dopplerDistr.clear();
    m_chsData[rx].prxDopplerSpctr.clear();
    m_chsData[rx].riceFactor = 0;

}

// ---------------------------------------------------- ProductObserver -------------------------------------------------------------------


Data *Tx::update(ProductObservable *receiver, const QLineF movement)
{
    //      The trasnmitter is updated every time an receiver moves

    // Clear data corresponding to the receiver calling the update
    clearChData(receiver);

    m_receiversField[receiver] = 0;
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


    const QPointF &pos = *receiver->getPos();

    if (m_zone.containsPoint(pos, Qt::OddEvenFill)) {
        //      The receiver is in the illumination zone

        WholeRay *wholeRay = new WholeRay;
//        QPointF m_pos(int(this->x()), int(this->y()));
        wholeRay->push_back(m_rayFactory->createRay(*this, pos));
        m_receiversRays[receiver].push_back(wholeRay);
    }

    notifyObservers(receiver, movement);

    compute(receiver);

    return getChData(receiver);
}

void Tx::notifyObservers(ProductObservable *rx, const QLineF mvmnt)
{
    for (auto &txImg: m_txImgs) {
        txImg->update(rx, mvmnt);
    }
}

void Tx::attachObservable(ProductObservable *productObservable)
{
    m_productObservable.push_back(productObservable);
    m_chosenBeams[productObservable] = false;
}


void Tx::drawRays(ProductObservable *productObservable, bool draw)
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


Data * Tx::getChData(ProductObservable *rx)
{
    // Rice Factor
    m_chsData[rx].riceFactor = 10*log10(m_los_factor[rx]/m_nlos_factor[rx]);

    // Angular Spread
    m_chsData[rx].angularSpred = ph::angularSpread(m_chsData[rx].prxAngularSpctr, m_chsData[rx].u, wvNbr);

    // Doppler Spread
    double speed = receivers_speed[rx].length();
    m_chsData[rx].dopplerSpread = ph::angularSpread(m_chsData[rx].prxDopplerSpctr, m_chsData[rx].w, speed * wvNbr);

    // FFT
    vector<double> pas2 = m_chsData[rx].prxAngularSpctr;
    vector<double> u2 = m_chsData[rx].u;
    Eigen::FFT<double> fft;
    vector<complex<double>> pas =  vector<complex<double>>(pas2.begin(), pas2.end());
    vector<complex<double>> pas3 =  vector<complex<double>>(m_chsData[rx].prxAngularSpctr.begin(), m_chsData[rx].prxAngularSpctr.end());
    vector<complex<double>> out;

    vector <complex <double>> test;

    vector <double> out2;

    for (auto &key: m_chsData[rx].prxAngularSpctrMap) {
        test.push_back(key.second);
    }

    if (test.size() > 1){
        fft.inv(out2, test);
    }

    for (auto & val: out2){
        val = (float)(val);
    }

    vector<double> omega;
    for (unsigned i = 0; i <= u2.size(); i++) {
        omega.push_back(i);
    }

//    map<double, double> spaceCorr = ph::correlation(test);

    m_chsData[rx].prxDopplerSpctr = out2;
//    m_chsData[rx].w = vector <double>(u2.begin(), u2.end() -1 );
    m_chsData[rx].w = omega;
    return &m_chsData[rx];
}

void Tx::angularSpread(ProductObservable *rx)
{
    double prx = 0;
    double variance = 0;
    double mean = 0;

    const vector<double> &prxAngularSpread = m_chsData.at(rx).prxAngularSpctr;
    const vector<double> &u = m_chsData.at(rx).u;

    for (unsigned i = 0; i < prxAngularSpread.size(); i++) {
        prx += prxAngularSpread.at(i);
        variance += pow(u.at(i), 2) * prxAngularSpread.at(i);
        mean += u.at(i) * prxAngularSpread.at(i);
    }

    m_chsData.at(rx).angularSpred = sqrt(variance/prx - pow(mean, 2));
}

void Tx::compute(ProductObservable *receiver)
{
    if (!m_beamsFrozen && !m_chosenBeams[receiver]) {

        chooseBeam(receiver);
        comput4FixedBeam(receiver);

    } else {

        comput4FixedBeam(receiver);
    }

    double totalPower = computePrx(m_receiversField[receiver],m_receiversGroundField[receiver],receiver);

    double powerDBm = dBm(totalPower);

    m_chsData[receiver].fq = m_frequency;
    m_chsData[receiver].bw = m_bandwidth;
    m_chsData[receiver].prx = powerDBm;
    m_chsData[receiver].eField = m_receiversField[receiver];

    // m_algorithm->sendData(this, dynamic_cast<MathematicalProduct *>(receiver));
//    receiver->answer(this, m_frequency, m_bandwidth, powerDBm, m_receiversField[receiver]);
}


double
Tx::computePathLossPower(ProductObservable* copy_receiver)
{
    double powerAtReceiver = 0;
    complex<double> emField = 0;
    complex<double> groundField = 0;

    for (unsigned i = 0; i < m_receiversRays[copy_receiver].size(); i++)
    {
        WholeRay *wholeRay = m_receiversRays[copy_receiver].at(i);

        if (wholeRay->at(0)->getDiffracted())
        {
            map<ProductObservable *, map<double, double>>::iterator it;
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

complex<double> Tx::computeInterference(ProductObservable* copy_receiver,QLineF local_region)
{
    complex<double> impulse_r = 0;
    vector<WholeRay *> wholeRays = m_receiversRays[copy_receiver];

    for (unsigned j = 0; j < wholeRays.size(); j++)
    {
        WholeRay *wholeRay  = wholeRays.at(j);

        if (wholeRay->at(0)->getDiffracted())
        {
            impulse_r += computeImpulseDiffraction(wholeRay, local_region);
        }
        else
        {
            int amountSegment = wholeRay->size();
            if (amountSegment == 1)
            {
                double angle_transmitter = wholeRay->back()->angle();
                impulse_r += computeImpulseGroundReflection(copy_receiver, angle_transmitter, local_region);
            }
            impulse_r += computeImpulseReflection(wholeRay,local_region);
        }
    }
    return impulse_r;
}

// ---------------------------------------------------- ModelObserver -------------------------------------------------------------------


void Tx::attachObservable(ModelObservable *modelObservable)
{
    // ????????????
    m_model = modelObservable;
}


// ---------------------------------------------------- AbstractAntenna ---------------------------


void Tx::notifyParent(ProductObservable *receiver,
                                                  double speed,
                                                  const QPointF &point,
                                                  WholeRay *wholeRay)
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


void Tx::carMoved(MathematicalCarProduct *car, int /*x*/, int /*y*/, double /*orientation*/)
{
    int idx = 0;
    if (m_zone.intersects(*car)) {

        m_illuminatedCars.push_back(car);
        emit detectsCar(this);
    }

    else if (inIlluminatedCars(car, &idx)) {

        m_illuminatedCars.erase(m_illuminatedCars.begin() + idx);
        emit detectsCar(this);
    }
}

