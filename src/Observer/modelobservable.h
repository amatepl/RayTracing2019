#ifndef MODELOBSERVABLE_H
#define MODELOBSERVABLE_H

class Tx;

class ModelObservable{
public:
    virtual void notify(Tx* transmitter) = 0;
};

#endif // MODELOBSERVABLE_H
