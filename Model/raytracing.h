#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "Model/imagesmethod.h"
#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"
#include "Abstract_Factory/rayfactory.h"
#include "Model/algorithmInterface.h"

class RayTracing: public AlgorithmInterface
{
public:
    RayTracing(MathematicalTransmitterProduct* transmitter, MathematicalReceiverProduct* receiver);
    RayTracing();

    //AlgorithmInterface
    MathematicalComponent* compute(MathematicalTransmitterProduct* transmitter, MathematicalReceiverProduct* receiver) override;

};

#endif // RAYTRACING_H
