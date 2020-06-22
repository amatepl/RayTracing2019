#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "scenefactory.h"
#include "Product/TreeProduct/graphicstreeproduct.h"
#include "Product/TreeProduct/mathematicaltreeproduct.h"

class TreeFactory: public SceneFactory
{
public:
    TreeFactory();
    GraphicsComponent * createGraphicsComponent(int posX, int posY, QMenu *productmenu, QGraphicsScene* scene) override;
};

#endif // TREEFACTORY_H
