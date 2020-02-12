#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QString>

class GraphicsComponent{
public:
    enum Type{TransmitterProduct,ReceiverProduct};

    virtual ~GraphicsComponent() {}

    virtual void draw() = 0;
    virtual int getType() {return 0;}
    virtual bool graphicsSelected() {return false;}

    virtual void add(GraphicsComponent*) {}
    virtual void remove(GraphicsComponent*){}
    virtual unsigned long long getSize() {return 0;}
    virtual GraphicsComponent* getGraphicsComponent(unsigned long long){return nullptr;}
    virtual void setGraphicComponent(unsigned long long,GraphicsComponent*){}
};

#endif // GRAPHICSCOMPONENT_H
