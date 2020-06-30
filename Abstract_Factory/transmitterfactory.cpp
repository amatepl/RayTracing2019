#include "transmitterfactory.h"

TransmitterFactory::TransmitterFactory(QMenu* productmenu, QGraphicsScene* scene)
{
    m_productmenu = productmenu;
    m_scene = scene;
}


GraphicsProduct* TransmitterFactory::createGraphicsProduct(int posX, int posY){
    GraphicsTransmitterProduct* graphicsProduct = new GraphicsTransmitterProduct(m_productmenu, m_scene);
    MathematicalTransmitterProduct* mathematicalProduct = new MathematicalTransmitterProduct(posX, posY);
    graphicsProduct->attachObserver(mathematicalProduct);
    graphicsProduct->setX(posX);
    graphicsProduct->setY(posY);
    mathematicalProduct->MathematicalProduct::attachObservable(graphicsProduct);
    return graphicsProduct;
}

MathematicalProduct* TransmitterFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    MathematicalTransmitterProduct* mathematicalProduct = new MathematicalTransmitterProduct(posX,posY);
    if (linkgraphic){
        GraphicsTransmitterProduct* graphicsProduct = new GraphicsTransmitterProduct(m_productmenu, m_scene);
        graphicsProduct->attachObserver(mathematicalProduct);
    }
    return mathematicalProduct;
}
