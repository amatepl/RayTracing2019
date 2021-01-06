#ifndef CARFACTORY_H
#define CARFACTORY_H

#include "scenefactory.h"
#include "Product/CarProduct/graphicscarproduct.h"
#include "Product/CarProduct/car.h"

class CarFactory: public SceneFactory
{
public:
    CarFactory(QMenu *productmenu, QGraphicsScene* scene,const float scale);
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic =true) override;
    using SceneFactory::createMathematicalProduct;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, QPolygonF poly, bool linkgraphic);

private:
    struct CarParams {float l=4; float w=1.8;} m_carParams;
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
    float px_to_meter;
};

#endif // CARFACTORY_H
