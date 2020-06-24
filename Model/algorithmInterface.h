#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

class MathematicalComponent;
class MathematicalTransmitterProduct;
class MathematicalReceiverProduct;

class AlgorithmInterface
{
public:
    virtual MathematicalComponent* compute(MathematicalTransmitterProduct* transmitter, MathematicalReceiverProduct* receiver) =0;
};

#endif // ALGORITHMINTERFACE_H
