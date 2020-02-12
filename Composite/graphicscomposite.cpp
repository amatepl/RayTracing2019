#include "graphicscomposite.h"

GraphicsComposite::GraphicsComposite()
{
}

GraphicsComposite::~GraphicsComposite(){

}

void GraphicsComposite::draw(){
    for (unsigned long long i = 0; i < m_graphicscomponent.size(); i++){
        m_graphicscomponent.at(i)->draw();
    }
}

void GraphicsComposite::add(GraphicsComponent *graphicscomponent){
    m_graphicscomponent.push_back(graphicscomponent);
}

void GraphicsComposite::remove(GraphicsComponent *graphicscomponent){
    unsigned long long i = 0;
    for (m_graphicscomponentiterator = m_graphicscomponent.begin();
         m_graphicscomponentiterator != m_graphicscomponent.end();
         ++m_graphicscomponentiterator){
        if (m_graphicscomponent.at(i) == graphicscomponent){
            m_graphicscomponent.erase(m_graphicscomponentiterator);
        }
        i++;
    }
}

GraphicsComponent* GraphicsComposite::getGraphicsComponent(unsigned long long id){
    return m_graphicscomponent.at(id);
}

void GraphicsComposite::setGraphicComponent(unsigned long long id,GraphicsComponent* component){
    m_graphicscomponent.at(id) = component;
}

unsigned long long GraphicsComposite::getSize(){
    return m_graphicscomponent.size();
}
