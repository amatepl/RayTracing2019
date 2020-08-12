#ifndef TRANSMITTERPRODUCT_H
#define TRANSMITTERPRODUCT_H

#include "math.h"
#include "complex.h"
#include <vector>
#include <iostream>
#include <QPointF>

using namespace std;
class TransmitterProduct{
public:
    enum Kind{dipole,array,dipolereflector,arrayreflector};
    virtual ~TransmitterProduct() {}

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


    virtual complex <double> arrayFactor(double theta, double phi)
    {
        complex <double> xarray(0.0,0.0);
        complex <double> yarray(0.0,0.0);
        complex <double> arrayfactor(0.0,0.0);
        complex <double> i(0.0,1.0);
        complex <double> psy(0.0,0.0);
        complex <double> qsy(0.0,0.0);
        lambda = c/m_frequency;

        double d = lambda*0.5;
        double k = 2.0*M_PI/lambda;
        double alpha  = phi*M_PI/180.0;
        double principal_angle = m_pr_orientation*M_PI/12; // -5 -4 -3 ... 0 ... 3 4 5
        double beta = (theta+m_orientation)*M_PI/180;
        double alphaprime = M_PI/2;
        double betaprime = principal_angle;
        double A = sin(alpha)*sin(beta);
        double Aprime = sin(alphaprime)*sin(betaprime);
        double B = sin(alpha)*cos(beta);
        double Bprime = sin(alphaprime)*cos(betaprime);
        psy = i*d*k*(A-Aprime);
        qsy = i*d*k*(B-Bprime);
        double modA = fmod((A-Aprime),2);
        double modB = fmod((B-Bprime),2);
        if ((modA == 0) & (modB != 0)){
            yarray = double(m_column) + 0.0*i;
            xarray = (exp(qsy*double(m_row))-1.0)/(exp(qsy)-1.0);
        }
        else if ((modA != 0) && (modB == 0)){
            yarray = (exp(psy*double(m_column))-1.0)/(exp(psy)-1.0);
            xarray = double(m_row)+0.0*i;
        }
        else if ((modA == 0)&& (modB == 0)){
            yarray = double(m_column) + 0.0*i;
            xarray = double(m_row)+0.0*i;
        }
        else {
            yarray = (exp(psy*double(m_column))-1.0)/(exp(psy)-1.0);
            xarray = (exp(qsy*double(m_row))-1.0)/(exp(qsy)-1.0);
        }
        if (theta == 180 && phi == 90)
        {
            cout << "xarray: " << xarray << endl;
            cout << "yarray: " << yarray << endl;
        }
//        arrayfactor = xarray*yarray/complex<double>(m_column*m_row);
        arrayfactor = xarray*yarray;
        return arrayfactor;
    }


    virtual complex <double> dipoleFactor(double theta, double phi)
    {
        complex <double> dipolefactor(0.0,0.0);
        if (phi == 0.0 || phi == 180.0) dipolefactor = 0.0;
        else dipolefactor = cos(0.5*M_PI*cos(phi*M_PI/180))/sin(phi*M_PI/180);
        return dipolefactor;
    }

    virtual complex <double> reflectorFactor(double theta, double phi){
        complex <double> reflectorfactor(0.0,0.0);
        lambda = c/m_frequency;

        double d = lambda/4.0;
        double k = 2.0*M_PI/lambda;
        complex <double> i(0.0,1.0);
        double thetaprime = theta + m_orientation;
        if (thetaprime < 0.0){
            thetaprime = 360 + thetaprime;
        }
        complex <double> psy = k*d*sin(phi*M_PI/180)*cos(thetaprime*M_PI/180);
        if ((thetaprime >= 270 && thetaprime < 360.0) || (thetaprime >=0 && thetaprime < 90.0)){reflectorfactor = 2.0*i*exp(-i*psy)*sin(psy);}
        return reflectorfactor;
    }

    virtual complex <double> totaleArrayFactor(double theta, double phi){
        complex <double> arrayfactor = arrayFactor(theta, phi);
        complex <double> dipolefactor = dipoleFactor(theta,phi);
        complex <double> reflectorfactor = reflectorFactor(theta,phi);
        if (getKind() == dipole){
            return dipolefactor;
        }
        else if (getKind() == array){
            return dipolefactor*arrayfactor;
        }
        else if (getKind() == dipolereflector){
            return dipolefactor*reflectorfactor;
        }
        else if (getKind() == arrayreflector){
            return dipolefactor*arrayfactor*reflectorfactor;
        }
        return 0;
    }

    virtual double electricalGain(double theta, double phi){
        return abs(totaleArrayFactor(theta,phi));
    }

    virtual double powerGain(double theta, double phi){
        complex <double> arrayfactor = arrayFactor(theta, phi);
        complex <double> dipolefactor = dipoleFactor(theta,phi);
        complex <double> reflectorfactor = reflectorFactor(theta,phi);
        if (getKind() == dipole){
            return 16.0/(3.0*M_PI)*pow(abs(dipolefactor),2);
        }
        else if (getKind() == array){
            return 16.0/(3.0*M_PI)*pow(abs(dipolefactor),2)*pow(abs(arrayfactor),2);
        }
        else if (getKind() == dipolereflector){
            return 16.0/(3.0*M_PI)*pow(abs(dipolefactor),2)*pow(abs(reflectorfactor),2);
        }
        else if (getKind() == arrayreflector){
            return 16.0/(3.0*M_PI)*pow(abs(dipolefactor),2)*pow(abs(arrayfactor),2)*pow(abs(reflectorfactor),2);
        }

        return 0;
    }

protected:
    // --> Global variables (electrical constants)

    double  epsilonAir      = 8.864e-12;    // A²S⁴kg⁻1m⁻3
    double  Zvoid           = 120*M_PI;
    double  muAir           = 4*M_PI*1e-7;  // Tm/A
    double  c               = 2.998e+8;     // m/s
    double  kb              = 1.379e-23;    // Boltzmann's constant
    double  T0              = 290;          // K; reference temperature T_0
    double  BW              = 100e+6;       // Hz
    double  antennaHeight   = 1.8;          //m
    double  Ra              = 71.0;   // Ohms, its a typical resistance data for \lambda/2 emettors

    double epsilonWallRel;
    unsigned long long m_frequency;           // Hz
    unsigned long long m_bandwidth;
    int m_row;
    int m_column;
    double lambda = c/m_frequency;
    double m_orientation;
    char m_pr_orientation;
};

#endif // TRANSMITTERPRODUCT_H
