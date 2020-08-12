#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

#include "scenefactory.h"
#include "Product/BuildingProduct/graphicsbuildingproduct.h"
#include "Product/BuildingProduct/mathematicalbuildingproduct.h"

class BuildingFactory: public SceneFactory
{
public:
    BuildingFactory(QMenu *productmenu, QGraphicsScene* scene,const float scale);
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic = true) override;
    using SceneFactory::createMathematicalProduct;
    MathematicalProduct * createMathematicalProduct(QPolygonF polygone, bool linkgraphic = true);


private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
    float px_to_meter;
};

#endif // BUILDINGFACTORY_H
