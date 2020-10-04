#ifndef TXINTERFACE_H
#define TXINTERFACE_H

#include "math.h"
#include "complex.h"
#include <vector>
#include <iostream>
#include <QPointF>
#include "Share/physics.h"

using namespace std;
class TxInterface{
public:
    enum Kind{dipole,array,dipolereflector,arrayreflector};
    virtual ~TxInterface() {}

    /* Getters */
    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual double getOrientation() = 0;
    virtual char principalOrientation() = 0;
    virtual Kind getKind() = 0;
    virtual double getPower() = 0;
    virtual int getRow() = 0;
    virtual int getColumn() = 0;
    virtual unsigned long getFrequency() = 0;
    virtual unsigned long getBandwidth() = 0;
    virtual vector<double> powerPathLoss() = 0;
    virtual vector<double> distancePathLoss() = 0;
    virtual vector<double> linearPathLoss() = 0;
    virtual vector<double> friisLoss() = 0;
    virtual vector<double> powerPathLossModel() = 0;
    virtual vector<double> distancePathLossModel() = 0;
    virtual vector<double> linearPathLossModel() = 0;
    virtual double pathLossExponent() = 0;
    virtual double fadingVariability() = 0;
    virtual double minPower() = 0;

    /* Setters */
    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setOrientation(double orientation) = 0;
    virtual void setPrincipalOrientation(char orientation) = 0;
    virtual void setPower(double power) = 0;
    virtual void setFrequency(unsigned long frequency) = 0;
    virtual void setBandwidth(unsigned long bandwidth) = 0;
    virtual void setRow(int row) = 0;
    virtual void setColumn(int column) = 0;
    virtual void setKind(Kind kind) = 0;
    virtual void newProperties() {};
    virtual void newProperties(QPointF, double){};


    virtual complex <double> getTotalArrayFctr(double theta, double phy)
    {
        return ph::totaleArrayFactor(theta, phy, m_frequency, m_orientation, m_pr_orientation, m_column, m_row, static_cast<ph::TxType>(getKind()));
    }

protected:
    // --> Global variables (electrical constants)

    double epsilonWallRel;
    unsigned long long m_frequency;           // Hz
    unsigned long long m_bandwidth;
    int m_row;
    int m_column;
    double lambda /*= c/m_frequency*/;
    double wvNbr;
    double m_orientation;
    char m_pr_orientation;
};

#endif // TXINTERFACE_H
