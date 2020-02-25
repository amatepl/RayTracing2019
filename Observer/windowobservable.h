#ifndef WINDOWOBSERVABLE_H
#define WINDOWOBSERVABLE_H

#include "windowobserver.h"

class WindowObservable{
public:
    enum Mode{MoveItem,InsertTransmitter,InsertReceiver,InsertBuilding,InsertTree,InsertCar};
    virtual ~WindowObservable(){}

    virtual void attachObserver(WindowObserver*) = 0;
    virtual void detachObserver(WindowObserver*) = 0;
    virtual void notify(int mode) = 0;
    virtual void answer() = 0;
};

#endif // WINDOWOBSERVABLE_H
