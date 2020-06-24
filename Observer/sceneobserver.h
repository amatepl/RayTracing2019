#ifndef SCENEOBSERVER_H
#define SCENEOBSERVER_H

#include "Product/graphicsproduct.h"

class SceneObserver{

public:
    virtual ~SceneObserver(){}
    virtual void updateNewProperties(GraphicsProduct*) = 0;
    virtual void updateChangeProperties(GraphicsProduct*) = 0;
};

#endif // SCENEOBSERVER_H
