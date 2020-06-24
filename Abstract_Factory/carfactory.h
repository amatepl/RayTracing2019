#ifndef CARFACTORY_H
#define CARFACTORY_H

#include "scenefactory.h"
#include "Product/CarProduct/graphicscarproduct.h"
#include "Product/CarProduct/mathematicalcarproduct.h"

class CarFactory: public SceneFactory
{
public:
    CarFactory(QMenu *productmenu, QGraphicsScene* scene);
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic) override;

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
};

#endif // CARFACTORY_H
