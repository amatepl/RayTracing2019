#ifndef MATHEMATICALRECEIVERPRODUCT_H
#define MATHEMATICALRECEIVERPRODUCT_H

#include <QPointF>
#include <iostream>
#include <vector>

//#include "receiverproduct.h"
#include "Composite/MathematicalComponent.h"
#include "Composite/graphicscomponent.h"
#include "Observer/productobservable.h"
//#include "Product/ReceiverProduct/graphicsreceiverproduct.h"
class GraphicsReceiverProduct;

using namespace std;

//class MathematicalFactory;
class GraphicsReceiverProduct;

class MathematicalReceiverProduct: public QPointF/*, public ReceiverProduct*/, public MathematicalComponent,
        public ProductObservable
{
public:
//    MathematicalReceiverProduct(ReceiverProduct* graphic, MathematicalFactory* factory);
    MathematicalReceiverProduct(GraphicsReceiverProduct* graphics);
    ~MathematicalReceiverProduct() override;

    void newProperties();

    int getPosX() override;
    int getPosY() override;
    double getPower();
    unsigned long getFrequency();

    //ReceiverProduct* getReceiverProduct();

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setFrequency(unsigned long frequency);

    void setReceiverProduct(GraphicsReceiverProduct* graphic);

    MathematicalComponent* toMathematicalComponent() override;
    void notifyObservers();

    void attachObserver(ProductObserver *productObserver) override;

private:

    //ReceiverProduct* m_graphic;
    GraphicsReceiverProduct* m_graphic;
    int m_posx,m_posy;
    double m_power, m_efield;
    unsigned long m_frequency;
    vector<ProductObserver*> m_observers;
};

#endif // MATHEMATICALRECEIVERPRODUCT_H
