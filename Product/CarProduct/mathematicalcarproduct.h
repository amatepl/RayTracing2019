#ifndef MATHEMATICALCARPRODUCT_H
#define MATHEMATICALCARPRODUCT_H

#include <QRectF>
#include <iostream>

#include "carproduct.h"
#include "Product/mathematicalproduct.h"
#include "dialogcarproduct.h"

using namespace std;

class MathematicalCarProduct: public QPolygonF,  public MathematicalProduct, public CarProduct
{
public:
    MathematicalCarProduct(QPolygonF rect, QPointF center);
    ~MathematicalCarProduct() override;

    double getSpeed() override;
    double getOrientation() override;
    int getPosX() override;
    int getPosY() override;

    void setSpeed(double) override;
    void setOrientation(double orientation) override;
    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void update(QGraphicsItem *graphic) override;
    void openDialog() override;
    void newProperties() override;

private:
    //MathematicalFactory* m_mathematicalfactory;
    QPointF m_center;
    double m_orientation, m_speed;
};

#endif // MATHEMATICALCARPRODUCT_H
