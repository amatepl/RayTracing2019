#ifndef ABSTRACTALGORITHMFACTORY_H
#define ABSTRACTALGORITHMFACTORY_H

#include "Model/algorithmInterface.h"

class Tx;
class Rx;


class AbstractAlgorithmFactory{
public:
    virtual AlgorithmInterface* createAlgorithm(Tx *transmitter, Rx *receiver) = 0;
};

#endif // ABSTRACTALGORITHMFACTORY_H
