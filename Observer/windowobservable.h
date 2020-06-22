#ifndef WINDOWOBSERVABLE_H
#define WINDOWOBSERVABLE_H

#include "windowobserver.h"
#include "Product/sceneproduct.h"

class WindowObservable{
public:
    enum Mode{MoveItem,InsertTransmitter,InsertReceiver,InsertBuilding,InsertTree,InsertCar,DeleteItem
             ,PropertiesItem};
    virtual ~WindowObservable(){}

    virtual void attachObserver(WindowObserver*) = 0;
    virtual void detachObserver(WindowObserver*) = 0;
    virtual void notify(int mode) = 0;
    virtual void answer(SceneProduct *sceneproduct) = 0;
    virtual void modelAnswer(SceneProduct *sceneproduct) = 0;

};

#endif // WINDOWOBSERVABLE_H
