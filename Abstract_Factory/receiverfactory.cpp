#include "receiverfactory.h"

ReceiverFactory::ReceiverFactory(QMenu* productmenu, InfoWidget *info, QGraphicsScene* scene)
{
    m_productmenu = productmenu;
    m_scene = scene;
    info_widget = info;
}


// Overrides

GraphicsProduct* ReceiverFactory::createGraphicsProduct(int posX, int posY){
    GraphicsReceiverProduct* graphicsReceiverProduct = new GraphicsReceiverProduct(true,m_productmenu, m_scene);
    MathematicalReceiverProduct* mathematicalReceiverProduct = new MathematicalReceiverProduct(posX, posY);
    mathematicalReceiverProduct->setInfoWidget(info_widget);
    graphicsReceiverProduct->attachObserver(mathematicalReceiverProduct);
    graphicsReceiverProduct->setX(posX);
    graphicsReceiverProduct->setY(posY);
    mathematicalReceiverProduct->attachObservable(graphicsReceiverProduct);
    return graphicsReceiverProduct;
}

MathematicalProduct* ReceiverFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    MathematicalReceiverProduct* mathematicalReceiverProduct = new MathematicalReceiverProduct(posX,posY);
    mathematicalReceiverProduct->setInfoWidget(info_widget);
    if (linkgraphic){
        GraphicsReceiverProduct* graphicsReceiverProduct = new GraphicsReceiverProduct(false,m_productmenu, m_scene);
        graphicsReceiverProduct->attachObserver(mathematicalReceiverProduct);
        graphicsReceiverProduct->setX(posX);
        graphicsReceiverProduct->setY(posY);
        mathematicalReceiverProduct->attachObservable(graphicsReceiverProduct);
    }
    return mathematicalReceiverProduct;
}

MathematicalProduct* ReceiverFactory::createMathematicalProduct(MathematicalProduct *original, bool linkgraphic){
    MathematicalReceiverProduct* mathematicalReceiverProduct = new MathematicalReceiverProduct(dynamic_cast<MathematicalReceiverProduct*>(original));
    mathematicalReceiverProduct->setInfoWidget(info_widget);
    if (linkgraphic){
        GraphicsReceiverProduct* graphicsReceiverProduct = new GraphicsReceiverProduct(false,m_productmenu, m_scene);
        graphicsReceiverProduct->attachObserver(mathematicalReceiverProduct);
        graphicsReceiverProduct->setX(mathematicalReceiverProduct->getPosX());
        graphicsReceiverProduct->setY(mathematicalReceiverProduct->getPosY());
        mathematicalReceiverProduct->attachObservable(graphicsReceiverProduct);
    }
    return mathematicalReceiverProduct;
}
