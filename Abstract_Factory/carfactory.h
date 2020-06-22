#ifndef CARFACTORY_H
#define CARFACTORY_H

#include "scenefactory.h"
#include "Product/CarProduct/graphicscarproduct.h"
#include "Product/CarProduct/mathematicalcarproduct.h"

class CarFactory: public SceneFactory
{
public:
    CarFactory();
    GraphicsComponent * createGraphicsComponent(int posX, int posY, QMenu *productmenu, QGraphicsScene* scene) override;
};

#endif // CARFACTORY_H
