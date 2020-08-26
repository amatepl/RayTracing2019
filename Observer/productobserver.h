#ifndef PRODUCTOBSERVER_H
#define PRODUCTOBSERVER_H

#include <QPointF>
#include <QLineF>
#include <complex>
#include <vector>
#include <map>

class ProductObservable;

class ProductObserver{

public:
    virtual ~ProductObserver(){}
    //virtual void update(const QPointF *pos,const float speed, const float direction) = 0;
    virtual void update(ProductObservable* productObservable,QLineF const movement) = 0;
    virtual void drawRays(ProductObservable *, bool){}
    virtual void attachObservable(ProductObservable* productObservable) = 0;
    virtual void compute(ProductObservable*) {};

    virtual std::map<double,std::complex<double>> receiverImpulse(ProductObservable *receiver) {return m_receiversImpulse[receiver];}
    virtual std::map<double,std::complex<double>> receiverDoppler(ProductObservable *receiver) {return m_dopplerSpectrum[receiver];}
    virtual double riceFactor(ProductObservable*) {return 0;}
    virtual std::vector<QLineF> linesForPathLoss(ProductObservable *) {std::vector<QLineF> vector(0); return vector;}
    virtual double computePathLossPower(ProductObservable* ) {return 0;}
    virtual std::complex<double> computeInterference(ProductObservable*,QLineF){return 0;}
//    virtual void updateCarPos(ProductObservable *productObservable)  = 0;

protected:
    std::map<ProductObservable *,std::map<double,std::complex<double>>> m_receiversImpulse;
    std::map<ProductObservable *,std::map<double,std::complex<double>>> m_dopplerSpectrum;
};

#endif // PRODUCTOBSERVER_H
