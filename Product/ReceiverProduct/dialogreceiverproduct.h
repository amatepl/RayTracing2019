#ifndef DIALOGRECEIVERPRODUCT_H
#define DIALOGRECEIVERPRODUCT_H

#include <QDialog>
#include <QLineEdit>

#include "receiverproduct.h"
#include "Abstract_Factory/dialogfactory.h"


class DialogFactory;

class DialogReceiverProduct : public QDialog, public ReceiverProduct
{
    Q_OBJECT
public:
    DialogReceiverProduct(ReceiverProduct* graphic, DialogFactory* dialogfactory);
    ~DialogReceiverProduct() override;

    void createDialog();

    int getPosX() override;
    int getPosY() override;
    unsigned long getFrequency() override;
    double getPower() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setFrequency(unsigned long frequency) override;

private:
    QSpinBox *m_posx,*m_posy;
    QDoubleSpinBox *m_frequency;
    QLineEdit *m_power;
    QLineEdit *m_efield;
    QComboBox *m_frequencyorder;

    DialogFactory *m_dialogfactory;

public slots:
    void newProperties();
};

#endif // DIALOGRECEIVERPRODUCT_H
