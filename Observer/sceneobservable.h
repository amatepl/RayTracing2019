#ifndef SCENEOBSERVABLE_H
#define SCENEOBSERVABLE_H

#include "sceneobserver.h"
#include "Composite/graphicscomponent.h"

class SceneObservable{

public:
    virtual ~SceneObservable(){}

    virtual void attachObserver(SceneObserver*) = 0;
    virtual void detachObserver(SceneObserver*) = 0;
    virtual void notify(GraphicsComponent*) = 0;
};


#endif // SCENEOBSERVABLE_H
