#include "transmitterfactory.h"

TransmitterFactory::TransmitterFactory()
{

}

GraphicsComponent* TransmitterFactory::createGraphicsComponent(int posX, int posY, QMenu* productmenu,QGraphicsScene* scene){
    GraphicsTransmitterProduct* graphicsProduct = new GraphicsTransmitterProduct(0,0,true,productmenu, scene);
    MathematicalTransmitterProduct* mathematicalProduct = new MathematicalTransmitterProduct(graphicsProduct);
    graphicsProduct->setMathematicalComponent(mathematicalProduct);
    return graphicsProduct;
}
