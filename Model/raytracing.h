#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "Model/imagesmethod.h"
#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"
#include "Abstract_Factory/rayfactory.h"
#include "Model/algorithmInterface.h"
#include "Model/imagesmethod.h"

class RayTracing: public AlgorithmInterface, public ImagesMethod
{
public:
    RayTracing(MathematicalTransmitterProduct* transmitter, MathematicalReceiverProduct* receiver);
    RayTracing();

    //AlgorithmInterface
    MathematicalComponent* compute(vector<MathematicalTransmitterProduct *> transmitters, MathematicalReceiverProduct* receiver,
                                   vector<MathematicalBuildingProduct*> buildings) override;
    MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> mathematicalComponents) override;

    void setAttributs(map<string,vector<MathematicalProduct*>> mathematicalComponents);

};

#endif // RAYTRACING_H
