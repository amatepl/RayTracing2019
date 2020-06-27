#include "receiverfactory.h"

ReceiverFactory::ReceiverFactory(QMenu* productmenu, QGraphicsScene* scene)
{
    m_productmenu = productmenu;
    m_scene = scene;
}


// Overrides

GraphicsProduct* ReceiverFactory::createGraphicsProduct(int posX, int posY){
    GraphicsReceiverProduct* graphicsReceiverProduct = new GraphicsReceiverProduct(true,m_productmenu, m_scene);
    MathematicalReceiverProduct* mathematicalReceiverProduct = new MathematicalReceiverProduct(posX, posY);
    graphicsReceiverProduct->attachObserver(mathematicalReceiverProduct);
    graphicsReceiverProduct->setX(posX);
    graphicsReceiverProduct->setY(posY);
    mathematicalReceiverProduct->attachObservable(graphicsReceiverProduct);
    return graphicsReceiverProduct;
}

MathematicalProduct* ReceiverFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    MathematicalReceiverProduct* mathematicalReceiverProduct = new MathematicalReceiverProduct(posX,posY);
    if (linkgraphic){
        GraphicsReceiverProduct* graphicsReceiverProduct = new GraphicsReceiverProduct(true,m_productmenu, m_scene);
        graphicsReceiverProduct->attachObserver(mathematicalReceiverProduct);
    }
    return mathematicalReceiverProduct;
}
