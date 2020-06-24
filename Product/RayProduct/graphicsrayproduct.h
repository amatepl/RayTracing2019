#ifndef GRAPHICSRAYPRODUCT_H
#define GRAPHICSRAYPRODUCT_H

#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <iostream>

#include "Product/graphicsproduct.h"

using namespace std;

class GraphicsRayProduct: public GraphicsProduct, public QGraphicsLineItem
{
public:
    GraphicsRayProduct(const QPointF &p1, const QPointF &p2/*, QGraphicsScene *scene*/);
    ~GraphicsRayProduct();

    void draw() override;
    void setMathematicalComponent(MathematicalProduct* mathematicalComponent);
    MathematicalProduct* toMathematicalComponent();

private:
    MathematicalProduct* m_mathematicalComponent;
};

#endif // GRAPHICSRAYPRODUCT_H
