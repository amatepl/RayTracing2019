#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include "windowobserver.h"

class GraphicsProduct;

class AppInterface{
public:
    enum GraphicsMode{MoveItem,InsertTransmitter,InsertReceiver,InsertBuilding,InsertTree,InsertCar};
    enum ActionMode{DeleteItem,PropertiesItem,LaunchRayTracing};

    virtual ~AppInterface(){}

    virtual void answer(GraphicsProduct* graphic) = 0;
};

#endif //  APPINTERFACE_H
