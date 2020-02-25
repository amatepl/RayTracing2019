#ifndef CARPRODUCT_H
#define CARPRODUCT_H
#include <QPointF>

class CarProduct{
public:
    virtual ~CarProduct() {}

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual double getSpeed() = 0;
    virtual double getOrientation() = 0;

    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setOrientation(double orientation) = 0;
    virtual void setSpeed(double) = 0;
};
#endif // CARPRODUCT_H
