#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

#include "scenefactory.h"
#include "Product/BuildingProduct/graphicsbuilding.h"
#include "Product/BuildingProduct/building.h"

class BuildingFactory: public SceneFactory
{
public:
    BuildingFactory(QMenu *productmenu, QGraphicsScene* scene,const float scale);
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic = true) override;
    using SceneFactory::createMathematicalProduct;
    MathematicalProduct * createMathematicalProduct(QPolygonF polygone, bool linkgraphic = true);
    void setScale(const double &px_to_m) override;

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
    float px_to_meter;
};

#endif // BUILDINGFACTORY_H
