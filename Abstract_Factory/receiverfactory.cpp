#include "receiverfactory.h"

ReceiverFactory::ReceiverFactory(QMenu* productmenu, InfoWidget *info, QGraphicsScene* scene,const float scale, QWidget *parent):m_parent(parent)
{
    m_productmenu = productmenu;
    m_scene = scene;
    info_widget = info;
    px_to_meter = scale;
}


// Overrides

GraphicsProduct* ReceiverFactory::createGraphicsProduct(int posX, int posY){
    GraphicsRx* graphicsReceiverProduct = new GraphicsRx(true,m_productmenu, m_scene, m_parent);
    Rx* mathematicalReceiverProduct = new Rx(posX, posY);
    mathematicalReceiverProduct->setScale(px_to_meter);
    mathematicalReceiverProduct->setInfoWidget(info_widget);
    graphicsReceiverProduct->attachObserver(mathematicalReceiverProduct);
    graphicsReceiverProduct->setX(posX);
    graphicsReceiverProduct->setY(posY);
    mathematicalReceiverProduct->attachObservable(graphicsReceiverProduct);

//    vector<QPointF> pl_points = mathematicalReceiverProduct->circlePoints(QPointF(250,300),15,20);
//    int rad = 1;
//    for (unsigned i = 0; i < pl_points.size(); i++)
//    {
//        m_scene->addEllipse(pl_points.at(i).x()-rad, pl_points.at(i).y()-rad, rad*2.0, rad*2.0,
//            QPen(QColor(Qt::red)), QBrush(Qt::SolidPattern));
//    }

    return graphicsReceiverProduct;
}

MathematicalProduct* ReceiverFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    Rx* mathematicalReceiverProduct = new Rx(posX,posY);
    mathematicalReceiverProduct->setScale(px_to_meter);
    mathematicalReceiverProduct->setInfoWidget(info_widget);
    if (linkgraphic){
        GraphicsRx* graphicsReceiverProduct = new GraphicsRx(false,m_productmenu, m_scene, m_parent);
        graphicsReceiverProduct->attachObserver(mathematicalReceiverProduct);
        graphicsReceiverProduct->setX(posX);
        graphicsReceiverProduct->setY(posY);
        mathematicalReceiverProduct->attachObservable(graphicsReceiverProduct);
    }
    return mathematicalReceiverProduct;
}

MathematicalProduct* ReceiverFactory::createMathematicalProduct(MathematicalProduct *original, bool linkgraphic){
    Rx* mathematicalReceiverProduct = new Rx(dynamic_cast<Rx*>(original));
    mathematicalReceiverProduct->setInfoWidget(info_widget);
    mathematicalReceiverProduct->setScale(px_to_meter);
    if (linkgraphic){
        GraphicsRx* graphicsReceiverProduct = new GraphicsRx(false,m_productmenu, m_scene, m_parent);
        graphicsReceiverProduct->attachObserver(mathematicalReceiverProduct);
        graphicsReceiverProduct->setX(mathematicalReceiverProduct->getPosX());
        graphicsReceiverProduct->setY(mathematicalReceiverProduct->getPosY());
        mathematicalReceiverProduct->attachObservable(graphicsReceiverProduct);
    }
    return mathematicalReceiverProduct;
}
