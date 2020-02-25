#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include "Product/TransmitterProduct/transmitterproduct.h"
#include "Product/ReceiverProduct/receiverproduct.h"
#include "Product/BuildingProduct/buildingproduct.h"
#include "Product/TreeProduct/treeproduct.h"
#include "Product/CarProduct/carproduct.h"

class SceneFactory{
public:
    virtual ~SceneFactory() {}
    virtual TransmitterProduct* createTransmitterProduct() = 0;
    virtual ReceiverProduct* createReceiverProduct() = 0;
    virtual BuildingProduct* createBuildingProduct() = 0;
    virtual TreeProduct* createTreeProduct() = 0;
    virtual CarProduct* createCarProduct() = 0;

};

#endif // SCENEFACTORY_H
