#include "graphicsrayproduct.h"

GraphicsRayProduct::GraphicsRayProduct(const QPointF &p1, const QPointF &p2):
    QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y())
{

}

GraphicsRayProduct::~GraphicsRayProduct(){
    //cout<<"Graphics ray deleted"<<endl;

}

void GraphicsRayProduct::draw(){}

void GraphicsRayProduct::setMathematicalComponent(MathematicalProduct *mathematicalComponent){
    m_mathematicalComponent = mathematicalComponent;
}

MathematicalProduct* GraphicsRayProduct::toMathematicalComponent(){
    return m_mathematicalComponent;
}

