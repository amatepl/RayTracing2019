#ifndef CARFACTORY_H
#define CARFACTORY_H

#include "scenefactory.h"
#include "Product/CarProduct/graphicscarproduct.h"
#include "Product/CarProduct/mathematicalcarproduct.h"

class CarFactory: public SceneFactory
{
public:
    CarFactory(QMenu *productmenu, QGraphicsScene* scene,const float scale);
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic =true) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, QPolygonF poly, bool linkgraphic);

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
    float px_to_meter;
};

#endif // CARFACTORY_H
