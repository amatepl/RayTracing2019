#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <vector>
#include <map>
#include <QPointF>

class MathematicalComponent;
class MathematicalTransmitterProduct;
class MathematicalReceiverProduct;
class MathematicalBuildingProduct;
class MathematicalProduct;
class ProductObservable;
class ReceiverFactory;
class ProductObserver;

using namespace std;

class AlgorithmInterface
{
public:
//    virtual MathematicalComponent* compute(vector<MathematicalTransmitterProduct*> transmitter, MathematicalReceiverProduct* receiver,
//                                           vector<MathematicalBuildingProduct*> buildings) =0;
    virtual MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> m_mathematicalComponents, ReceiverFactory* receiverfactory) =0;

    // Method used in the mediator design pattern where the algorithminterface is the mediator.
    virtual void sendData(MathematicalProduct* transmitter, MathematicalProduct *receiver) = 0;
    virtual void pathLossComputation(std::vector<QPointF> points, ProductObservable* true_receiver, ProductObserver* true_transmitter) = 0;
    virtual void clearWorkspace() = 0;
};

#endif // ALGORITHMINTERFACE_H
