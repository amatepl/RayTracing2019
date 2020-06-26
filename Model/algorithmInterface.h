#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <vector>
#include <map>

class MathematicalComponent;
class MathematicalTransmitterProduct;
class MathematicalReceiverProduct;
class MathematicalBuildingProduct;
class MathematicalProduct;

using namespace std;

class AlgorithmInterface
{
public:
    virtual MathematicalComponent* compute(vector<MathematicalTransmitterProduct*> transmitter, MathematicalReceiverProduct* receiver,
                                           vector<MathematicalBuildingProduct*> buildings) =0;
    virtual MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> m_mathematicalComponents) =0;
};

#endif // ALGORITHMINTERFACE_H
