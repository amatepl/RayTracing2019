#ifndef MATHEMATICALRECEIVERPRODUCT_H
#define MATHEMATICALRECEIVERPRODUCT_H

#include <QPointF>
#include <iostream>
#include <vector>

#include "Product/mathematicalproduct.h"
#include "Product/graphicsproduct.h"
#include "Observer/productobservable.h"

using namespace std;

class MathematicalReceiverProduct: public QPointF, public MathematicalProduct, public ProductObservable
{
public:
    MathematicalReceiverProduct(int posX, int posY);
    ~MathematicalReceiverProduct() override;

    void update(QGraphicsItem *graphic) override;

    void attachObserver(ProductObserver *productObserver) override;

private:
    vector<ProductObserver*> m_observers;
};

#endif // MATHEMATICALRECEIVERPRODUCT_H
