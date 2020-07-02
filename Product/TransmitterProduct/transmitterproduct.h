#ifndef TRANSMITTERPRODUCT_H
#define TRANSMITTERPRODUCT_H

#include "math.h"
#include "complex.h"
#include <vector>
#include <iostream>

using namespace std;
class TransmitterProduct{
public:
    enum Kind{dipole,array,dipolereflector,arrayreflector};
    virtual ~TransmitterProduct() {}

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual double getOrientation() = 0;
    virtual Kind getKind() = 0;
    virtual double getPower() = 0;
    virtual int getRow() = 0;
    virtual int getColumn() = 0;
    virtual unsigned long getFrequency() = 0;

    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setOrientation(double orientation) = 0;
    virtual void setPower(double power) = 0;
    virtual void setFrequency(unsigned long frequency) = 0;
    virtual void setRow(int row) = 0;
    virtual void setColumn(int column) = 0;
    virtual void setKind(Kind kind) = 0;
    virtual void newProperties() = 0;

    virtual complex <double> arrayFactor(double theta, double phi) {
        complex <double> xarray(0.0,0.0);
        complex <double> yarray(0.0,0.0);
        complex <double> arrayfactor(0.0,0.0);
        complex <double> i(0.0,1.0);
        complex <double> psy(0.0,0.0);
        complex <double> qsy(0.0,0.0);
        lambda = c/m_frequency;

        double d = lambda*0.5;
        double k = 2.0*M_PI/lambda;

        psy = i*k*d*sin(phi*M_PI/180)*sin(theta*M_PI/180);
        qsy = i*k*d*sin(phi*M_PI/180)*cos(theta*M_PI/180);

        if ((theta == 0.0 || theta == 180.0) && (phi != 0.0)){
            yarray = double(m_column) + 0.0*i;
            xarray = (exp(qsy*double(m_row))-1.0)/(exp(qsy)-1.0);

        }
        else if ((theta == 90.0 || theta == 270.0) && (phi != 0.0)){
            yarray = (exp(psy*double(m_column))-1.0)/(exp(psy)-1.0);
            xarray = double(m_row)+0.0*i;
            std::cout << "Condition 2: " << lambda << " and " << exp(psy) << std::endl;

        }
        else if (phi == 0.0){
            yarray = double(m_column) + 0.0*i;
            xarray = double(m_row)+0.0*i;

        }
        else {
            yarray = (exp(psy*double(m_column))-1.0)/(exp(psy)-1.0);
            xarray = (exp(qsy*double(m_row))-1.0)/(exp(qsy)-1.0);
        }
        arrayfactor = xarray*yarray;
        return arrayfactor;
    }

    virtual complex <double> dipoleFactor(double phi) {
        complex <double> dipolefactor(0.0,0.0);
        if (phi == 0.0 || phi == 180.0) dipolefactor = 0.0;
        else dipolefactor = cos(0.5*M_PI*cos(phi*M_PI/180))/sin(phi*M_PI/180);
        return dipolefactor;
    }

    virtual complex <double> totaleArrayFactor(double theta, double phi){
        complex <double> arrayfactor = arrayFactor(theta, phi);
        complex <double> dipolefactor = dipoleFactor(phi);
        return arrayfactor;//*dipolefactor;
    }

    virtual double electricalGain(double theta, double phi){
        return abs(totaleArrayFactor(theta,phi));
    }

    virtual double powerGain(double theta, double phi){
        double gain;
        complex <double> arrayfactor = arrayFactor(theta, phi);
        complex <double> dipolefactor = dipoleFactor(phi);
        gain = 16.0/(3.0*M_PI)*pow(abs(dipolefactor),2)*pow(abs(arrayfactor),2);
        return gain;
    }

protected:
    // --> Global variables (electrical constants)

    double  epsilonAir = 8.864e-12; // A²S⁴kg⁻1m⁻3
    double  Zvoid = 120*M_PI;
    double  muAir = 4*M_PI*1e-7;    // Tm/A
    double  c = 2.998e+8;           // m/s
    double  kb = 1.379e-23;         // Boltzmann's constant
    double  T0 = 290;               // K; reference temperature T_0
    double  BW = 100e+6;            // Hz
    double  antennaHeight = 1.8;    //m
    double  Ra = 71.0;   // Ohms, its a typical resistance data for \lambda/2 emettors

    double epsilonWallRel;
    unsigned long m_frequency;           // Hz
    int m_row;
    int m_column;
    double lambda;
};

#endif // TRANSMITTERPRODUCT_H
