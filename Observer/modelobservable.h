#ifndef MODELOBSERVABLE_H
#define MODELOBSERVABLE_H

class MathematicalTransmitterProduct;

class ModelObservable{
public:
    virtual void notify(MathematicalTransmitterProduct* transmitter) = 0;
};

#endif // MODELOBSERVABLE_H
