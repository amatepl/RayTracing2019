/*!
    \class DialogRx
    \brief Dialog window for the receiver

    The dialog window of the receiver lets the user choose the physical and electrical properties
    of the receiving antena.

    It also displays the graphs of the communication channel properties.
    
*/

#ifndef DIALOGRX_H
#define DIALOGRX_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QtDataVisualization>

#include "receiverproduct.h"
#include "Product/ReceiverProduct/graphicsrx.h"
#include "qcustomplot.h"
#include "Graphics/interfererencepattern.h"

using namespace QtDataVisualization;

class DialogRx : public QDialog/*, public ReceiverProduct*/
{
    Q_OBJECT
public:
    DialogRx(ReceiverProduct* mathematicalproduct, QWidget *parent=nullptr);
    ~DialogRx() override;

    /*!
     * \brief templatePlot
     * \param plot
     * \param title
     * \param xlabel
     * \param ylabel
     * \param xlog
     * \param ylog
     * \return Widget window with a simple graph window
     */
    QWidget* templatePlot(QCustomPlot *plot,
                          QString title,
                          QString xlabel,
                          QString ylabel,
                          bool xlog = false,
                          bool ylog = false);

    QWidget* PhysicalImpulseResponse();
    void updateImpulseResponse();
    QWidget* TDLImpulseResponse();
    QWidget* GeneralTabDialog();
    void updateChInfo();
    QWidget* InterferencePattern();
    QWidget* DistributionInterference();
    QWidget* PrxAngularSpctr();
    void updatePrxAngularSpctr();
    QWidget* AngularDistr();
    QWidget* PrxDopplerSpctr();
    void updatePrxDopplerSpctr();
    QWidget* DopplerDistr();
    QWidget *SpcCrltn();
    void updateSpcCrltn();
    QWidget *timeCrltn();
    void updateTimeCrltn();
    QWidget *DopplerSpectrum();
    void updateDopplerSpctr();
    QWidget* PDP();
    void updatePDP();
    QWidget *fqResp();
    void updateFqResp();

    template<typename T>
    QVector<T> vec2QVec(vector<T> vec)
    {
        return QVector(vec.begin(), vec.end());
    }
    void changeGraph();
    void setInterferencePattern(vector<double> impulse_r, double min, double max);
    void setDistributionInterference(map<double,double> impulse, QVector<double> rice_distribution);

//    float getSpeed() override
//    {
//        return m_speed->value();
//    }
//    float getOrientation() override
//    {
//        return m_orientation->value();
//    }
//    int getPosX() override {return m_posx->value();}
//    int getPosY() override {return m_posy->value();}
//    double getPower() override {return m_power->text().toDouble();}
//    complex <double> getEField() override {return m_e_field->text().toDouble();}
//    bool getEnable() override {return enable;}
//    int targetSNR() override {return m_target_snr->value();}
//    int noiseFigure() override {return m_noise_figure->value();}
//    int interFerenceMargin() override {return m_interferencemargin->value();}

//    void setSpeed(float speed) override
//    {
//        m_speed->setValue(speed);
//    }
//    void setOrientation(float orientation) override
//    {
//        m_orientation->setValue(orientation);
//    }
//    void setPosX(int posX) override {m_posx->setValue(posX);}
//    void setPosY(int posY) override {m_posy->setValue(posY);}
//    void setPower(double p) override {m_power->insert(QString::number(p));}
//    void setEField(complex<double> e) override {m_e_field->insert(QString::number(norm(e)));}
    void setEnable(bool enable);
//    void setTargetSNR(int target) override {m_target_snr->setValue(target);}
//    void setNoiseFigure(int figure) override {m_noise_figure->setValue(figure);}
//    void setInterferecenceMargin(int interference) override {m_interferencemargin->setValue(interference);}

    void newProperties();
    void update();
    void updateGeneralTab();

    /* To delete */
//    vector<double> spaceCrltn() override {};
private:

    int idxTab {0};
    ReceiverProduct *m_mathematicalproduct;
    QSpinBox *m_posx,*m_posy, *m_target_snr, *m_noise_figure,* m_interferencemargin;
    QDoubleSpinBox *m_speed, *m_orientation;
    QTabWidget* m_tabwidget;
    QDialogButtonBox *m_buttonbox;
    QVector<QCPItemLine*> impulse_tdl;
    QCustomPlot *impulse_plot;
    QCustomPlot *pas_plot;
    QCustomPlot *pds_plot;
    QCustomPlot *angular_distr_plot;
    QCustomPlot *doppler_distr_plot;
    QCustomPlot *spc_crltn_plot;
    QCustomPlot *tm_crltn_plot;
    QCustomPlot *pdp_plot;

    bool show_tdl;
    bool enable;
    InterfererencePattern *m_interferencepattern;
    QCustomPlot *m_distribution;

    // 1. Channel
    QLabel *m_eField;
    QLabel *m_indVoltage;
    QLabel *m_prx;
    QLabel *m_dstnc;
    QLabel *m_dlySprd;
    QLabel *m_riceFactor;
    QLabel *m_coherenceDist;
    QLabel *m_coherenceBw;
    QLabel *m_coherenceTm;
    QLabel *m_angSpdr;
    QLabel *m_dopplerSpdr;

    // 2. Impulse and TDL vVariables
    QVector<double> h,h_tdl,tau, tau_tdl;
    QCPTextElement *title_impulse;

    // 3. Frequency Response
    QCustomPlot *fq_resp_plot;

    // 4. Doppler
    PrxDopplerSpread pds;
    QVector<double> doppler_distr;
    double doppler_spread {0};
    QVector<double> w;
    QCustomPlot *doppler_spctr_plot;

    QVector<double> omega;
    QVector<double> doppler;

    // 5. Spatial correlation
    PrxAngularSpread pas;
    QVector<double> angular_distr;
    double angular_spread {0};
    QVector <double> u;

    // 6. Time correlation

    unsigned long m_transmitterfrequency;
    unsigned long m_transmitterbandwidth;

    // 7. PDP
    QVector<double> pdp;

signals:
    void save(string path);
    void interferenceActivated();

public slots:
    void buttonBoxClicked(QAbstractButton *button);
    void saveProperties();
    void saveToDisk();
    void showTDL();
    void tabOpened(int index);
};

template<class T>
QVector<double> normalise(T &vec, double coef)
{
    QVector<double> res;
    for(const auto &e: vec){
        res.push_back(e / coef);
    }
    return res;
}

#endif // DIALOGRX_H
