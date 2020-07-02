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
    GraphicsRayProduct(const QPointF &p1, const QPointF &p2, QGraphicsScene *scene = nullptr);
    ~GraphicsRayProduct();

    void draw() override;
    void erase() override;
    void setMathematicalComponent(MathematicalProduct* mathematicalComponent);
    MathematicalProduct* toMathematicalComponent();

private:
    MathematicalProduct* m_mathematicalComponent;
    QGraphicsScene *m_scene;
};

#endif // GRAPHICSRAYPRODUCT_H
