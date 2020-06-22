#ifndef GRAPHICSRAYPRODUCT_H
#define GRAPHICSRAYPRODUCT_H

#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

#include "Composite/graphicscomponent.h"

class GraphicsRayProduct: public GraphicsComponent, public QGraphicsLineItem
{
public:
    GraphicsRayProduct(const QPointF &p1, const QPointF &p2, QGraphicsScene *scene);

    void draw() override;
    void setMathematicalComponent(MathematicalComponent* mathematicalComponent) override;
    MathematicalComponent* toMathematicalComponent() override;

private:
    MathematicalComponent* m_mathematicalComponent;
};

#endif // GRAPHICSRAYPRODUCT_H
