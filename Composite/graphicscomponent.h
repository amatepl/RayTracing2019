#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

//#include <QString>
#include "Product/sceneproduct.h"
//#include "Composite/MathematicalComponent.h"

class QPixmap;

class GraphicsComponent: public SceneProduct
{
public:
    enum Type{TransmitterProduct,ReceiverProduct,BuildingProduct,TreeProduct,CarProduct};

    virtual ~GraphicsComponent() {}

    virtual void draw() = 0;
    virtual int getType() {return 0;}
    virtual bool graphicsSelected() {return false;}
    //virtual QPixmap getImage() = 0;

    virtual void add(GraphicsComponent*) {}
    virtual void remove(GraphicsComponent*){}
    virtual unsigned long long getSize() {return 0;}
    virtual GraphicsComponent* getGraphicsComponent(unsigned long long){return nullptr;}
    virtual void setGraphicComponent(unsigned long long,GraphicsComponent*){}
    virtual void setMathematicalComponent(MathematicalComponent* mathematicalComponent) = 0;

};

#endif // GRAPHICSCOMPONENT_H
