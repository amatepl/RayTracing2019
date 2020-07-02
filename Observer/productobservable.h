#ifndef PRODUCTOBSERVABLE_H
#define PRODUCTOBSERVABLE_H

#include <vector>
#include <complex>

#include "Observer/productobserver.h"


class ProductObservable{
public:
    virtual void attachObserver(ProductObserver* productObserver) = 0;
    virtual void notify() =0;
    virtual void notify(double &power, std::vector<double>* powers, std::complex <double> &EMfiled)=0;
    virtual void answer(ProductObserver* observer,double &power, std::vector<double>* powers, std::complex <double> &EMfiled) = 0;
    virtual QPointF* getPos() =0;
    virtual float getSpeed(){return m_speed;}
    virtual float getOrientation(){return m_orientation;}

protected:

    QPointF *m_pos;
    float m_speed;
    float m_orientation;
};

#endif // PRODUCTOBSERVABLE_H
