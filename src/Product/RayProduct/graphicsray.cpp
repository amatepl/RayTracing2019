#include "graphicsray.h"

GraphicsRay::GraphicsRay(const QPointF &p1, const QPointF &p2, QGraphicsScene *scene):
    QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y()),m_scene(scene)
{

}

GraphicsRay::~GraphicsRay(){
    //cout << "Graphics Ray Product Deleted." << endl;

}

void GraphicsRay::draw(){
    try {
        m_scene->addItem(this);
    } catch (const QException &e) {

    }

}

void GraphicsRay::erase(){
    m_scene->removeItem(this);
}
void GraphicsRay::setMathematicalComponent(MathematicalProduct *mathematicalComponent){
    m_mathematicalComponent = mathematicalComponent;
}

MathematicalProduct* GraphicsRay::toMathematicalComponent(){
    return m_mathematicalComponent;
}

