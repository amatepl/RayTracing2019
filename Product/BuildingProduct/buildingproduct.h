#ifndef BUILDINGPRODUCT_H
#define BUILDINGPRODUCT_H

#include <QVector>
#include <QPointF>

class BuildingProduct
{
public:
    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual void setPosX(int posx) = 0;
    virtual void setPosY(int posy) = 0;
    virtual double getConductivity() = 0;
    virtual double getPermittivity() = 0;
    virtual void setConductivity(double sigma) = 0;
    virtual void setPermittivity(double eps) = 0;
    virtual void setExtremities(QVector<QPointF> extremities) = 0;
    virtual void setModel(std::string model) = 0;
    virtual std::string getModel() = 0;
    virtual QVector<QPointF> getExtremities() = 0;
    virtual void newProperties() = 0;
};

#endif // BUILDINGPRODUCT_H
