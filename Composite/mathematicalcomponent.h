#ifndef MATHEMATICALCOMPONENT_H
#define MATHEMATICALCOMPONENT_H

#include "Product/SceneProduct.h"

class MathematicalComponent: public SceneProduct
{
public:
    virtual ~MathematicalComponent(){}
    virtual void setGraphicsComponent(GraphicsComponent* graphicsComponent){
        m_graphicsComponent = graphicsComponent;}

private:
    GraphicsComponent* m_graphicsComponent;
};

#endif // MATHEMATICALCOMPONENT_H
