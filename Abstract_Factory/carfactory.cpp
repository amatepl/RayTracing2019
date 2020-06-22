#include "carfactory.h"

CarFactory::CarFactory()
{

}

GraphicsComponent* CarFactory::createGraphicsComponent(int posX, int posY, QMenu* productmenu,QGraphicsScene* scene){
    GraphicsCarProduct* graphicsProduct = new GraphicsCarProduct(0,0,0,true,productmenu, scene);
    MathematicalCarProduct* mathematicalProduct = new MathematicalCarProduct(graphicsProduct);
    graphicsProduct->setMathematicalComponent(mathematicalProduct);
    return graphicsProduct;
}
