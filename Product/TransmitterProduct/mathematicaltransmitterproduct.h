#ifndef MATHEMATICALTRANSMITTERPRODUCT_H
#define MATHEMATICALTRANSMITTERPRODUCT_H

#include "math.h"
#include "complex.h"
#include <iostream>
#include <QPointF>
#include <QPolygonF>
#include <vector>

#include "transmitterproduct.h"
#include "Composite/MathematicalComponent.h"

#include "Observer/productobserver.h"

#include <Product/RayProduct/mathematicalrayproduct.h>

//class MathematicalFactory;

using namespace std;

class MathematicalTransmitterProduct : public TransmitterProduct, public QPointF, public MathematicalComponent,
        public ProductObserver
{
public:
    MathematicalTransmitterProduct(TransmitterProduct* graphic);
    ~MathematicalTransmitterProduct() override;

    void newProperties();

    static double computeGain(double theta,double phi, double frequency,int row,int column,double antennaDistance);

    void drawRays();

    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    unsigned long getFrequency();
    double getPower() ;
    int getRow();
    int getColumn();
    double getAntennaDistance() override;
    int getModel() override;

    TransmitterProduct* getTransmitterProduct();

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setPower(double power);
    void setFrequency(unsigned long frequency);
    void setRow(int row);
    void setColumn(int column);
    void setAntennaDistance(double distance) override;
    virtual void setModel(Model model) override;

    void setTransmitterProduct(TransmitterProduct*);
    complex<double> computeEMfield(vector<MathematicalRayProduct> *rayLine);
    double computeReflexionPer(double thetaI, double epsilonR);

    MathematicalComponent* toMathematicalComponent() override;

    // ProductObserver

    void notify(const QPointF &pos) override;

private:
    TransmitterProduct* m_graphic;
    int m_posx,m_posy;
    int m_row, m_column, m_model;
    double m_orientation, m_power, m_antennadistance;
    unsigned long m_frequency;
    double m_powerAtReceiver;

    QPolygonF m_zone;
    complex<double> m_EMfieldAtReceiver;
    vector<vector<MathematicalRayProduct>*> m_wholeRays;

    complex<double> m_EMfield;

    // --> Global variables (electrical constants)

    double  epsilonAir = 8.864e-12; // A²S⁴kg⁻1m⁻3
    double  Zvoid = 120*M_PI;
    double  muAir = 4*M_PI*1e-7;    // Tm/A
    double  c = 2.998e+8;           // m/s
    double  kb = 1.379e-23;         // Boltzmann's constant
    double  T0 = 290;               // K; reference temperature T_0
    double  freq = 26e+9;           // Hz
    double  BW = 100e+6;            // Hz
    double  antennaHeight = 1.8;    //m

    double lambda = c/freq;
    double  Ra = 71.0;   // Ohms, its a typical resistance data for \lambda/2 emettors

    double epsilonWallRel;

};

#endif // MATHEMATICALTRANSMITTERPRODUCT_H
