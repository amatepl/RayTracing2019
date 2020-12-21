#ifndef RX_H
#define RX_H

//#include <stdio.h>  /* defines FILENAME_MAX */
//#ifdef WINDOWS
//#include <direct.h>
//#define GetCurrentDir _getcwd
//#else
//#include <unistd.h>
//#define GetCurrentDir getcwd
//#endif

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

#include <QPointF>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <random>

/* Project Specific */

#include "Product/mathematicalproduct.h"
#include "Product/graphicsproduct.h"
#include "Observer/productobservable.h"
#include "receiverproduct.h"
#include "dialogrx.h"
#include "Widget/infowidget.h"
#include "Share/chdata.h"

//--------------------------------------------------------------------------------------------
//
//          Defines
//
//--------------------------------------------------------------------------------------------

using namespace std;

//--------------------------------------------------------------------------------------------
//
//          Class Rx
//
//--------------------------------------------------------------------------------------------

class Rx: public QPointF, public MathematicalProduct,
                                   public ProductObservable, public ReceiverProduct,
                                    public QObject
{
public:
    Rx(int posX, int posY);
    Rx(Rx *receiver);
    ~Rx() override;

    void clearObeservers();
    void clearData();
    double inputNoise();
    void computeMinPrx();
    void setInfoWidget(InfoWidget* info) {m_info_widget = info;}
    void setTransmitterDistance(double distance) {m_transmitter_distance = distance;}
    void computeSnr();
    void computeDelaySpread();
    void riceFactor(double rice);
    void coherenceBandwidth();
    void attachTransmitter(ProductObserver *transmitter);

    /*!
     * \brief extractChData
     *
     * Extracts the data from chData and copy it to ReceiverProduct
     * member attributs.
     */
    void extractChData();   // Will need to be removed

    // 1. Path Loss Computation:
//    void linearRegressionPathLoss();
//    void computePathLossFading();
//    double standardDeviation();
//    void modelPathLoss();

    // 2. Impulse Response and TDL Computation:
    void computeImpulseTDL();

    // 3. Cell Range Computation:
//    void cellRange();
    // Frequecy Response
    vector<double> fqResp() const override;
    vector<double> fq() const override;

    // 4. Doppler
    void dopplerSpectrum();

    // . Power Angular Spectrum
//    vector<double> prxAngularSpctr() const override;

    // . Power Doppler Spectrum
//    vector<double> prxDopplerSpctr() const override;

    // 5. Space correlation
    vector<double> spaceCrltn() override;
    vector<double> deltaZ() override;

    // 6. Time correlation
    vector<double> timeCrltn() const override;
    vector<double> timeCrltnT() const override;

    // From ReceiverProduct:
    float getSpeed() override;
    float getOrientation() override;
    QLineF movement() const;
    int getPosX() override;
    int getPosY() override;
    double getPower() override;
    double getDstnc() override;
    double getDlySprd() override;
    double getRiceFctr() override;
    double getCoherenceBw() override;
    double getCoherenceTm() override;
    double getAngSprd() override;
    double getDopplerSprd() override;
    complex<double> getEField() override;
    complex<double> getVoltage() override;
    bool getEnable() override;
    int targetSNR() override {return m_target_snr;}
    int noiseFigure() override {return m_noise_figure;}
    int interFerenceMargin() override {return m_interferencemargin;}
    vector<double> getDoppler() override;
    vector<double> getOmega() override;

    void setSpeed(float speed) override;
    void setOrientation(float orientation) override;
    void setMovement(QLineF const movement);
    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setPower(double p) override;
    void setEField(complex<double> e) override;
    void setEnable(bool enable) override;
    void setTargetSNR(int target) override {m_target_snr = target;}
    void setNoiseFigure(int figure) override {m_noise_figure = figure;}
    void setInterferecenceMargin(int interference) override {m_interferencemargin = interference;}
    void newProperties() override;
    void dialogDeleted() override;

    // From MathematicalProduct
    void update(QGraphicsItem *graphic) override;
    void attachObservable(GraphicsProduct* graphic) override;
    void openDialog(QWidget *parent) override;
    void updateInformation() override;


    // From ProductObservable
    void attachObserver(ProductObserver *productObserver) override;
    void detachObservers() override;
    void notifyObservers();

    complex<double> notifyObserversInterference(QLineF local_region);
    void notify() override;
    void notify(double &, std::vector<double> *, std::complex<double> &) override;
    const QPointF *getPos() const override;

private:
    // 0. Intrisic parameters
    bool enable;
    QLineF m_movement;
    int m_target_snr;
    int m_noise_figure;
    int m_interferencemargin;
    std::map<double,std::complex<double>> m_tdl;
    DialogRx *m_dialog = nullptr;
    InfoWidget *m_info_widget;
    double min_prx;

    // 1. For ProductOBserves

    vector<ProductObserver *> m_transmitters;
    ProductObserver *m_transmitter = nullptr;
//    map<ProductObserver *, vector<ProductObserver *>> m_txImages;
    Data *m_chData {nullptr};

    // 2. For E Field And Power Computation
    complex <double> m_ind_voltage;
    complex <double> m_e_field;
    double m_power = 0;
    double m_transmitter_distance;
    double snr_received;
    double delay_spread;
    double rice_factor;
    double coherence_bandwidth;

    // 3. For Path Loss Computation
    std::map<double /*distance*/, double /*power*/> m_pathloss;
    QVector<double> logD, fading, logD_model;

    // 4. For Impulse Response and TDL
    std::map<double,std::complex<double>> m_impulse;

    // 5. Doppler
    std::map<double,std::complex<double>> m_doppler;

    // 6. Correlations


public slots:
    void save(string path);
    void record();
    void sendInterferencePattern();
};

template <typename T>
void dB (T &container)
{
    for (auto & i: container) {
        i = 20 * log10(i);
    }
}


#endif // RX_H
