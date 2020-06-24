#include "carfactory.h"

CarFactory::CarFactory(QMenu* productmenu, QGraphicsScene* scene)
{
    m_productmenu = productmenu;
    m_scene = scene;
}

GraphicsProduct* CarFactory::createGraphicsProduct(int posX, int posY){
    GraphicsCarProduct* graphicsProduct = new GraphicsCarProduct(m_productmenu, m_scene);
    MathematicalCarProduct* mathematicalProduct = new MathematicalCarProduct(posX, posY);
    graphicsProduct->attachObserver(mathematicalProduct);
    graphicsProduct->setX(posX);
    graphicsProduct->setY(posY);
    return graphicsProduct;
}

MathematicalProduct* CarFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    MathematicalCarProduct* mathematicalProduct = new MathematicalCarProduct(posX,posY);
    if (linkgraphic){
        GraphicsCarProduct* graphicsProduct = new GraphicsCarProduct(m_productmenu, m_scene);
        graphicsProduct->attachObserver(mathematicalProduct);
    }
    return mathematicalProduct;
}
