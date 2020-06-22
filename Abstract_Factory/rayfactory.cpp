#include "rayfactory.h"

RayFactory::RayFactory(bool visible)
{
    m_visibleRays = visible;
}

GraphicsComponent* RayFactory::createGraphicsComponent(int posX, int posY, QMenu *productmenu, QGraphicsScene *scene){

}

MathematicalComponent* RayFactory::createMathematicalComponent(){
    MathematicalRayProduct* mathematicalComponent;
    if(m_visibleRays){
        //MathematicalRayProduct* mathematicalComponent = new MathematicalRayProduct();
        //GraphicsRayProduct* graphicsComponent = new GraphicsRayProduct();
    }
    else{
        //MathematicalRayProduct* mathematicalComponent = new MathematicalRayProduct();
    }
    return mathematicalComponent;
}
