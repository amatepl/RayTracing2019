#include "rayfactory.h"

RayFactory::RayFactory(bool visible, QGraphicsScene *scene,const float scale)
{
    m_visibleRays = visible;
    m_scene = scene;
    px_to_meter = scale;
}

MathematicalRayProduct* RayFactory::createRay(const QPointF &p1, const QPointF &p2, double Tetai, int indWall){
    MathematicalRayProduct* mathematicalComponent;
    if(m_visibleRays){

        //cout<<"Ray created in factory"<<endl;
        mathematicalComponent = new MathematicalRayProduct(p1, p2, Tetai, indWall);
        mathematicalComponent->Line::setScale(px_to_meter);
        GraphicsRayProduct* graphicsComponent = new GraphicsRayProduct(p1, p2,m_scene);
        mathematicalComponent->attachObservable(graphicsComponent);
    }
    else{
        mathematicalComponent = new MathematicalRayProduct(p1, p2, Tetai, indWall);
        mathematicalComponent->Line::setScale(px_to_meter);
    }
    return mathematicalComponent;
}
