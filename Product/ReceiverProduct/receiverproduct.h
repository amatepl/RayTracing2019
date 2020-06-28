#ifndef RECEIVERPRODUCT_H
#define RECEIVERPRODUCT_H

class ReceiverProduct
{
public:
    virtual ~ReceiverProduct() {}

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual bool getEnable() = 0;
    virtual double getEField() = 0;
    virtual double getPower() = 0;

    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setEnable(bool enable) = 0;
    virtual void setEField(double e) = 0;
    virtual void setPower(double p) = 0;

    virtual void newProperties() = 0;
};
#endif // RECEIVERPRODUCT_H
