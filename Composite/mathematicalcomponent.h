#ifndef MATHEMATICALCOMPONENT_H
#define MATHEMATICALCOMPONENT_H

#include "Product/SceneProduct.h"
#include <string>

class MathematicalComponent: public SceneProduct
{
public:
    virtual ~MathematicalComponent(){}
    virtual void setGraphicsComponent(GraphicsComponent* graphicsComponent){
        m_graphicsComponent = graphicsComponent;}
    std::string getType(){return m_type;}

protected:
    //GraphicsComponent* m_graphicsComponent = nullptr;
    std::string m_type;
};

#endif // MATHEMATICALCOMPONENT_H
