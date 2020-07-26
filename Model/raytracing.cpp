#include "raytracing.h"

RayTracing::RayTracing(MathematicalTransmitterProduct *transmitter,
                       MathematicalReceiverProduct *receiver)
{
    RayFactory* rayFactory = new RayFactory(true, m_scene);
    m_rayFactory = rayFactory;
    transmitter->setRayFactory(rayFactory);

}


RayTracing::RayTracing()
{

}


//MathematicalComponent* RayTracing::compute(vector<MathematicalTransmitterProduct*>
//        transmitters, MathematicalReceiverProduct* receiver,
//        vector<MathematicalBuildingProduct *> buildings)
//{
//    m_transmitters = transmitters;
//    m_receiver=receiver;
//    m_buildings = buildings;
//    reflectionsNumber = 1;



//    //createImages();
//    illuminationZones();

//    RayFactory* rayFactory = new RayFactory(true, m_scene);
//    m_rayFactory = rayFactory;
//    cout<<"Before adding trees"<<endl;

//    for(unsigned i =0; i<transmitters.size(); i++) {
//        transmitters.at(i)->setRayFactory(rayFactory);
//        QPolygonF illuminatedZone = transmitters.at(i)->getIlluminatedZone();
//        for (unsigned j = 0; j<m_trees.size(); j++) {
//            if (illuminatedZone.intersects(*m_trees.at(j))) {
//                transmitters.at(i)->appendTree(m_trees.at(j));
//            }
//        }
//    }

//    return nullptr;
//}


MathematicalComponent* RayTracing::compute(map<string,vector<MathematicalProduct *>>
        mathematicalComponents, ReceiverFactory* receiverfactory)
{


    setAttributs(mathematicalComponents);

    m_receiverfactory = receiverfactory;

    reflectionsNumber = 3;

    RayFactory* rayFactory = new RayFactory(true, m_scene);
    m_rayFactory = rayFactory;


//    for(unsigned i =0; i<m_transmitters.size(); i++) {
//        m_transmitters.at(i)->setRayFactory(rayFactory);
//    }

    //createImages();
    illuminationZones();

    for(unsigned i =0; i<m_transmitters.size(); i++) {
        m_transmitters.at(i)->setRayFactory(rayFactory);
        QPolygonF illuminatedZone = m_transmitters.at(i)->getIlluminatedZone();
        for (unsigned j = 0; j<m_trees.size(); j++) {
            if (illuminatedZone.intersects(*m_trees.at(j))) {
                m_transmitters.at(i)->appendTree(m_trees.at(j));
            }
        }
    }

    for (unsigned i = 0; i < m_receivers.size(); i++) {
        //((MathematicalReceiverProduct*)m_mathematicalComponents["Receiver"].at(i))->notifyObservers();
        m_receivers.at(i)->notifyObservers();
    }

    return nullptr;
}


void RayTracing::sendData(MathematicalProduct *transmitter, MathematicalProduct *receiver)
{
    // Send data is used to share some computed data from the transmitter to the receiver.
    MathematicalTransmitterProduct* true_transmitter =
        static_cast<MathematicalTransmitterProduct*>(transmitter);

    MathematicalReceiverProduct* true_receiver =
        static_cast<MathematicalReceiverProduct*>(receiver);

    true_receiver->setFrequency(true_transmitter->getFrequency());
    true_receiver->setBandwidth(true_transmitter->getBandwidth());
    true_receiver->setImpulseTau(true_transmitter->impulseTau(true_receiver));
    true_receiver->setImpulseAttenuation(true_transmitter->impulseAttenuation(true_receiver));
    true_receiver->setPathLoss(true_transmitter->pathLoss(copy_receiver));
    true_receiver->setTransmitterDistance(true_transmitter->receiverDistance(true_receiver));
    true_receiver->riceFactor(true_transmitter->riceFactor(true_receiver));
    true_receiver->setDopplerShift(true_transmitter->dopplerShift(true_receiver));
    true_receiver->computeMinPrx();

//    true_receiver->save();
}


void RayTracing::pathLossComputation(std::vector<QPointF> points,
                                     ProductObservable *true_receiver, ProductObserver* true_transmitter)
{
    MathematicalReceiverProduct* original_receiver = dynamic_cast<MathematicalReceiverProduct *>
            (true_receiver);

    copy_receiver = (MathematicalReceiverProduct*)m_receiverfactory->createMathematicalProduct(original_receiver,false);

    MathematicalTransmitterProduct* original_transmitter = (MathematicalTransmitterProduct *)
            true_transmitter;

    original_transmitter->erasePathLoss(original_receiver);
    original_transmitter->activePathLoss(false);
    original_transmitter->computePathLoss(true);

    for (unsigned long i = 0; i<points.size()-1; i++) {
        copy_receiver->setPosX(points.at(i).x());
        copy_receiver->setPosY(points.at(i).y());
    }
    original_transmitter->activePathLoss(true);
    original_transmitter->computePathLoss(false);

    delete copy_receiver;

}

void RayTracing::clearWorkspace()
{
    for(unsigned i=0; i<m_transmitters.size(); i++) {
        m_transmitters.at(i)->clearAll();
    }
    for(unsigned i=0; i<m_receivers.size(); i++) {
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
            m_transmitters.push_back(static_cast<MathematicalTransmitterProduct*>
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
            m_receiver = static_cast<MathematicalReceiverProduct*>(m_mathematicalComponents["Receiver"].at(
                             0)) ;
            m_receivers.push_back(static_cast<MathematicalReceiverProduct *>
                                  (m_mathematicalComponents["Receiver"].at(i)));
        }
    }

    if(m_mathematicalComponents.count("Building")) {
        for(unsigned i = 0; i<m_mathematicalComponents["Building"].size(); i++) {
            m_buildings.push_back(static_cast<MathematicalBuildingProduct *>
                                  (m_mathematicalComponents["Building"].at(i)) );
        }
    }

    if(m_mathematicalComponents.count("Car")) {
        for(unsigned i = 0; i<m_mathematicalComponents["Car"].size(); i++) {
            m_cars.push_back(static_cast<MathematicalCarProduct *>
                                  (m_mathematicalComponents["Car"].at(i)) );

            m_buildings.push_back(static_cast<MathematicalBuildingProduct *>
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
