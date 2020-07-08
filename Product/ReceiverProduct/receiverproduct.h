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

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual bool getEnable() = 0;
    virtual std::complex<double> getEField() = 0;
    virtual double getPower() = 0;
    virtual int targetSNR() = 0;
    virtual int noiseFigure() = 0;
    virtual int interFerenceMargin() = 0;

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
    QVector<double> powerPathLoss() {return Prx;}
    QVector<double> distancePathLoss() {return D;}
    QVector<double> linearPathLoss() {return path_loss;}
    QVector<double> powerPathLossModel() {return Prx_model;}
    QVector<double> distancePathLossModel() {return D_model;}
    QVector<double> linearPathLossModel() {return path_loss_model;}
    double pathLossExponent() {return m/10;}
    double fadingVariability() {return fading_variability;}
    double minPower() {return min_prx;}

    std::map<std::vector<double>,double> impulseRayLength() {return m_raylength;}
    std::map<std::vector<double>,double> impulseAttenuation() {return m_attenuation;}
    unsigned long frequency() {return m_transmitterfrequency;}
    unsigned long bandwidth() {return m_transmitterbandwidth;}
    void setImpulseRayLength(std::map<std::vector<double>,double> raylength){m_raylength = raylength;}
    void setImpulseAttenuation(std::map<std::vector<double>,double> attenuation){m_attenuation = attenuation;}
    void setFrequency(unsigned long frequency){m_transmitterfrequency = frequency;}
    void setBandwidth(unsigned long bandwidth){m_transmitterbandwidth = bandwidth;}

    virtual void newProperties() = 0;

protected:
    // 1. Path Loss Variables
    QVector<double> Prx, path_loss, D;
    QVector<double> Prx_model, path_loss_model, D_model;
    double m,b,r,fading_variability, min_prx; //Path loss slope and intercept and regression coefficient

    std::map<std::vector<double>,double> m_raylength;
    std::map<std::vector<double>,double> m_attenuation;

    unsigned long m_transmitterfrequency;
    unsigned long m_transmitterbandwidth;

};
#endif // RECEIVERPRODUCT_H
