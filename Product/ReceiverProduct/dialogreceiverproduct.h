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

#include "receiverproduct.h"
#include "Product/ReceiverProduct/graphicsreceiverproduct.h"
#include "qcustomplot.h"

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
    QWidget* DopplerSpectrum();
    void changeGraph();

    int getPosX() override {return m_posx->value();}
    int getPosY() override {return m_posy->value();}
    double getPower() override {return m_power->text().toDouble();}
    complex <double> getEField() override {return m_e_field->text().toDouble();}
    bool getEnable() override {return enable;}
    int targetSNR() override {return m_target_snr->value();}
    int noiseFigure() override {return m_noise_figure->value();}
    int interFerenceMargin() override {return m_interferencemargin->value();}

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
    QLineEdit *m_power;
    QLineEdit *m_e_field;
    QTabWidget* m_tabwidget;
    QDialogButtonBox *m_buttonbox;
    QVector<QCPItemLine*> impulse_tdl;
    QCustomPlot *impulse_plot;
    bool show_tdl;
    bool enable;

public slots:
    void saveProperties();
    void showTDL();
};

#endif // DIALOGRECEIVERPRODUCT_H
