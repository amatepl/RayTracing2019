#include "buildingfactory.h"

BuildingFactory::BuildingFactory(QMenu *productmenu, QGraphicsScene* scene,const float scale)
{
    m_productmenu = productmenu;
    m_scene = scene;
    px_to_meter = scale;
}

GraphicsProduct* BuildingFactory::createGraphicsProduct(int posX, int posY){
    GraphicsBuilding* graphicsProduct = new GraphicsBuilding(m_productmenu,m_scene);
    QVector<QPointF> points = graphicsProduct->polygon();
    Building* mathematicalProduct = new Building(points);
    mathematicalProduct->setScale(px_to_meter);
    graphicsProduct->attachObserver(mathematicalProduct);
    graphicsProduct->setX(posX);
    graphicsProduct->setY(posY);
    mathematicalProduct->attachObservable(graphicsProduct);
    return graphicsProduct;
}

MathematicalProduct* BuildingFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    QRectF rect(posX,posY,50,50);
    QPolygonF poly(rect);
    Building* mathematicalBuildingProduct = new Building(poly);
    mathematicalBuildingProduct->setScale(px_to_meter);
    if (linkgraphic){
        GraphicsBuilding* graphicsBuildingProduct = new GraphicsBuilding(m_productmenu, m_scene);
        graphicsBuildingProduct->attachObserver(mathematicalBuildingProduct);
    }
    return mathematicalBuildingProduct;
}

MathematicalProduct* BuildingFactory::createMathematicalProduct(QPolygonF poly, bool linkgraphic){

    Building* mathematicalBuildingProduct = new Building(poly);
    mathematicalBuildingProduct->setScale(px_to_meter);
    if (linkgraphic){
        GraphicsBuilding* graphicsBuildingProduct = new GraphicsBuilding(poly,m_productmenu, m_scene);
        graphicsBuildingProduct->attachObserver(mathematicalBuildingProduct);
        mathematicalBuildingProduct->attachObservable(graphicsBuildingProduct);
    }
    return mathematicalBuildingProduct;
}
