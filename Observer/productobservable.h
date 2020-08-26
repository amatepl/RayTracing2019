#ifndef PRODUCTOBSERVABLE_H
#define PRODUCTOBSERVABLE_H

#include <vector>
#include <complex>

#include "Observer/productobserver.h"


class ProductObservable{
public:
    virtual void attachObserver(ProductObserver* productObserver) = 0;
    virtual void detachObservers() = 0;
    virtual void notify() =0;
    virtual void notify(double &power, std::vector<double>* powers, std::complex <double> &EMfiled)=0;
    virtual void answer(ProductObserver* observer, double frequency, double bandwidth,
                        double &power, std::complex <double> &EMfiled) = 0;
    virtual const QPointF * getPos() const =0;

    void eraseObservers()
    {
        for (unsigned i = 0; i < m_observers.size(); i++) {
            delete m_observers.at(i);
        }
        m_observers.erase(m_observers.begin(), m_observers.end());
        m_observers.shrink_to_fit();
    }

    //virtual float getSpeed(){return m_speed;}
    //virtual float getOrientation(){return m_orientation;}

protected:

    QPointF *m_pos;
    std::vector<ProductObserver *> m_observers;
    //float m_speed;
    //float m_orientation;
};

#endif // PRODUCTOBSERVABLE_H
