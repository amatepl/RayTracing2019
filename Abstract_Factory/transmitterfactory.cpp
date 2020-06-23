#include "transmitterfactory.h"

TransmitterFactory::TransmitterFactory()
{

}

GraphicsComponent* TransmitterFactory::createGraphicsComponent(int posX, int posY, QMenu* productmenu,QGraphicsScene* scene){
    GraphicsTransmitterProduct* graphicsProduct = new GraphicsTransmitterProduct(posX,posY,true,productmenu, scene);
    MathematicalTransmitterProduct* mathematicalProduct = new MathematicalTransmitterProduct(posX,posY);
    graphicsProduct->setMathematicalComponent(mathematicalProduct);
    cout<<posX<<", "<<posY<<endl;
    return graphicsProduct;
}
