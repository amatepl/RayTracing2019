#ifndef MATHEMATICALRECEIVERPRODUCT_H
#define MATHEMATICALRECEIVERPRODUCT_H

#include <QPointF>
#include <iostream>
#include <vector>

#include "Product/mathematicalproduct.h"
#include "Product/graphicsproduct.h"
#include "Observer/productobservable.h"
#include "receiverproduct.h"
#include "dialogreceiverproduct.h"

const double kb = 1.379e-23;
const double To = 290.0;

using namespace std;

class MathematicalReceiverProduct: public QPointF, public MathematicalProduct, public ProductObservable,
        public ReceiverProduct
{
public:
    MathematicalReceiverProduct(int posX, int posY);
    ~MathematicalReceiverProduct() override;

    void clearData();
    double inputNoise();
    void computeMinPrx();

    // 1. Path Loss Computation:
    std::map<double,double> pathLoss(){return m_pathloss;}
    void setPathLoss(std::map<double,double> pathloss);
    void linearRegressionPathLoss();
    void computePathLossFading();
    double standardDeviation();
    void modelPathLoss();

    // From ReceiverProduct:
    int getPosX() override;
    int getPosY() override;
    double getPower() override;
    complex<double> getEField() override;
    bool getEnable() override;
    int targetSNR() override {return m_target_snr;}
    int noiseFigure() override {return m_noise_figure;}
    int interFerenceMargin() override {return m_interferencemargin;}

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setPower(double p) override;
    void setEField(complex<double> e) override;
    void setEnable(bool enable) override;
    void setTargetSNR(int target) override {m_target_snr = target;}
    void setNoiseFigure(int figure) override {m_noise_figure = figure;}
    void setInterferecenceMargin(int interference) override {m_interferencemargin = interference;}

    void newProperties() override;

    // From MathematicalProduct
    void update(QGraphicsItem *graphic) override;
    void openDialog() override;


    // From ProductObservable
    void attachObserver(ProductObserver *productObserver) override;
    void notifyObservers();
    void notify() override;
    void notify(double &power, std::vector<double> *powers, std::complex<double> &EMfiled) override;
    void answer(ProductObserver *observer, double &power, std::vector<double> *powers, std::complex<double> &EMfield) override;
    QPointF* getPos()override;

private:
    // 0. Intrisic parameters
    bool enable;
    float m_speed;
    float m_orientation;
    int m_target_snr;
    int m_noise_figure;
    int m_interferencemargin;

    // 1. For ProductOBserves
    vector<ProductObserver*> m_observers;
    ProductObserver *m_transmitter = nullptr;

    // 2. For E Field And Power Computation
    complex <double> m_e_field;
    double m_power=0;

    // 3. For Path Loss Computation
    std::map<double,double> m_pathloss;
    QVector<double> logD, fading, logD_model;
};

#endif // MATHEMATICALRECEIVERPRODUCT_H
