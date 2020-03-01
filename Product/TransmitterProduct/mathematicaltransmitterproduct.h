#ifndef MATHEMATICALTRANSMITTERPRODUCT_H
#define MATHEMATICALTRANSMITTERPRODUCT_H

#include "math.h"
#include "complex.h"
#include <iostream>
#include <QPointF>

#include "transmitterproduct.h"
#include "Abstract_Factory/mathematicalfactory.h"

class MathematicalFactory;

using namespace std;

class MathematicalTransmitterProduct : public TransmitterProduct, public QPointF
{
public:
    MathematicalTransmitterProduct(TransmitterProduct* graphic, MathematicalFactory *factory);
    ~MathematicalTransmitterProduct() override;

    void newProperties();

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

    TransmitterProduct* getTransmitterProduct();

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setPower(double power) override;
    void setFrequency(unsigned long frequency) override;
    void setRow(int row) override;
    void setColumn(int column) override;
    void setAntennaDistance(double distance) override;
    virtual void setModel(Model model) override;

    void setTransmitterProduct(TransmitterProduct*);

private:
    TransmitterProduct* m_graphic;
    MathematicalFactory *m_mathematicalfactory;
    int m_posx,m_posy;
    int m_row, m_column, m_model;
    double m_orientation, m_power, m_antennadistance;
    unsigned long m_frequency;

};

#endif // MATHEMATICALTRANSMITTERPRODUCT_H
