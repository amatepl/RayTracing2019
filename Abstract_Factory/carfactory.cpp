#include "carfactory.h"

CarFactory::CarFactory(QMenu* productmenu, QGraphicsScene* scene)
{
    m_productmenu = productmenu;
    m_scene = scene;
}

GraphicsProduct* CarFactory::createGraphicsProduct(int posX, int posY){
    GraphicsCarProduct* graphicsProduct = new GraphicsCarProduct(m_productmenu, m_scene);
    QRectF rect = graphicsProduct->sceneBoundingRect();
    MathematicalCarProduct* mathematicalProduct = new MathematicalCarProduct(rect, QPointF(posX,posY));
    graphicsProduct->attachObserver(mathematicalProduct);
    graphicsProduct->setX(posX);
    graphicsProduct->setY(posY);
    mathematicalProduct->attachObservable(graphicsProduct);
    return graphicsProduct;
}

MathematicalProduct* CarFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic ){
    QRectF rect(posX - 11, posY - 11,22,22);
    MathematicalCarProduct* mathematicalProduct = new MathematicalCarProduct(rect, QPointF(posX,posY));
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

    MathematicalBuildingProduct* mathematicalCarProduct = new MathematicalCarProduct(poly,QPointF(posX,posY));
    if (linkgraphic){
        GraphicsCarProduct* graphicsCarProduct = new GraphicsCarProduct(poly,m_productmenu, m_scene);
        graphicsCarProduct->attachObserver(mathematicalCarProduct);
        graphicsCarProduct->setPos(QPointF(posX,posY));
        mathematicalCarProduct->attachObservable(graphicsCarProduct);
    }
    return mathematicalCarProduct;
}
