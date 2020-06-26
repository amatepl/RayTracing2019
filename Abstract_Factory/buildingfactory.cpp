#include "buildingfactory.h"

BuildingFactory::BuildingFactory(QMenu *productmenu, QGraphicsScene* scene)
{
    m_productmenu = productmenu;
    m_scene = scene;
}

GraphicsProduct* BuildingFactory::createGraphicsProduct(int posX, int posY){
    GraphicsBuildingProduct* graphicsProduct = new GraphicsBuildingProduct(m_productmenu,m_scene);
    QVector<QPointF> points = graphicsProduct->polygon();
    QVector<QPointF> p;
    cout<<"Polygone: -------------"<<endl;
    for(int i =0;i< points.size();i++){
        p.push_back(points.at(i)+QPointF(posX,posY));

        cout<<p.at(i).x()<<", "<<p.at(i).y()<<endl;

    }

    cout<<"------------------"<<endl;

    MathematicalBuildingProduct* mathematicalProduct = new MathematicalBuildingProduct(points);
    graphicsProduct->attachObserver(mathematicalProduct);
    graphicsProduct->setX(posX);
    graphicsProduct->setY(posY);
    mathematicalProduct->attachObservable(graphicsProduct);
    return graphicsProduct;
}

MathematicalProduct* BuildingFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    QRectF rect(posX,posY,50,50);
    QPolygonF poly(rect);
    MathematicalBuildingProduct* mathematicalBuildingProduct = new MathematicalBuildingProduct(poly);
    if (linkgraphic){
        GraphicsBuildingProduct* graphicsBuildingProduct = new GraphicsBuildingProduct(m_productmenu, m_scene);
        graphicsBuildingProduct->attachObserver(mathematicalBuildingProduct);
    }
    return mathematicalBuildingProduct;
}
