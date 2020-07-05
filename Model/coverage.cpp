#include "coverage.h"

Coverage::Coverage(SceneFactory *receiverFactory):m_receiverFactory(receiverFactory)
{

}

MathematicalComponent* Coverage::compute(vector<MathematicalTransmitterProduct*> transmitter, MathematicalReceiverProduct* receiver,
                       vector<MathematicalBuildingProduct*> buildings){

}

MathematicalComponent* Coverage::compute(map<string, vector<MathematicalProduct *> > mathematicalComponents){
    setAttributs(mathematicalComponents);
    reflectionsNumber = 5;
    //cout<<"I am computing"<<endl;



    RayFactory* rayFactory = new RayFactory(false, m_scene);
    m_rayFactory = rayFactory;

    for(int i =0;i<m_transmitters.size();i++){
        m_transmitters.at(i)->setRayFactory(rayFactory);
    }





//    MathematicalProduct* receiver = m_receiverFactory->createMathematicalProduct(workingZone.topLeft().x(),workingZone.topLeft().y(),true);
    MathematicalProduct* receiver = m_receiverFactory->createMathematicalProduct(0,0,true);
    m_receivers.push_back(dynamic_cast<MathematicalReceiverProduct*>(receiver));
    m_receiver = dynamic_cast<MathematicalReceiverProduct*>(receiver);

    illuminationZones();

    QRectF workingZone = m_totalIlluminationZone.boundingRect();

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

//    m_scene->addRect(workingZone,QPen(),illumination1);

    for(int i=workingZone.topLeft().y();i<workingZone.bottomLeft().y();i+= workingZone.height()/200){
        dynamic_cast<MathematicalReceiverProduct*>(receiver)->setPosY(i);
        for(int j=workingZone.topLeft().x();j<workingZone.topRight().x();j+= workingZone.width()/200){
//            MathematicalProduct* receiver = m_receiverFactory->createMathematicalProduct(i,j,true);
//            dynamic_cast<MathematicalReceiverProduct*>(receiver)->notifyObservers();
            dynamic_cast<MathematicalReceiverProduct*>(receiver)->setPosX(j);
            MathematicalProduct* newReceiver = m_receiverFactory->createMathematicalProduct(receiver,true);

        }
    }
}

void Coverage::sendData(MathematicalProduct *transmitter, MathematicalProduct *receiver){
    // Send data is used to share some computed data from the transmitter to the receiver.
    MathematicalTransmitterProduct* true_transmitter = static_cast<MathematicalTransmitterProduct*>(transmitter);
    MathematicalReceiverProduct* true_receiver = static_cast<MathematicalReceiverProduct*>(receiver);
}


void Coverage::setAttributs(map<string, vector<MathematicalProduct *> > m_mathematicalComponents){
    if(m_mathematicalComponents.count("Transmitter")){
        for(int i=0;i<m_mathematicalComponents["Transmitter"].size();i++){
            m_transmitters.push_back(static_cast<MathematicalTransmitterProduct*>(m_mathematicalComponents["Transmitter"].at(i)) );
        }

    }
//    if(m_mathematicalComponents.count("Receiver")){
//        for(int i=0;i<m_mathematicalComponents["Receiver"].size();i++){
//            m_receiver = static_cast<MathematicalReceiverProduct*>(m_mathematicalComponents["Receiver"].at(0)) ;
//            m_receivers.push_back(static_cast<MathematicalReceiverProduct*>(m_mathematicalComponents["Receiver"].at(i)));
//    }
//    }
    if(m_mathematicalComponents.count("Building")){
        for(int i=0;i<m_mathematicalComponents["Building"].size();i++){
            m_buildings.push_back(static_cast<MathematicalBuildingProduct*>(m_mathematicalComponents["Building"].at(i)) );
        }
    }
}

vector<QRectF> Coverage::buildCoverageZone(){
    for(int i=0; i<m_transmitters.size();i++){

    }
}
