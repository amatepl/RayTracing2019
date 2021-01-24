#include "coverage.h"

Coverage::Coverage(SceneFactory *receiverFactory,const float scale):m_receiverFactory(receiverFactory)
{
    px_to_meter = scale;
}

//MathematicalComponent* Coverage::compute(vector<Tx*> transmitter, Rx* receiver,
//                       vector<Building*> buildings){

//}

MathematicalComponent* Coverage::compute(map<string, vector<MathematicalProduct *>> mathematicalComponents,
                                         ReceiverFactory* /*receiverfactory*/)
{
    setAttributs(mathematicalComponents);
//    reflectionsNumber = 10;

    RayFactory* rayFactory = new RayFactory(false, m_scene,px_to_meter);
    m_rayFactory = rayFactory;

    for(unsigned int i = 0; i < m_transmitters.size(); i++){
        m_transmitters.at(i)->setRayFactory(rayFactory);
    }

    MathematicalProduct* receiver;

    if (m_receivers.size()){
        illuminationZones();
        for (unsigned i = 0; i < m_receivers.size(); i++) {
            m_receivers.at(i)->notifyObservers();
        }

        for (unsigned i = 0; i < m_transmitters.size(); i++) {
            m_transmitters.at(i)->freazeBeams();
        }

        receiver = m_receivers.at(0);

    } else {

        receiver = m_receiverFactory->createMathematicalProduct(0,0,true);

        m_receivers.push_back(dynamic_cast<Rx*>(receiver));

        illuminationZones();

    }

//    MathematicalProduct* receiver = m_receiverFactory->createMathematicalProduct(0,0,true);
//    m_receivers.push_back(dynamic_cast<Rx*>(receiver));

//    m_receiver = dynamic_cast<Rx*>(receiver);

//    illuminationZones();

    QRectF workingZone = m_totalIlluminationZone.boundingRect();

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

//    m_scene->addRect(workingZone,QPen(),illumination1);

    emit(computed(buildCoverageZone(workingZone.toRect()), m_mode));

//    for(int i = workingZone.topLeft().y();
//         i < workingZone.bottomLeft().y();
//         i += workingZone.height() / (200/px_to_meter)){

//        dynamic_cast<Rx*>(receiver)->setPosY(i);

//             j < workingZone.topRight().x();
//             j += workingZone.width() / (200/px_to_meter)){

//            dynamic_cast<Rx*>(receiver)->setPosX(j);
//            MathematicalProduct* newReceiver = m_receiverFactory->createMathematicalProduct(receiver,true);
//            m_coverageRxs.push_back(newReceiver);

//        }
//    }
    return nullptr;
}

void Coverage::clearWorkspace()
{

}

void Coverage::clear()
{
    ImagesMethod::clear();
    m_heatMap.clear();
}

void Coverage::setAttributs(map<string, vector<MathematicalProduct *> > m_mathematicalComponents){

    if(m_mathematicalComponents.count("Transmitter")){
        for(unsigned int i=0;i<m_mathematicalComponents["Transmitter"].size();i++){
            m_transmitters.push_back(static_cast<Tx*>
                                     (m_mathematicalComponents["Transmitter"].at(i)) );
            m_transmitters.at(i)->setMediator(this);
        }

    }
    if(m_mathematicalComponents.count("Receiver")){
        for(unsigned i = 0; i < m_mathematicalComponents["Receiver"].size(); i++){
//            m_receiver = static_cast<Rx*>(m_mathematicalComponents["Receiver"].at(0)) ;
            m_receivers.push_back(static_cast<Rx*>(m_mathematicalComponents["Receiver"].at(i)));
    }
    }
    if(m_mathematicalComponents.count("Building")){
        for(unsigned int i=0;i<m_mathematicalComponents["Building"].size();i++){
            m_buildings.push_back(static_cast<Building*>
                                  (m_mathematicalComponents["Building"].at(i)));
        }
    }

    if(m_mathematicalComponents.count("Car")) {
        for(unsigned i = 0; i<m_mathematicalComponents["Car"].size(); i++) {
            m_cars.push_back(static_cast<Car *>
                             (m_mathematicalComponents["Car"].at(i)) );

            m_buildings.push_back(static_cast<Building *>
                                  (m_mathematicalComponents["Car"].at(i)) );
        }
    }
}


void Coverage::choseBeams()
{
    for (unsigned i = 0; i < m_receivers.size(); i++) {
        for (unsigned j = 0; j < m_transmitters.size(); j++) {
            m_transmitters.at(j)->chooseBeam(m_receivers.at(i));
            m_transmitters.at(j)->freazeBeams();
        }
    }
}


HeatMap *Coverage::buildCoverageZone(const QRect &workingZone)
{
    QPointF rx;
//    unsigned h = workingZone.height();
//    unsigned w = workingZone.width();
    int maxY = workingZone.bottomLeft().y();
    int maxX = workingZone.topRight().x();

    fptr f = selectFct();

    notifptr nptr = selectNotifier();

    for(int i = workingZone.topLeft().y(); i < maxY; i += (int) (1 / m_dnsty)){
        rx.setY(i);

        for(int j = workingZone.topLeft().x(); j < maxX; j += (int) (1 / m_dnsty)){

                rx.setX(j);

                (this->*nptr)(&rx, f);
//                notifyTxs(&rx, f);
        }
    }
    return &m_heatMap;
}

void Coverage::notifyTxs(QPointF *rx, fptr f)
{
    complex<double> eField(0,0);
    for (auto &tx: m_transmitters){
        tx->deleteRays(rx);
        tx->detectAndLink(*rx);
        tx->notifyObservers(rx, tx->movement());
        eField += (this->*f)(tx, rx);
//        eField += tx->computeEField(rx);

    }
    m_heatMap.push_back(Tile{rx->toPoint(), eField, (int) (1 / m_dnsty)});
}

void Coverage::notifyTxsRms(QPointF *rx, fptr f)
{
    complex<double> eField(0,0);
    for (auto &tx: m_transmitters){
        tx->deleteRays(rx);
        tx->detectAndLink(*rx);
        tx->notifyObservers(rx, tx->movement());
//        eField += (this->*f)(tx, rx);
        eField += normE(tx,rx);

    }
    eField = sqrt(eField);
    m_heatMap.push_back(Tile{rx->toPoint(), eField, (int) (1 / m_dnsty)});
}

void Coverage::notifyTxsPrx(QPointF *rx, fptr)
{
    double mindBm = -130;
    double prx = pow(10, (mindBm - 30)/10);
    for (auto &tx: m_transmitters){
        tx->deleteRays(rx);
        tx->detectAndLink(*rx);
        tx->notifyObservers(rx, tx->movement());
        double txPrx = tx->getRxPrx(rx);
//        txPrx = tx->dBm(txPrx);
        if (prx < txPrx) {
            prx = txPrx;
        }
    }
    m_heatMap.push_back(Tile{rx->toPoint(), prx, (int) (1 / m_dnsty)});
}

void Coverage::setDnsty(const double dnsty)
{
    m_dnsty = dnsty;
}

complex<double> Coverage::complexE(Tx *tx, QPointF *rx)
{
    return tx->computeEField(rx);
}

complex<double> Coverage::normE(Tx *tx, QPointF *rx)
{

//    return (complex<double>) abs(tx->computeEField(rx));
    return (complex<double>) norm(tx->computeEField(rx));
}

complex<double> Coverage::prx(Tx *tx, QPointF *rx)
{
//    double totalPower = computePrx(m_receiversField[receiver],m_receiversGroundField[receiver],receiver);
    return (complex<double>) tx->getRxPrx(rx);
}

void Coverage::setHeatmapMode(int mode)
{
    m_mode = static_cast<HeatmapMode>(mode);
}

Coverage::fptr Coverage::selectFct()
{
    switch (m_mode) {
    case HeatmapMode::complexE:
        return &Coverage::complexE;
    case HeatmapMode::sumAbsE:
        return &Coverage::normE;
    case HeatmapMode::prx:
        return &Coverage::prx;
    default:
        break;
    }
}

Coverage::notifptr Coverage::selectNotifier()
{
    switch (m_mode) {
    case HeatmapMode::complexE:
        return &Coverage::notifyTxs;
    case HeatmapMode::sumAbsE:
        return &Coverage::notifyTxsRms;
    case HeatmapMode::prx:
        return &Coverage::notifyTxsPrx;
    default:
        break;
    }
}

void Coverage::setScale(const double &px_to_m)
{
    px_to_meter = px_to_m;
}

HeatmapMode Coverage::mode() const
{
    return m_mode;
}
//-------SIGNALS-----------------------------------------------------------------------------------

