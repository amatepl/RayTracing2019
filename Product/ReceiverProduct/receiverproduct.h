#ifndef RECEIVERPRODUCT_H
#define RECEIVERPRODUCT_H

#include "Product/SceneProduct.h"

class ReceiverProduct/*: public SceneProduct*/
{
public:
    virtual ~ReceiverProduct() {}

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual unsigned long getFrequency()= 0;
    virtual double getPower() = 0;

//    virtual void setPosX(int posX) = 0;
//    virtual void setPosY(int posY) = 0;
    virtual void setFrequency(unsigned long frequency) = 0;
};
#endif // RECEIVERPRODUCT_H
