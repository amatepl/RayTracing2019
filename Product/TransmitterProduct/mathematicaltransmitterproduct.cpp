#include "mathematicaltransmitterproduct.h"
MathematicalTransmitterProduct::MathematicalTransmitterProduct(int posx,int posy,double orientation,double power,unsigned long frequency)
{
    m_posx = posx;
    m_posy = posy;
    m_orientation = orientation;
    m_power = power;
    m_frequency = frequency;
}

MathematicalTransmitterProduct::~MathematicalTransmitterProduct(){

}

double MathematicalTransmitterProduct::computeGain(double theta,double phi, double frequency, int row,int column,double antennaDistance){
    complex <double> dipolefactor(0.0,0.0);
    complex <double> xarray(0.0,0.0);
    complex <double> yarray(0.0,0.0);
    complex <double> arrayfactor(0.0,0.0);
    complex <double> i(0.0,1.0);
    complex <double> psy(0.0,0.0);
    complex <double> qsy(0.0,0.0);

    double c = 3.0e9;
    double lambda = c/frequency;
    double d = lambda*antennaDistance;
    double k = 2.0*M_PI/lambda;
    double gain;

    psy = i*k*d*sin(phi*M_PI/180)*sin(theta*M_PI/180);
    qsy = i*k*d*sin(phi*M_PI/180)*cos(theta*M_PI/180);
    xarray = (exp(qsy*double(row))-1.0)/(exp(qsy)-1.0);
    yarray = (exp(psy*double(column))-1.0)/(exp(psy)-1.0);

    if (psy == 0.0+0.0*i){
        yarray = double(column) +0.0*i;
    }
    if(qsy == 0.0+0.0*i){
        xarray = double(row)+0.0*i;
    }

    arrayfactor = xarray*yarray;
    if (phi == 0.0 || phi == 180.0) dipolefactor = 0.0;
    else dipolefactor = cos(0.5*M_PI*cos(phi*M_PI/180))/sin(phi*M_PI/180);
    gain = 16.0/(3.0*M_PI)*abs(arrayfactor)*abs(dipolefactor);
    return gain;
}

int MathematicalTransmitterProduct::getPosX(){
    return m_posx;
}

int MathematicalTransmitterProduct::getPosY(){
    return m_posy;
}

double MathematicalTransmitterProduct::getOrientation(){
    return m_orientation;
}

unsigned long MathematicalTransmitterProduct::getFrequency(){
    return m_frequency;
}

double MathematicalTransmitterProduct::getPower(){
    return m_power;
}

int MathematicalTransmitterProduct::getRow(){

}

int MathematicalTransmitterProduct::getColumn() {

}
double MathematicalTransmitterProduct::getAntennaDistance() {

}
int MathematicalTransmitterProduct::getModel() {

}

void MathematicalTransmitterProduct::setPosX(int posX){
    m_posx = posX;
}

void MathematicalTransmitterProduct::setPosY(int posY){
    m_posy = posY;
}

void MathematicalTransmitterProduct::setOrientation(double orientation){
    m_orientation = orientation;
}

void MathematicalTransmitterProduct::setPower(double power){
    m_power = power;
}

void MathematicalTransmitterProduct::setFrequency(unsigned long frequency){
    m_frequency = frequency;
}

void MathematicalTransmitterProduct::setRow(int row){

}

void MathematicalTransmitterProduct::setColumn(int column) {

}

void MathematicalTransmitterProduct::setAntennaDistance(double distance) {

}

void  MathematicalTransmitterProduct::setModel(Model model) {

}
