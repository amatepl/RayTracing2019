#include "coverage.h"

Coverage::Coverage(SceneFactory *receiverFactory):m_receiverFactory(receiverFactory)
{
}

//MathematicalComponent* Coverage::compute(vector<MathematicalTransmitterProduct*> transmitter, MathematicalReceiverProduct* receiver,
//                       vector<MathematicalBuildingProduct*> buildings){

//}

MathematicalComponent* Coverage::compute(map<string, vector<MathematicalProduct *>> mathematicalComponents,
                                         ReceiverFactory* receiverfactory)
{
    setAttributs(mathematicalComponents);
    reflectionsNumber = 5;

    RayFactory* rayFactory = new RayFactory(false, m_scene);
    m_rayFactory = rayFactory;

    for(unsigned int i =0;i<m_transmitters.size();i++){
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

        m_receivers.push_back(dynamic_cast<MathematicalReceiverProduct*>(receiver));

        illuminationZones();

    }


//    MathematicalProduct* receiver = m_receiverFactory->createMathematicalProduct(0,0,true);
//    m_receivers.push_back(dynamic_cast<MathematicalReceiverProduct*>(receiver));

//    m_receiver = dynamic_cast<MathematicalReceiverProduct*>(receiver);

//    illuminationZones();




    QRectF workingZone = m_totalIlluminationZone.boundingRect();

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

//    m_scene->addRect(workingZone,QPen(),illumination1);

    for(int i = workingZone.topLeft().y();
         i < workingZone.bottomLeft().y();
         i += workingZone.height() / 200){

        dynamic_cast<MathematicalReceiverProduct*>(receiver)->setPosY(i);

        for(int j = workingZone.topLeft().x();
             j < workingZone.topRight().x();
             j += workingZone.width() / 200){

            dynamic_cast<MathematicalReceiverProduct*>(receiver)->setPosX(j);
            MathematicalProduct* newReceiver = m_receiverFactory->createMathematicalProduct(receiver,true);

        }
    }
    return nullptr;
}





void Coverage::sendData(MathematicalProduct *transmitter, MathematicalProduct *receiver)
{
    // Send data is used to share some computed data from the transmitter to the receiver.
    MathematicalTransmitterProduct* true_transmitter = static_cast<MathematicalTransmitterProduct*>(transmitter);
    MathematicalReceiverProduct* true_receiver = static_cast<MathematicalReceiverProduct*>(receiver);
}


void Coverage::pathLossComputation(std::vector<QPointF> points,
                                   ProductObservable *true_receiver,
                                   ProductObserver* true_transmitter)
{
    MathematicalTransmitterProduct* original_transmitter = (MathematicalTransmitterProduct*) true_transmitter;
    original_transmitter->activePathLoss(false);
    original_transmitter->computePathLoss(false);
}


void Coverage::setAttributs(map<string, vector<MathematicalProduct *> > m_mathematicalComponents)
{
    if(m_mathematicalComponents.count("Transmitter")){
        for(unsigned int i=0;i<m_mathematicalComponents["Transmitter"].size();i++){
            m_transmitters.push_back(static_cast<MathematicalTransmitterProduct*>
                                     (m_mathematicalComponents["Transmitter"].at(i)) );
            m_transmitters.at(i)->setMediator(this);
        }

    }
    if(m_mathematicalComponents.count("Receiver")){
        for(unsigned i = 0; i < m_mathematicalComponents["Receiver"].size(); i++){
//            m_receiver = static_cast<MathematicalReceiverProduct*>(m_mathematicalComponents["Receiver"].at(0)) ;
            m_receivers.push_back(static_cast<MathematicalReceiverProduct*>(m_mathematicalComponents["Receiver"].at(i)));
    }
    }
    if(m_mathematicalComponents.count("Building")){
        for(unsigned int i=0;i<m_mathematicalComponents["Building"].size();i++){
            m_buildings.push_back(static_cast<MathematicalBuildingProduct*>
                                  (m_mathematicalComponents["Building"].at(i)));
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


vector<QRectF> Coverage::buildCoverageZone()
{
    for(unsigned int i=0; i<m_transmitters.size();i++){

    }
    vector<QRectF> res;
    return res;
}
