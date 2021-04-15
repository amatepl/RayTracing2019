#ifndef SCENEPRODUCT_H
#define SCENEPRODUCT_H

//#include "mathematicalproduct.h"
//#include "graphicsproduct.h"

class MathematicalProduct;
class GraphicsProduct;

class SceneProduct{

public:
    virtual ~SceneProduct() {}
    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual float getOrientation() = 0;
    virtual void setPosX(int posX) = 0 ;
    virtual void setPosY(int posY) = 0 ;

    virtual void setOrientation(float theta) = 0;
    virtual MathematicalProduct* toMathematicalProduct() = 0;
    virtual GraphicsProduct* toGraphicsComponent(){return m_graphicsComponent;};

protected:
    GraphicsProduct* m_graphicsComponent;
};

#endif // SCENEPRODUCT_H
