#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

#include "scenefactory.h"
#include "Product/BuildingProduct/graphicsbuildingproduct.h"
#include "Product/BuildingProduct/mathematicalbuildingproduct.h"

class BuildingFactory: public SceneFactory
{
public:
    BuildingFactory();
    GraphicsComponent * createGraphicsComponent(int posX, int posY, QMenu *productmenu, QGraphicsScene* scene) override;
};

#endif // BUILDINGFACTORY_H
