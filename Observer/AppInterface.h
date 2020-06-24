#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include "windowobserver.h"
#include "Product/sceneproduct.h"

class AppInterface{
public:
    enum GraphicsMode{MoveItem,InsertTransmitter,InsertReceiver,InsertBuilding,InsertTree,InsertCar};
    enum ActionMode{DeleteItem,PropertiesItem};

    virtual ~AppInterface(){}

    virtual void answer() = 0;
};

#endif //  APPINTERFACE_H
