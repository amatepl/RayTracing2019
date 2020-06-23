#ifndef ABSTRACTALGORITHMFACTORY_H
#define ABSTRACTALGORITHMFACTORY_H

#include "Model/algorithmInterface.h"

class MathematicalTransmitterProduct;
class MathematicalReceiverProduct;


class AbstractAlgorithmFactory{
public:
    virtual AlgorithmInterface* createAlgorithm(MathematicalTransmitterProduct *transmitter, MathematicalReceiverProduct *receiver) = 0;
};

#endif // ABSTRACTALGORITHMFACTORY_H
