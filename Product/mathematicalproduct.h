#ifndef MATHEMATICALPRODUCT_H
#define MATHEMATICALPRODUCT_H

#include <QGraphicsItem>

class MathematicalProduct
{
public:
    virtual ~MathematicalProduct(){}
    virtual void update(QGraphicsItem* graphic) = 0;
};

#endif // MATHEMATICALPRODUCT_H
