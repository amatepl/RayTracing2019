#ifndef GRAPHICSCOMPOSITE_H
#define GRAPHICSCOMPOSITE_H

#include <vector>
#include <iostream>
#include <QGraphicsScene>

#include "graphicscomponent.h"

using namespace std;

class GraphicsComposite : public GraphicsComponent
{
public:
    GraphicsComposite();
    ~GraphicsComposite() override;

    void draw() override;
    void add(GraphicsComponent *graphicscomponent) override;
    void remove(GraphicsComponent *graphicscomponent) override;
    unsigned long long getSize() override;
    GraphicsComponent * getGraphicsComponent(unsigned long long id) override;
    void setGraphicComponent(unsigned long long,GraphicsComponent*) override;

private:
    vector<GraphicsComponent*> m_graphicscomponent;
    vector<GraphicsComponent*>::iterator m_graphicscomponentiterator;

};

#endif // GRAPHICSCOMPOSITE_H
