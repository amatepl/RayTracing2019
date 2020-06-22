#ifndef RAYFACTORY_H
#define RAYFACTORY_H

#include "Abstract_Factory/scenefactory.h"
#include "Product/RayProduct/graphicsrayproduct.h"
#include "Product/RayProduct/mathematicalrayproduct.h"

class RayFactory: public SceneFactory
{
public:
    RayFactory(bool visible);
    GraphicsComponent* createGraphicsComponent(int posX = 0, int posY = 0, QMenu* productmenu = 0 , QGraphicsScene* scene = 0 ) override;
    MathematicalComponent* createMathematicalComponent();

private:
    bool m_visibleRays;
};

#endif // RAYFACTORY_H
