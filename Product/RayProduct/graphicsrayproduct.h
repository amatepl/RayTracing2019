#ifndef GRAPHICSRAYPRODUCT_H
#define GRAPHICSRAYPRODUCT_H

#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

#include "Product/graphicsproduct.h"

class GraphicsRayProduct: public GraphicsProduct, public QGraphicsLineItem
{
public:
    GraphicsRayProduct(const QPointF &p1, const QPointF &p2/*, QGraphicsScene *scene*/);

    void draw() override;
    void setMathematicalComponent(MathematicalProduct* mathematicalComponent);
    MathematicalProduct* toMathematicalComponent();
    void setPosX(int posX);
    void setPosY(int posY);
    int getPosX();
    int getPosY();

private:
    MathematicalProduct* m_mathematicalComponent;
};

#endif // GRAPHICSRAYPRODUCT_H
