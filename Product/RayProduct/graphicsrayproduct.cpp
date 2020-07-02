#include "graphicsrayproduct.h"

GraphicsRayProduct::GraphicsRayProduct(const QPointF &p1, const QPointF &p2, QGraphicsScene *scene):
    QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y()),m_scene(scene)
{

}

GraphicsRayProduct::~GraphicsRayProduct(){
    //cout<<"Graphics ray deleted"<<endl;

}

void GraphicsRayProduct::draw(){
    m_scene->addItem(this);
}

void GraphicsRayProduct::erase(){
    m_scene->removeItem(this);
}
void GraphicsRayProduct::setMathematicalComponent(MathematicalProduct *mathematicalComponent){
    m_mathematicalComponent = mathematicalComponent;
}

MathematicalProduct* GraphicsRayProduct::toMathematicalComponent(){
    return m_mathematicalComponent;
}

