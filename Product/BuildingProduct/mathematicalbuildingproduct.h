#ifndef MATHEMATICALBUILDINGPRODUCT_H
#define MATHEMATICALBUILDINGPRODUCT_H

#include <QPolygonF>

#include "buildingproduct.h"
#include "Abstract_Factory/mathematicalfactory.h"

class MathematicalFactory;

class MathematicalBuildingProduct : public QPolygonF, public BuildingProduct
{
public:
    MathematicalBuildingProduct(BuildingProduct* graphic, MathematicalFactory* mathematicalFactory);
    ~MathematicalBuildingProduct() override;

    void newProperties();

    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    double getConductivity() override;
    double getPermittivity() override;
    int getModel() override;
    QVector<QPointF> getExtremities() override;

    BuildingProduct* getBuildingProduct();

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setConductivity(double sigma) override;
    void setPermittivity(double eps) override;
    void setModel(int model) override;
    void setExtremities(QVector<QPointF> extremities) override;

    void setBuildingProduct(BuildingProduct *graphic);

private:
    MathematicalFactory *m_mathematicalfactory;
    QVector<QPointF> m_extremities;
    Model m_model;
    BuildingProduct* m_graphic;
    int m_posx,m_posy;
    double m_orientation,m_permittivity,m_conductivity;
};

#endif // MATHEMATICALBUILDINGPRODUCT_H
