/*!
    \class DialogReceiverProduct
    \brief Dialog window for the receiver

    The dialog window of the receiver lets the user choose the physical and electrical properties
    of the receiving antena.

    It also displays the graphs of the communication channel properties.
    
*/

#ifndef DIALOGRECEIVERPRODUCT_H
#define DIALOGRECEIVERPRODUCT_H

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
#include "Product/ReceiverProduct/graphicsreceiverproduct.h"
#include "qcustomplot.h"
#include "Graphics/interfererencepattern.h"

using namespace QtDataVisualization;

class DialogReceiverProduct : public QDialog, public ReceiverProduct
{
    Q_OBJECT
public:
    DialogReceiverProduct(ReceiverProduct* mathematicalproduct);
    ~DialogReceiverProduct() override;

    QWidget* PhysicalImpulseResponse();
    QWidget* TDLImpulseResponse();
    QWidget* GeneralTabDialog();
    QWidget* RealPathLossDialog();
    QWidget* ModelPathLossDialog();
    QWidget* CellRange();
//    QWidget* DopplerSpectrum();
    QWidget* InterferencePattern();
    QWidget* DistributionInterference();
    QWidget* PrxAngularSpctr();
    QWidget* AngularDistr();
    QWidget* PrxDopplerSpctr();
    QWidget* DopplerDistr();

    void changeGraph();
    void setInterferencePattern(vector<double> impulse_r, double min, double max);
    void setDistributionInterference(map<double,double> impulse, QVector<double> rice_distribution);

    float getSpeed() override
    {
        return m_speed->value();
    }
    float getOrientation() override
    {
        return m_orientation->value();
    }
    int getPosX() override {return m_posx->value();}
    int getPosY() override {return m_posy->value();}
    double getPower() override {return m_power->text().toDouble();}
    complex <double> getEField() override {return m_e_field->text().toDouble();}
    bool getEnable() override {return enable;}
    int targetSNR() override {return m_target_snr->value();}
    int noiseFigure() override {return m_noise_figure->value();}
    int interFerenceMargin() override {return m_interferencemargin->value();}

    void setSpeed(float speed) override
    {
        m_speed->setValue(speed);
    }
    void setOrientation(float orientation) override
    {
        m_orientation->setValue(orientation);
    }
    void setPosX(int posX) override {m_posx->setValue(posX);}
    void setPosY(int posY) override {m_posy->setValue(posY);}
    void setPower(double p) override {m_power->insert(QString::number(p));}
    void setEField(complex<double> e) override {m_e_field->insert(QString::number(norm(e)));}
    void setEnable(bool enable) override;
    void setTargetSNR(int target) override {m_target_snr->setValue(target);}
    void setNoiseFigure(int figure) override {m_noise_figure->setValue(figure);}
    void setInterferecenceMargin(int interference) override {m_interferencemargin->setValue(interference);}

    void newProperties() override;
private:
    ReceiverProduct *m_mathematicalproduct;
    QSpinBox *m_posx,*m_posy, *m_target_snr, *m_noise_figure,* m_interferencemargin;
    QDoubleSpinBox *m_speed, *m_orientation;
    QLineEdit *m_power;
    QLineEdit *m_e_field;
    QTabWidget* m_tabwidget;
    QDialogButtonBox *m_buttonbox;
    QVector<QCPItemLine*> impulse_tdl;
    QCustomPlot *impulse_plot;
    QCustomPlot *angular_distr_plot;
    QCustomPlot *doppler_distr_plot;

    bool show_tdl;
    bool enable;
    InterfererencePattern *m_interferencepattern;
    QCustomPlot *m_distribution;

signals:
    void save(string path);
    void interferenceActivated();

public slots:
    void buttonBoxClicked(QAbstractButton *button);
    void saveProperties();
    void saveToDisk();
    void showTDL();
};

#endif // DIALOGRECEIVERPRODUCT_H
