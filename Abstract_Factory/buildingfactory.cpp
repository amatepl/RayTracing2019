#include "buildingfactory.h"

BuildingFactory::BuildingFactory()
{

}

GraphicsComponent* BuildingFactory::createGraphicsComponent(int posX, int posY, QMenu* productmenu,QGraphicsScene* scene){
    GraphicsBuildingProduct* graphicsProduct = new GraphicsBuildingProduct(posX,posY,true,productmenu, scene);
    MathematicalBuildingProduct* mathematicalProduct = new MathematicalBuildingProduct(graphicsProduct);
    graphicsProduct->setMathematicalComponent(mathematicalProduct);
    return graphicsProduct;
}
