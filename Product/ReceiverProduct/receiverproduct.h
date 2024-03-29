#ifndef RECEIVERPRODUCT_H
#define RECEIVERPRODUCT_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

#include <complex>
#include <vector>
#include <map>
#include <QPointF>
#include <QVector>

//--------------------------------------------------------------------------------------------
//
//          Definitions
//
//--------------------------------------------------------------------------------------------

using PrxAngularSpread = QVector<double>;
using PrxDopplerSpread = QVector<double>;
//--------------------------------------------------------------------------------------------
//
//          Class ReceiverProduct
//
//--------------------------------------------------------------------------------------------

class ReceiverProduct
{
public:
    virtual ~ReceiverProduct() {};

    virtual float getSpeed() = 0;
    virtual float getOrientation() = 0;
    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual bool getEnable() = 0;
    virtual std::complex<double> getEField() = 0;
    virtual std::complex<double> getVoltage() = 0;
    virtual double getPower() = 0;
    virtual double getDstnc() = 0;
    virtual double getDlySprd() = 0;
    virtual double getRiceFctr() = 0;
    virtual double getCoherenceDist() = 0;
    virtual double getCoherenceBw() = 0;
    virtual double getCoherenceTm() = 0;
    virtual double getAngSprd() = 0;
    virtual double getDopplerSprd() = 0;
    virtual int targetSNR() = 0;
    virtual int noiseFigure() = 0;
    virtual int interFerenceMargin() = 0;
    virtual void dialogDeleted() = 0;

    virtual void  setSpeed(float speed) = 0;
    virtual void setOrientation(float orientation) = 0;
    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setEnable(bool enable) = 0;
    virtual void setEField(std::complex<double> e) = 0;
    virtual void setPower(double p) = 0;
    virtual void setTargetSNR(int target) = 0;
    virtual void setNoiseFigure(int figure) = 0;
    virtual void setInterferecenceMargin(int interference) = 0;

    // Physical Result and parameters

    // 1. Impulse and TDL Results:
    virtual double maxVoltage() {return max_voltage;}
    virtual double maxVoltageTDL() {return max_voltage_tdl;}
    virtual QVector<double> impulse(){return h;}
    virtual QVector<double> impulseTDL(){return h_tdl;}
    virtual QVector<double> impulseTau() {return tau;}
    virtual QVector<double> impulseTauTDL() {return tau_tdl;}

    // 2. Frequency Response
    virtual std::vector<double> fqResp() const = 0;
    virtual std::vector<double> fq() const = 0;

    // 4. Cell Range Results:
    virtual unsigned long frequency() {return m_transmitterfrequency;}
    virtual unsigned long bandwidth() {return m_transmitterbandwidth;}
    virtual void setFrequency(unsigned long frequency){m_transmitterfrequency = frequency;}
    virtual void setBandwidth(unsigned long bandwidth){m_transmitterbandwidth = bandwidth;}

    // 5. Doppler
    virtual QVector<double> prxDopplerSpread(){return pds;}
//    virtual std::vector<double> prxDopplerSpctr() const = 0;
    virtual QVector<double> dopplerDistr(){return doppler_distr;}
    double dopplerSpread(){return doppler_spread;}
    QVector<double> getw() {return w;}

    virtual std::vector<double> getDoppler() = 0;
    virtual std::vector<double> getOmega() = 0;

    // 6. Spatial correlation
    virtual QVector<double> prxAngularSpread(){return pas;}
//    virtual std::vector<double> prxAngularSpctr() const = 0;

    virtual QVector<double> angularDistr(){return angular_distr;}
//    virtual std::vector<double> angularDistr() const = 0;
//    double angularSpread(){return angular_spread;}
    QVector<double> getu() {return u;}
    virtual std::vector<double> spaceCrltn() = 0;
    virtual std::vector<double> deltaZ() = 0;

    // 7. Time correlation
    virtual std::vector<double> timeCrltn() const = 0;
    virtual std::vector<double> timeCrltnT() const = 0;

    // 8. PDP
    virtual std::vector<double> getPDP() = 0;

    virtual void newProperties() = 0;

protected:

    // 2. Impulse and TDL vVariables
    QVector<double> h,h_tdl,tau, tau_tdl;
    double max_voltage, max_voltage_tdl;

    // 4. Doppler
    PrxDopplerSpread pds;
    QVector<double> doppler_distr;
    double doppler_spread {0};
    QVector<double> w;

    // 5. Spatial correlation
    PrxAngularSpread pas;
    QVector<double> angular_distr;
//    double angular_spread {0};
    QVector <double> u;

    unsigned long m_transmitterfrequency;
    unsigned long m_transmitterbandwidth;

};
#endif // RECEIVERPRODUCT_H
