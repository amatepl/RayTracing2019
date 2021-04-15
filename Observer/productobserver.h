#ifndef PRODUCTOBSERVER_H
#define PRODUCTOBSERVER_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

#include <QPointF>
#include <QLineF>
#include <complex>
#include <vector>
#include <map>

//--------------------------------------------------------------------------------------------
//
//          Global Variables
//
//--------------------------------------------------------------------------------------------

class ProductObservable;
struct Data;

//--------------------------------------------------------------------------------------------
//
//          Class ProductObserver
//
//--------------------------------------------------------------------------------------------

/*!
 * \brief The ProductObserver class
 */
class ProductObserver{

public:
    virtual ~ProductObserver(){}
    //virtual void update(const QPointF *pos,const float speed, const float direction) = 0;
    virtual Data *update(QPointF* productObservable,QLineF const movement) = 0;
    virtual void drawRays(QPointF *, bool){}
    virtual void attachObservable(QPointF* productObservable) = 0;
//    virtual void compute(ProductObservable*) {};
//    virtual Data *getChData(ProductObservable *) {return nullptr;};

//    virtual std::map<double, std::complex<double>> receiverImpulse(ProductObservable *receiver)
//    {
//        return m_receiversImpulse[receiver];
//    }

//    virtual std::map<double, std::complex<double>> receiverDoppler(ProductObservable *receiver)
//    {
//        return m_dopplerSpectrum[receiver];
//    }

//    virtual double riceFactor(ProductObservable *) { return 0; }
//    virtual std::vector<QPointF> pathLossPoints() const {std::vector<QPointF> points; return points;}
//    virtual double computePathLossPower(ProductObservable* ) {return 0;}
//    virtual std::complex<double> computeInterference(ProductObservable*,QLineF){return 0;}
//    virtual void updateCarPos(ProductObservable *productObservable)  = 0;

protected:
    std::map<const QPointF *, std::map<double /*tau*/, std::complex<double> /*impulseResp*/>>
        m_receiversImpulse;
    std::map<const QPointF *, std::map<double, std::complex<double>>> m_dopplerSpectrum;
};

#endif // PRODUCTOBSERVER_H
