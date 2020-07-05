#ifndef RECEIVERPRODUCT_H
#define RECEIVERPRODUCT_H

#include <complex>
#include <vector>

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
    std::vector<double> rayLength() {return m_raylength;}
    std::vector<double> attenuation() {return m_attenuation;}
    unsigned long frequency() {return m_transmitterfrequency;}
    unsigned long bandwidth() {return m_transmitterbandwidth;}
    void setAttenuation(std::vector<double> attenuation){
        m_attenuation.erase(m_attenuation.begin(),m_attenuation.end());
        m_attenuation = attenuation;
    }

    void setRayLength(std::vector<double> raylength){
        m_raylength.erase(m_raylength.begin(),m_raylength.end());
        m_raylength = raylength;
    }
    void setFrequency(unsigned long frequency){m_transmitterfrequency = frequency;}
    void setBandwidth(unsigned long bandwidth){m_transmitterbandwidth = bandwidth;}

    virtual void newProperties() = 0;

protected:
    std::vector<double> m_attenuation;
    std::vector<double> m_raylength;
    unsigned long m_transmitterfrequency;
    unsigned long m_transmitterbandwidth;
};
#endif // RECEIVERPRODUCT_H
