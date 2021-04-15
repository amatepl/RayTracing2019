#ifndef GRAPHICSRAY_H
#define GRAPHICSRAY_H

#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <iostream>
#include <QException>

#include "Product/graphicsproduct.h"

using namespace std;

class GraphicsRay: public GraphicsProduct, public QGraphicsLineItem
{
public:
    GraphicsRay(const QPointF &p1, const QPointF &p2, QGraphicsScene *scene = nullptr);
    ~GraphicsRay();

    void draw() override;
    void erase() override;
    void setMathematicalComponent(MathematicalProduct* mathematicalComponent);
    MathematicalProduct* toMathematicalComponent();

private:
    MathematicalProduct* m_mathematicalComponent;
    QGraphicsScene *m_scene;
};

#endif // GRAPHICSRAY_H
