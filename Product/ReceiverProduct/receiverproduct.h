#ifndef RECEIVERPRODUCT_H
#define RECEIVERPRODUCT_H

#include <complex>
#include <vector>
#include <map>
#include <QPointF>
#include <QVector>

class ReceiverProduct
{
public:
    virtual ~ReceiverProduct() {}

    virtual float getSpeed() = 0;
    virtual float getOrientation() = 0;
    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual bool getEnable() = 0;
    virtual std::complex<double> getEField() = 0;
    virtual double getPower() = 0;
    virtual int targetSNR() = 0;
    virtual int noiseFigure() = 0;
    virtual int interFerenceMargin() = 0;

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
    // 1. Path Loss Results:
    virtual QVector<double> powerPathLoss() {return Prx;}
    virtual QVector<double> distancePathLoss() {return D;}
    virtual QVector<double> linearPathLoss() {return path_loss;}
    virtual QVector<double> friisLoss() {return friis_loss;}
    virtual QVector<double> powerPathLossModel() {return Prx_model;}
    virtual QVector<double> distancePathLossModel() {return D_model;}
    virtual QVector<double> linearPathLossModel() {return path_loss_model;}
    virtual double pathLossExponent() {return m/10;}
    virtual double fadingVariability() {return fading_variability;}
    virtual double minPower() {return min_prx;}

    // 2. Impulse and TDL Results:
    virtual QVector<double> impulse(){return h;}
    virtual QVector<double> impulseTDL(){return h_tdl;}
    virtual QVector<double> impulseTau() {return tau;}
    virtual QVector<double> impulseTauTDL() {return tau_tdl;}

    // 3. Cell Range Results:
    virtual QVector<double> probabilityConnection() {return probability;}
    virtual QVector<double> cellRangeConnection() {return cell_range;}
    virtual unsigned long frequency() {return m_transmitterfrequency;}
    virtual unsigned long bandwidth() {return m_transmitterbandwidth;}
    virtual void setFrequency(unsigned long frequency){m_transmitterfrequency = frequency;}
    virtual void setBandwidth(unsigned long bandwidth){m_transmitterbandwidth = bandwidth;}

    // 4. Doppler
    virtual QVector<double> getDoppler() {return doppler;}
    virtual QVector<double> getOmega() {return omega;}

    virtual void newProperties() = 0;

protected:
    // 1. Path Loss Variables
    QVector<double> Prx, path_loss, friis_loss, D;
    QVector<double> Prx_model, path_loss_model, D_model;
    double m,b,r,fading_variability, min_prx; //Path loss slope and intercept and regression coefficient

    // 2. Impulse and TDL vVariables
    QVector<double> h,h_tdl,tau, tau_tdl;

    // 3. Cell Range
    QVector<double> cell_range, probability;

    // 4. Doppler
    QVector<double> omega;
    QVector<double> doppler;

    unsigned long m_transmitterfrequency;
    unsigned long m_transmitterbandwidth;

};
#endif // RECEIVERPRODUCT_H
