#ifndef SCENEOBSERVABLE_H
#define SCENEOBSERVABLE_H

#include "sceneobserver.h"
#include "Product/graphicsproduct.h"

class SceneObservable{

public:
    virtual ~SceneObservable(){}

    virtual void attachObserver(SceneObserver*) = 0;
    virtual void detachObserver(SceneObserver*) = 0;
    virtual void notifyNewProperties(GraphicsProduct*) = 0;
    virtual void notifyChangeProperties(GraphicsProduct*) = 0;
};


#endif // SCENEOBSERVABLE_H
