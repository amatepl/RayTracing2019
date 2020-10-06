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
    reflectionsNumber = 1;

    RayFactory* rayFactory = new RayFactory(false, m_scene,px_to_meter);
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

    for(int i = workingZone.topLeft().y();
         i < workingZone.bottomLeft().y();
         i += workingZone.height() / (200/px_to_meter)){

        dynamic_cast<Rx*>(receiver)->setPosY(i);

        for(int j = workingZone.topLeft().x();
             j < workingZone.topRight().x();
             j += workingZone.width() / (200/px_to_meter)){

            dynamic_cast<Rx*>(receiver)->setPosX(j);
            MathematicalProduct* newReceiver = m_receiverFactory->createMathematicalProduct(receiver,true);
            m_coverageRxs.push_back(newReceiver);

        }
    }
    return nullptr;
}

void Coverage::clearWorkspace()
{

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
