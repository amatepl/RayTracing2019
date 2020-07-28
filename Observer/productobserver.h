#ifndef PRODUCTOBSERVER_H
#define PRODUCTOBSERVER_H

#include <QPointF>
#include <QLineF>
#include <complex>
#include <vector>

class ProductObservable;

class ProductObserver{

public:
    virtual ~ProductObserver(){}
    //virtual void update(const QPointF *pos,const float speed, const float direction) = 0;
    virtual void update(ProductObservable* productObservable,QLineF const movement) = 0;
    virtual void compute(ProductObservable*) {};
    virtual std::vector<QPointF> pointsForPathLoss(ProductObservable *) {std::vector<QPointF> vector(0); return vector;}
    virtual double computePathLossPower(ProductObservable* ) {return 0;}
    virtual std::complex<double> computeInterference(ProductObservable*){return 0;}
    virtual void drawRays(ProductObservable*, bool){}
    virtual void attachObservable(ProductObservable* productObservable)=0;
};

#endif // PRODUCTOBSERVER_H
