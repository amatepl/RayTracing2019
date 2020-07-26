#ifndef PRODUCTOBSERVER_H
#define PRODUCTOBSERVER_H

#include <QPointF>
#include <QLineF>
#include <complex>

class ProductObservable;

class ProductObserver{

public:
    virtual ~ProductObserver(){}
    //virtual void update(const QPointF *pos,const float speed, const float direction) = 0;
    virtual void update(ProductObservable *productObservable, const QLineF movement) = 0;
//    virtual void updateCarPos(ProductObservable *productObservable)  = 0;
    virtual void compute(ProductObservable *productObservable) {};
    virtual void drawRays(ProductObservable *productObservable, bool draw){}
    virtual void attachObservable(ProductObservable* productObservable) = 0;

    virtual std::complex<double> computeInterference(ProductObservable*){return 0;}

};

#endif // PRODUCTOBSERVER_H
