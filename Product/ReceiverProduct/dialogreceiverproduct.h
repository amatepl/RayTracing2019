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

    int getPosX() override {return m_posx->value();}
    int getPosY() override {return m_posy->value();}
    double getPower() override {return m_power->text().toDouble();}
    complex <double> getEField() override {return m_e_field->text().toDouble();}
    bool getEnable() override {return enable;}

    void setPosX(int posX) override {m_posx->setValue(posX);}
    void setPosY(int posY) override {m_posy->setValue(posY);}
    void setPower(double p) override {m_power->insert(QString::number(p));}
    void setEField(complex<double> e) override {m_e_field->insert(QString::number(norm(e)));}
    void setEnable(bool enable) override;

    void newProperties() override;
private:
    ReceiverProduct *m_mathematicalproduct;
    QSpinBox *m_posx,*m_posy;
    QLineEdit *m_power;
    QLineEdit *m_e_field;
    QTabWidget* m_tabwidget;
    QDialogButtonBox *m_buttonbox;
    bool enable;

public slots:
    void saveProperties();
};

#endif // DIALOGRECEIVERPRODUCT_H
