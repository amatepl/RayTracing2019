#ifndef MATHEMATICALRECEIVERPRODUCT_H
#define MATHEMATICALRECEIVERPRODUCT_H

#include <QPointF>
#include <iostream>
#include <vector>

#include "Product/mathematicalproduct.h"
#include "Product/graphicsproduct.h"
#include "Observer/productobservable.h"
#include "receiverproduct.h"
#include "dialogreceiverproduct.h"

using namespace std;

class MathematicalReceiverProduct: public QPointF, public MathematicalProduct, public ProductObservable,
        public ReceiverProduct
{
public:
    MathematicalReceiverProduct(int posX, int posY);
    ~MathematicalReceiverProduct() override;

    // From ReceiverProduct:
    int getPosX() override;
    int getPosY() override;
    double getPower() override;
    complex<double> getEField() override;
    bool getEnable() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setPower(double p) override;
    void setEField(complex<double> e) override;
    void setEnable(bool enable) override;

    void newProperties() override;

    // From MathematicalProduct
    void update(QGraphicsItem *graphic) override;
    void openDialog() override;


    // From ProductObservable
    void attachObserver(ProductObserver *productObserver) override;
    void notifyObservers();
    void notify() override;
    void notify(double &power, std::vector<double> *powers, std::complex<double> &EMfiled) override;
    void answer(ProductObserver *observer, double &power, std::vector<double> *powers, std::complex<double> &EMfield) override;
    QPointF* getPos()override;

private:
    vector<ProductObserver*> m_observers;
    complex <double> m_e_field;
    double m_power=0;
    bool enable;
    float m_speed;
    float m_orientation;
    ProductObserver *m_transmitter = nullptr;
};

#endif // MATHEMATICALRECEIVERPRODUCT_H
