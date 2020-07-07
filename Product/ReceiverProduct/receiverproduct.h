#ifndef RECEIVERPRODUCT_H
#define RECEIVERPRODUCT_H

#include <complex>
#include <vector>
#include <map>
#include <QPointF>

class ReceiverProduct
{
public:
    virtual ~ReceiverProduct() {}

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual bool getEnable() = 0;
    virtual std::complex<double> getEField() = 0;
    virtual double getPower() = 0;

    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setEnable(bool enable) = 0;
    virtual void setEField(std::complex<double> e) = 0;
    virtual void setPower(double p) = 0;

    // Physical Result and parameters
    std::map<std::vector<double>,double> impulseRayLength() {return m_raylength;}
    std::map<std::vector<double>,double> impulseAttenuation() {return m_attenuation;}
    std::map<double,double> pathLoss(){return m_pathloss;}
    unsigned long frequency() {return m_transmitterfrequency;}
    unsigned long bandwidth() {return m_transmitterbandwidth;}
    void setImpulseRayLength(std::map<std::vector<double>,double> raylength){m_raylength = raylength;}
    void setImpulseAttenuation(std::map<std::vector<double>,double> attenuation){m_attenuation = attenuation;}
    void setPathLoss(std::map<double,double> pathloss) {m_pathloss = pathloss;}
    void setFrequency(unsigned long frequency){m_transmitterfrequency = frequency;}
    void setBandwidth(unsigned long bandwidth){m_transmitterbandwidth = bandwidth;}

    virtual void newProperties() = 0;

protected:
    std::map<std::vector<double>,double> m_raylength;
    std::map<std::vector<double>,double> m_attenuation;
    std::map<double,double> m_pathloss;

    unsigned long m_transmitterfrequency;
    unsigned long m_transmitterbandwidth;
};
#endif // RECEIVERPRODUCT_H
