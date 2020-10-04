#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <vector>
#include <map>
#include <QPointF>

class MathematicalComponent;
class Tx;
class Rx;
class Building;
class MathematicalProduct;
class ProductObservable;
class ReceiverFactory;
class ProductObserver;

using namespace std;

class AlgorithmInterface
{
public:
//    virtual MathematicalComponent* compute(vector<Tx*> transmitter, Rx* receiver,
//                                           vector<Building*> buildings) =0;
    virtual MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> m_mathematicalComponents, ReceiverFactory* receiverfactory) =0;

    virtual void clearWorkspace() = 0;
};

#endif // ALGORITHMINTERFACE_H
