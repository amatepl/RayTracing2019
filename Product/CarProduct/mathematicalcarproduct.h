#ifndef MATHEMATICALCARPRODUCT_H
#define MATHEMATICALCARPRODUCT_H

#include <QRectF>
#include <iostream>

#include "carproduct.h"
#include "Abstract_Factory/mathematicalfactory.h"

using namespace std;

class MathematicalCarProduct: public QRectF, public CarProduct
{
public:
    MathematicalCarProduct(CarProduct* graphic, MathematicalFactory* factory);
    ~MathematicalCarProduct() override;

    void newProperties();

    int getPosX() override;
    int getPosY() override;
    double getSpeed() override;
    double getOrientation() override;

    CarProduct* getCarProduct();

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setSpeed(double) override;
    void setOrientation(double orientation) override;

    void setCarProduct(CarProduct*);

private:
    MathematicalFactory* m_mathematicalfactory;
    CarProduct* m_graphic;
    int m_posx, m_posy;
    double m_orientation, m_speed;
};

#endif // MATHEMATICALCARPRODUCT_H
