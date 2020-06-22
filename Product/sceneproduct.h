#ifndef SCENEPRODUCT_H
#define SCENEPRODUCT_H

//#include "Composite/MathematicalComponent.h"
//#include "Composite/graphicscomponent.h"

class MathematicalComponent;
class GraphicsComponent;

class SceneProduct{

public:
    virtual ~SceneProduct() {}
    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual void setPosX(int posX) = 0 ;
    virtual void setPosY(int posY) = 0 ;
    virtual MathematicalComponent* toMathematicalComponent() = 0;
    //virtual GraphicsComponent* toGraphicsComponent() = 0;
};

#endif // SCENEPRODUCT_H
