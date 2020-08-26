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

//--------------------------------------------------------------------------------------------
//
//          Struct Data
//
//--------------------------------------------------------------------------------------------

/*!
 * \brief The Data struct
 * \struct Data
 *
 * Data is a struture used to share the channel data, known by the transmitter,
 * with the receiver in order to display it.
 *
 */
struct Data {
    std::map<double /*tau*/, std::complex<double> /*impulseResp*/>  impulseResp;
    std::map<double, std::complex<double>>                          dopplerSpctr;
    double                                                          pathLossP{0};
    std::complex<double>                                            interference{0};
    double                                                          angularSpred{0};
    std::vector<double>                                             u;
//    std::map<double /*u*/, std::complex<double> /* a(u) */>         angularDistr;
    std::vector<std::complex<double> /* a(u) */>                    angularDistr;
//    std::map<double /*u*/, double /* S(u) */>                       prxAngularSpctr;
    std::vector<double /* S(u) */>                                  prxAngularSpctr;
    double                                                          riceFactor{0};
};

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
    virtual void update(ProductObservable* productObservable,QLineF const movement) = 0;
    virtual void drawRays(ProductObservable *, bool){}
    virtual void attachObservable(ProductObservable* productObservable) = 0;
    virtual void compute(ProductObservable*) {};
    virtual Data *getChData(ProductObservable *) {return nullptr;};

    virtual std::map<double, std::complex<double>> receiverImpulse(ProductObservable *receiver)
    {
        return m_receiversImpulse[receiver];
    }

    virtual std::map<double, std::complex<double>> receiverDoppler(ProductObservable *receiver)
    {
        return m_dopplerSpectrum[receiver];
    }

    virtual double riceFactor(ProductObservable *) { return 0; }


    virtual std::vector<QLineF> linesForPathLoss(ProductObservable *) {std::vector<QLineF> vector(0); return vector;}

    virtual double computePathLossPower(ProductObservable* ) {return 0;}
    virtual std::complex<double> computeInterference(ProductObservable*,QLineF){return 0;}
//    virtual void updateCarPos(ProductObservable *productObservable)  = 0;

protected:
    std::map<const ProductObservable *, std::map<double /*tau*/, std::complex<double> /*impulseResp*/>>
        m_receiversImpulse;
    std::map<const ProductObservable *, std::map<double, std::complex<double>>> m_dopplerSpectrum;
};

#endif // PRODUCTOBSERVER_H
