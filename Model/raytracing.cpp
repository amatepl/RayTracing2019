#include "raytracing.h"

RayTracing::RayTracing(MathematicalTransmitterProduct *transmitter, MathematicalReceiverProduct *receiver)
{
    RayFactory* rayFactory = new RayFactory(true);
    m_rayFactory = rayFactory;
    transmitter->setRayFactory(rayFactory);

}

RayTracing::RayTracing(){

}

MathematicalComponent* RayTracing::compute(vector<MathematicalTransmitterProduct*> transmitters, MathematicalReceiverProduct* receiver,
                                           vector<MathematicalBuildingProduct *> buildings)
{
    m_transmitters = transmitters;
    m_receiver=receiver;
    m_buildings = buildings;
    reflectionsNumber = 0;

    RayFactory* rayFactory = new RayFactory(true);
    m_rayFactory = rayFactory;
    for(int i =0;i<transmitters.size();i++){
        transmitters.at(i)->setRayFactory(rayFactory);
    }

    //createImages();
    illuminationZones();

}

MathematicalComponent* RayTracing::compute(map<string,vector<MathematicalProduct*>> mathematicalComponents)
{

    setAttributs(mathematicalComponents);
    reflectionsNumber = 5;
    //cout<<"I am computing"<<endl;

    RayFactory* rayFactory = new RayFactory(true);
    m_rayFactory = rayFactory;

    for(int i =0;i<m_transmitters.size();i++){
        m_transmitters.at(i)->setRayFactory(rayFactory);
    }

    //createImages();
    illuminationZones();

}

void RayTracing::setAttributs(map<string, vector<MathematicalProduct *> > m_mathematicalComponents){
    if(m_mathematicalComponents.count("Transmitter")){
        //m_transmitters.push_back((MathematicalTransmitterProduct*) m_mathematicalComponents["Transmitter"].at(i));
        for(int i=0;i<m_mathematicalComponents["Transmitter"].size();i++){
            m_transmitters.push_back(static_cast<MathematicalTransmitterProduct*>(m_mathematicalComponents["Transmitter"].at(i)) );
        }

    }
    for(int i=0;i<m_mathematicalComponents.count("Receiver");i++){
        //m_receiver.push_back((MathematicalTransmitterProduct*) m_mathematicalComponents["Transmitter"].at(i));
        //m_receiver = (MathematicalReceiverProduct*) m_mathematicalComponents["Transmitter"].at(0);
        m_receiver = static_cast<MathematicalReceiverProduct*>(m_mathematicalComponents["Receiver"].at(0)) ;
    }
    if(m_mathematicalComponents.count("Building")){
        //m_buildings.push_back((MathematicalBuildingProduct*) m_mathematicalComponents["Building"].at(i));
        for(int i=0;i<m_mathematicalComponents["Building"].size();i++){
            m_buildings.push_back(static_cast<MathematicalBuildingProduct*>(m_mathematicalComponents["Building"].at(i)) );
        }
    }
}
