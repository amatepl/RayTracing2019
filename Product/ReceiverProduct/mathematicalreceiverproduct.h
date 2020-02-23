#ifndef MATHEMATICALRECEIVERPRODUCT_H
#define MATHEMATICALRECEIVERPRODUCT_H

#include <QPointF>
#include <iostream>

#include "receiverproduct.h"
#include "Abstract_Factory/mathematicalfactory.h"

using namespace std;

class MathematicalFactory;

class MathematicalReceiverProduct: public QPointF, public ReceiverProduct
{
public:
    MathematicalReceiverProduct(ReceiverProduct* graphic, MathematicalFactory* factory);
    ~MathematicalReceiverProduct() override;

    void newProperties();

    int getPosX() override;
    int getPosY() override;
    double getPower() override;
    unsigned long getFrequency() override;

    ReceiverProduct* getReceiverProduct();

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setFrequency(unsigned long frequency) override;

    void setReceiverProduct(ReceiverProduct* graphic);

private:
    MathematicalFactory *m_mathematicalfactory;
    ReceiverProduct* m_graphic;
    int m_posx,m_posy;
    double m_power, m_efield;
    unsigned long m_frequency;
};

#endif // MATHEMATICALRECEIVERPRODUCT_H
