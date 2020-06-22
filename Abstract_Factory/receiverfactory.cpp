#include "receiverfactory.h"

ReceiverFactory::ReceiverFactory(QMenu* productmenu)
{
    m_productmenu = productmenu;
}


// Overrides

GraphicsComponent* ReceiverFactory::createGraphicsComponent(int posX, int posY, QMenu* productmenu,QGraphicsScene* scene){
    GraphicsReceiverProduct* graphicsReceiverProduct = new GraphicsReceiverProduct(posX,posY,true,productmenu, scene);
    MathematicalReceiverProduct* mathematicalReceiverProduct = new MathematicalReceiverProduct(graphicsReceiverProduct);
    graphicsReceiverProduct->setMathematicalComponent(mathematicalReceiverProduct);
    return graphicsReceiverProduct;
}
