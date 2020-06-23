#include "rayfactory.h"

RayFactory::RayFactory(bool visible)
{
    m_visibleRays = visible;
}

MathematicalRayProduct* RayFactory::createRay(const QPointF &p1, const QPointF &p2){
    MathematicalRayProduct* mathematicalComponent;
    if(m_visibleRays){
        mathematicalComponent = new MathematicalRayProduct(p1, p2);
        GraphicsRayProduct* graphicsComponent = new GraphicsRayProduct(p1, p2);
        mathematicalComponent->setGraphicsComponent(graphicsComponent);

    }
    else{
        mathematicalComponent = new MathematicalRayProduct();
    }
    return mathematicalComponent;
}
