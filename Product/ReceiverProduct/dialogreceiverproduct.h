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

//#include "receiverproduct.h"
//#include "Abstract_Factory/dialogfactory.h"
//#include "Product/ReceiverProduct/graphicsreceiverproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"


//class DialogFactory;

class ReceiverProduct;

class DialogReceiverProduct : public QDialog/*, public ReceiverProduct*/
{
    Q_OBJECT
public:
    DialogReceiverProduct(ReceiverProduct* graphic);
    ~DialogReceiverProduct() override;

    void createDialog();

    int getPosX();
    int getPosY();
    unsigned long getFrequency();
    double getPower();

    void setPosX(int posX);
    void setPosY(int posY);
    void setFrequency(unsigned long frequency);

private:
    QSpinBox *m_posx,*m_posy;
    QDoubleSpinBox *m_frequency;
    QLineEdit *m_power;
    QLineEdit *m_efield;
    QComboBox *m_frequencyorder;

    //DialogFactory *m_dialogfactory;

public slots:
    void newProperties();
};

#endif // DIALOGRECEIVERPRODUCT_H
