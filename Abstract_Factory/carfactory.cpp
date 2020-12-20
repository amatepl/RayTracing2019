#include "carfactory.h"

CarFactory::CarFactory(QMenu* productmenu, QGraphicsScene* scene,const float scale)
{
    m_productmenu = productmenu;
    m_scene = scene;
    px_to_meter = scale;
}

GraphicsProduct* CarFactory::createGraphicsProduct(int posX, int posY){
    GraphicsCarProduct* graphicsProduct = new GraphicsCarProduct(m_productmenu, m_scene);
    QRectF rect = graphicsProduct->sceneBoundingRect();
    Car* mathematicalProduct = new Car(rect, QPointF(posX,posY));
    mathematicalProduct->setScale(px_to_meter);
    graphicsProduct->attachObserver(mathematicalProduct);
    graphicsProduct->setX(posX);
    graphicsProduct->setY(posY);
    mathematicalProduct->attachObservable(graphicsProduct);
    return graphicsProduct;
}

MathematicalProduct* CarFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic ){
    QRectF rect(posX - 11, posY - 11,22,22);
    Car* mathematicalProduct = new Car(rect, QPointF(posX,posY));
    mathematicalProduct->setScale(px_to_meter);
    if (linkgraphic){
        GraphicsCarProduct* graphicsProduct = new GraphicsCarProduct(m_productmenu, m_scene);
        graphicsProduct->attachObserver(mathematicalProduct);
        graphicsProduct->setX(posX);
        graphicsProduct->setY(posY);
        mathematicalProduct->attachObservable(graphicsProduct);
    }
    return mathematicalProduct;
}

MathematicalProduct* CarFactory::createMathematicalProduct(int posX, int posY, QPolygonF poly, bool linkgraphic){

    Building* mathematicalCarProduct = new Car(poly,QPointF(posX,posY));
    mathematicalCarProduct->setScale(px_to_meter);
    if (linkgraphic){
        GraphicsCarProduct* graphicsCarProduct = new GraphicsCarProduct(poly, m_productmenu, m_scene);
        graphicsCarProduct->attachObserver(mathematicalCarProduct);
//        float w = static_cast<Car *>(mathematicalCarProduct)->getWidth();
//        float l = static_cast<Car *>(mathematicalCarProduct)->getLength();
//        graphicsCarProduct->setPos(QPointF(posX + w/2,posY + l));
        graphicsCarProduct->setPos(poly[0]);
        mathematicalCarProduct->attachObservable(graphicsCarProduct);
    }
    return mathematicalCarProduct;
}
