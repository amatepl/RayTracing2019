#include "rayfactory.h"

RayFactory::RayFactory(bool visible, QGraphicsScene *scene,const float scale)
{
    m_visibleRays = visible;
    m_scene = scene;
    px_to_meter = scale;
}

unique_ptr<Ray> RayFactory::createRay(const QPointF &p1, const QPointF &p2, const double Tetai, const double epsilonWall){
//    unique_ptr<Ray> mathematicalComponent;
    if(m_visibleRays){

        //cout<<"Ray created in factory"<<endl;
//        mathematicalComponent.swap(new Ray(p1, p2, Tetai, epsilonWall));
        unique_ptr<Ray> mathematicalComponent(new Ray(p1, p2, Tetai, epsilonWall));
        mathematicalComponent->Line::setScale(px_to_meter);
        GraphicsRay* graphicsComponent = new GraphicsRay(p1, p2, m_scene);
        mathematicalComponent->attachObservable(graphicsComponent);
        return mathematicalComponent;
    }
    else{
        unique_ptr<Ray> mathematicalComponent(new Ray(p1, p2, Tetai));
//        mathematicalComponent = new Ray(p1, p2, Tetai);
        mathematicalComponent->Line::setScale(px_to_meter);
        return mathematicalComponent;
    }
//    return mathematicalComponent;
}
