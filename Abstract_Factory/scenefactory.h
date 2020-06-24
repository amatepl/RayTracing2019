#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

//#include "Product/TransmitterProduct/transmitterproduct.h"
//#include "Product/ReceiverProduct/receiverproduct.h"
//#include "Product/BuildingProduct/buildingproduct.h"
//#include "Product/TreeProduct/treeproduct.h"
//#include "Product/CarProduct/carproduct.h"
#include "Product/graphicsproduct.h"
#include <QMenu>
#include <QGraphicsScene>

class SceneFactory{
public:
    virtual ~SceneFactory() {}
    virtual GraphicsProduct* createGraphicsProduct(int posX, int posY) = 0;
    virtual MathematicalProduct* createMathematicalProduct(int posX, int posY, bool linkgraphic) = 0;

};

#endif // SCENEFACTORY_H
