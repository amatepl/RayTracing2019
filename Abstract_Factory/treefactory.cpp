#include "treefactory.h"

TreeFactory::TreeFactory(QMenu *productmenu, QGraphicsScene* scene)
{
    m_productmenu = productmenu;
    m_scene = scene;
}

GraphicsProduct* TreeFactory::createGraphicsProduct(int posX, int posY){
    GraphicsTreeProduct* graphicsProduct = new GraphicsTreeProduct(m_productmenu, m_scene);
    QPolygonF poly(QRectF(0,0,posX,posY));
    MathematicalTreeProduct* mathematicalProduct = new MathematicalTreeProduct(poly, QPointF(posX,posY));
    graphicsProduct->attachObserver(mathematicalProduct);
    //graphicsProduct->setX(posX);
    //graphicsProduct->setY(posY);
    mathematicalProduct->attachObservable(graphicsProduct);
    return graphicsProduct;
}

MathematicalProduct* TreeFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    QRectF rect(posX,posY,50,50);
    QPolygonF poly(rect);

    MathematicalTreeProduct* mathematicalProduct = new MathematicalTreeProduct(poly, QPointF(posX,posY));
    if (linkgraphic){
        GraphicsTreeProduct* graphicsProduct = new GraphicsTreeProduct(m_productmenu, m_scene);
        graphicsProduct->attachObserver(mathematicalProduct);
//        graphicsProduct->setX(posX);
//        graphicsProduct->setY(posY);
        mathematicalProduct->attachObservable(graphicsProduct);
    }
    return mathematicalProduct;
}
