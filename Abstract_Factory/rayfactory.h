#ifndef RAYFACTORY_H
#define RAYFACTORY_H

//#include "Abstract_Factory/scenefactory.h"
#include "Product/RayProduct/graphicsrayproduct.h"
#include "Product/RayProduct/mathematicalrayproduct.h"

#include "Abstract_Factory/abstractrayfactory.h"

class RayFactory: public AbstractRayFactory
{
public:
    RayFactory(bool visible);
    MathematicalRayProduct* createRay(const QPointF &p1, const QPointF &p2,double Tetai=0,int indWall=0) override;

private:
    bool m_visibleRays;
};

#endif // RAYFACTORY_H
