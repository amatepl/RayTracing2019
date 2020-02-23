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
#include "Abstract_Factory/dialogfactory.h"
#include "Observer/dialogobservable.h"
#include "Graphics/patternwindow.h"

class DialogFactory;

class DialogTransmitterProduct : public QDialog, public TransmitterProduct,public DialogObservable
{
    Q_OBJECT
public:
    DialogTransmitterProduct(TransmitterProduct* graphic, DialogFactory* dialogfactory);
    ~DialogTransmitterProduct() override;

    void createDialog();

    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    unsigned long getFrequency() override;
    double getPower() override;
    int getRow() override;
    int getColumn() override;
    double getAntennaDistance() override;
    int getModel() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setPower(double power) override;
    void setFrequency(unsigned long frequency) override;
    void setRow(int row) override;
    void setColumn(int column) override;
    void setAntennaDistance(double distance) override;
    virtual void setModel(Model model) override;

    void attachObserver(DialogObserver*) override;
    void detachObserver(DialogObserver*) override;
    void notify() override;

private:
    Model m_model;
    QComboBox *m_modelBox;
    QSpinBox *m_posx,*m_posy,*m_row,*m_column;
    QDoubleSpinBox *m_orientation,*m_antennaDistance;
    QDoubleSpinBox *m_frequency;
    QDoubleSpinBox *m_power;
    QComboBox *m_frequencyorder;

    DialogFactory *m_dialogfactory;

    vector<DialogObserver*> m_dialogobserver;
    vector<DialogObserver*>::iterator m_dialogobserveriterator;

public slots:
    void newProperties();
    void openPlot();
    void changeModel(QString model);
};

#endif // DIALOGTRANSMITTERPRODUCT_H
