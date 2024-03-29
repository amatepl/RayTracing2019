#ifndef RAYFACTORY_H
#define RAYFACTORY_H

//#include "Abstract_Factory/scenefactory.h"
#include "Product/RayProduct/graphicsray.h"
#include "Product/RayProduct/ray.h"

#include "Abstract_Factory/abstractrayfactory.h"

class RayFactory: public AbstractRayFactory
{
public:
    RayFactory(bool visible,QGraphicsScene *scene,const float scale);
    unique_ptr<Ray> createRay(const QPointF &p1, const QPointF &p2, const double Tetai=0, const double epsilonWall = 5) override;

private:
    bool m_visibleRays;
    QGraphicsScene *m_scene;
    float px_to_meter;
};

#endif // RAYFACTORY_H
