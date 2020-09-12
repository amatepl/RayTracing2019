#ifndef ABSTRACTRAYFACTORY_H
#define ABSTRACTRAYFACTORY_H

class MathematicalRayProduct;
class QPointF;

class AbstractRayFactory{
public:
    virtual MathematicalRayProduct* createRay(const QPointF &p1, const QPointF &p2, const double Tetai=0, const double epsilonWall = 5) = 0;
};

#endif // ABSTRACTRAYFACTORY_H
