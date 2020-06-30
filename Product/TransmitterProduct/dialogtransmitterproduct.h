#ifndef DIALOGTRANSMITTERPRODUCT_H
#define DIALOGTRANSMITTERPRODUCT_H

#include <QObject>
#include <QDialog>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QComboBox>

#include "transmitterproduct.h"
#include "graphicstransmitterproduct.h"
#include"Graphics/patternwindow.h"

class DialogTransmitterProduct : public QDialog, public TransmitterProduct
{
    Q_OBJECT
public:
    DialogTransmitterProduct(TransmitterProduct* mathematicalproduct);
    ~DialogTransmitterProduct() override;

    void createDialog();

    int getPosX() override {return m_posx->value();}
    int getPosY() override {return m_posy->value();}
    double getOrientation() override {return m_orientation->value();}
    unsigned long getFrequency() override;
    double getPower() override {return m_power->value();}
    int getRow() override {return m_rowBox->value();}
    int getColumn() override {return m_columnBox->value();}
    Kind getKind() override {return m_kind;}

    void setPosX(int posX) override {m_posx->setValue(posX);}
    void setPosY(int posY) override {m_posy->setValue(posY);}
    void setOrientation(double orientation) override {m_orientation->setValue(orientation);}
    void setPower(double power) override {m_power->setValue(power);}
    void setFrequency(unsigned long frequency) override;
    void setRow(int row) override {m_rowBox->setValue(row); m_row = row;}
    void setColumn(int column) override {m_columnBox->setValue(column); m_column = column;}
    virtual void setKind(Kind kind) override;
    void newProperties() override;

private:
    Kind m_kind;
    QComboBox *m_modelBox;
    QSpinBox *m_posx,*m_posy,*m_rowBox,*m_columnBox;
    QDoubleSpinBox *m_orientation;
    QDoubleSpinBox *m_frequencyValue;
    QDoubleSpinBox *m_power;
    QComboBox *m_frequencyorder;

    TransmitterProduct* m_mathematicalproduct;

public slots:
    void saveProperties();
    void openPlot();
    void changeModel(QString model);
};

#endif // DIALOGTRANSMITTERPRODUCT_H
