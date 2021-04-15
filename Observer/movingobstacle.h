#ifndef MOVINGOBSTACLE_H
#define MOVINGOBSTACLE_H

#include <vector>

class ProductObserver;

class MovingObstacle
{

public:
    virtual void notify() = 0;
    virtual void attachObsever(ProductObserver *) = 0;

private:
    std::vector<ProductObserver *> m_observers;

};

#endif // MOVINGOBSTACLE_H
