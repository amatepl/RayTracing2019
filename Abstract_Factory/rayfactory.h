#ifndef RAYFACTORY_H
#define RAYFACTORY_H

//#include "Abstract_Factory/scenefactory.h"
#include "Product/RayProduct/graphicsrayproduct.h"
#include "Product/RayProduct/mathematicalrayproduct.h"

class RayFactory
{
public:
    RayFactory(bool visible);
    MathematicalRayProduct* createRay(const QPointF &p1, const QPointF &p2);

private:
    bool m_visibleRays;
};

#endif // RAYFACTORY_H
