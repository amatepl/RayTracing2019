#include "treefactory.h"

TreeFactory::TreeFactory()
{

}

GraphicsComponent* TreeFactory::createGraphicsComponent(int posX, int posY, QMenu* productmenu,QGraphicsScene* scene){
    GraphicsTreeProduct* graphicsProduct = new GraphicsTreeProduct(0,0,productmenu, scene);
    MathematicalTreeProduct* mathematicalProduct = new MathematicalTreeProduct(graphicsProduct);
    graphicsProduct->setMathematicalComponent(mathematicalProduct);
    return graphicsProduct;
}
