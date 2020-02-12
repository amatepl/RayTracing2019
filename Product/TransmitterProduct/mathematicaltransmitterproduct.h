#ifndef MATHEMATICALTRANSMITTERPRODUCT_H
#define MATHEMATICALTRANSMITTERPRODUCT_H

#include "math.h"
#include "complex.h"
#include <iostream>

#include "transmitterproduct.h"

using namespace std;

class MathematicalTransmitterProduct : public TransmitterProduct
{
public:
    MathematicalTransmitterProduct(int posx,int posy,double orientation,double power,unsigned long frequency);
    ~MathematicalTransmitterProduct() override;

    static double computeGain(double theta,double phi, double frequency,int row,int column,double antennaDistance);

    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    unsigned long getFrequency() override;
    double getPower() override;
    int getRow() override;
    int getColumn() override;
    double getAntennaDistance() override;
    int getModel() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setPower(double power) override;
    void setFrequency(unsigned long frequency) override;
    void setRow(int row) override;
    void setColumn(int column) override;
    void setAntennaDistance(double distance) override;
    virtual void setModel(Model model) override;

private:
    int m_posx,m_posy;
    double m_orientation, m_power;
    unsigned long m_frequency;

};

#endif // MATHEMATICALTRANSMITTERPRODUCT_H
