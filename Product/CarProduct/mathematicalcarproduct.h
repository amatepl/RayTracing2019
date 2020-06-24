#ifndef MATHEMATICALCARPRODUCT_H
#define MATHEMATICALCARPRODUCT_H

#include <QRectF>
#include <iostream>

#include "carproduct.h"
#include "Product/mathematicalproduct.h"

using namespace std;

class MathematicalCarProduct: public QRectF,  public MathematicalProduct
{
public:
    MathematicalCarProduct(int posX, int posY);
    ~MathematicalCarProduct() override;

    double getSpeed();
    double getOrientation();

    CarProduct* getCarProduct();

    void setSpeed(double);
    void setOrientation(double orientation);

    void update(QGraphicsItem *graphic) override;
    void openDialog() override;

private:
    //MathematicalFactory* m_mathematicalfactory;
    CarProduct* m_graphic;
    int m_posx, m_posy;
    double m_orientation, m_speed;
};

#endif // MATHEMATICALCARPRODUCT_H
