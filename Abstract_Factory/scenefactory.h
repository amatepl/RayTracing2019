#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include "Product/TransmitterProduct/transmitterproduct.h"
#include "Product/ReceiverProduct/receiverproduct.h"
#include "Product/BuildingProduct/buildingproduct.h"
#include "Product/TreeProduct/treeproduct.h"
#include "Product/CarProduct/carproduct.h"
#include "Composite/graphicscomponent.h"
#include <QMenu>
#include <QGraphicsScene>

class SceneFactory{
public:
    virtual ~SceneFactory() {}
    virtual GraphicsComponent* createGraphicsComponent(int posX, int posY, QMenu* productmenu, QGraphicsScene* scene) = 0;

};

#endif // SCENEFACTORY_H
