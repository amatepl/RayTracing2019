#include "raytracing.h"

RayTracing::RayTracing(Tx *transmitter,
                       Rx */*receiver*/, const float scale)
{
    RayFactory *rayFactory = new RayFactory(true, m_scene, scale);
    m_rayFactory = rayFactory;
    transmitter->setRayFactory(rayFactory);
    px_to_meter = scale;
}


RayTracing::RayTracing(const float scale)
{
    px_to_meter = scale;
}


MathematicalComponent* RayTracing::compute(map<string,vector<MathematicalProduct *>>
        mathematicalComponents, ReceiverFactory* receiverfactory)
{
    setAttributs(mathematicalComponents);

    m_receiverfactory = receiverfactory;

//    reflectionsNumber = 0;

    RayFactory* rayFactory = new RayFactory(true, m_scene,px_to_meter);
    m_rayFactory = rayFactory;


//    for(unsigned i =0; i<m_transmitters.size(); i++) {
//        m_transmitters.at(i)->setRayFactory(rayFactory);
//    }

    //createImages();
    illuminationZones();

    for (unsigned i = 0; i< m_transmitters.size(); i++) {
        m_transmitters.at(i)->setRayFactory(rayFactory);
        QPolygonF illuminatedZone = m_transmitters.at(i)->getIlluminatedZone();
        for (unsigned j = 0; j<m_trees.size(); j++) {
            if (illuminatedZone.intersects(*m_trees.at(j))) {
                m_transmitters.at(i)->appendTree(m_trees.at(j));
            }
        }
    }

//    for (unsigned i = 0; i < m_receivers.size(); i++) {
    for (Rx * rx: m_receivers) {
        //((Rx*)m_mathematicalComponents["Receiver"].at(i))->notifyObservers();
        rx->notifyObservers();
//        m_receivers.at(i)->notifyObservers();
    }

    return nullptr;
}

void RayTracing::clearWorkspace()
{
    for (unsigned i = 0; i< m_transmitters.size(); i++) {
        m_transmitters.at(i)->clearAll();
    }
    for (unsigned i = 0; i < m_receivers.size(); i++) {
        m_receivers.at(i)->detachObservers();
    }
    m_transmitters.clear();
    m_receivers.clear();
}



void RayTracing::setAttributs(map<string, vector<MathematicalProduct *> >
                              m_mathematicalComponents)
{
    if(m_mathematicalComponents.count("Transmitter")) {
        for(unsigned i=0; i<m_mathematicalComponents["Transmitter"].size(); i++) {
            m_transmitters.push_back(static_cast<Tx*>
                                     (m_mathematicalComponents["Transmitter"].at(i)) );

            // The mediator pattern begins here. The transmitter received the
            // algorithminterface to send the correct data between transmitter and receiver.
            //
            // One advantage of this pattern is that the receiver can also send
            // data at transmitter if we want.

            m_transmitters.at(i)->setMediator(this);
        }
    }

    if(m_mathematicalComponents.count("Receiver")) {
        for(unsigned i = 0; i<m_mathematicalComponents["Receiver"].size(); i++) {
            m_receiver = static_cast<Rx*>(m_mathematicalComponents["Receiver"].at(
                             0)) ;
            m_receivers.push_back(static_cast<Rx *>
                                  (m_mathematicalComponents["Receiver"].at(i)));
        }
    }

    if(m_mathematicalComponents.count("Building")) {
        for(unsigned i = 0; i<m_mathematicalComponents["Building"].size(); i++) {
            m_buildings.push_back(static_cast<Building *>
                                  (m_mathematicalComponents["Building"].at(i)) );
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

    if(m_mathematicalComponents.count("Tree")) {
        for (unsigned i = 0; i < m_mathematicalComponents["Tree"].size(); i++) {
            m_trees.push_back(static_cast<MathematicalTreeProduct *>
                              (m_mathematicalComponents["Tree"].at(i)) );
        }
    }
}
