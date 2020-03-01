#ifndef BUILDINGPRODUCT_H
#define BUILDINGPRODUCT_H

#include <QPointF>
#include <iostream>

using namespace std;

class BuildingProduct{
public:
    enum Model{brick,concrete,none};
    virtual ~BuildingProduct() {}

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual double getOrientation() = 0;
    virtual double getConductivity() = 0;
    virtual double getPermittivity() = 0;
    virtual int getModel()=0;
    virtual QVector<QPointF> getExtremities() = 0;

    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setOrientation(double orientation) = 0;
    virtual void setConductivity(double sigma) = 0;
    virtual void setPermittivity(double eps) = 0;
    virtual void setModel(int model)=0;
    virtual void setExtremities(QVector<QPointF> extremities) =0;
};
#endif // BUILDINGPRODUCT_H
