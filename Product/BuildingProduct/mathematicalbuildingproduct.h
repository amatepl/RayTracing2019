#ifndef MATHEMATICALBUILDINGPRODUCT_H
#define MATHEMATICALBUILDINGPRODUCT_H

#include <QPolygonF>

#include "buildingproduct.h"
#include "Product/mathematicalproduct.h"


//class MathematicalFactory;

class MathematicalBuildingProduct : public QPolygonF, public MathematicalProduct
{
    enum Model{brick,concrete,none};
public:
    MathematicalBuildingProduct(QVector<QPointF> points);
    ~MathematicalBuildingProduct() override;

    /*
    void newProperties();

    int getPosX() override;
    int getPosY() override;
    float getOrientation() override;

    BuildingProduct* getBuildingProduct();

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(float theta) override;
    */
    void setConductivity(double sigma);
    void setPermittivity(double eps);
    void setModel(int model);
    void setExtremities(QVector<QPointF> extremities);
    double getConductivity();
    double getPermittivity();
    int getModel();
    QVector<QPointF> getExtremities();
    void update(QGraphicsItem* graphic) override;

private:
    //MathematicalFactory *m_mathematicalfactory;
    QVector<QPointF> m_extremities;
    Model m_model;
    BuildingProduct* m_graphic;
    double m_orientation,m_permittivity,m_conductivity;
};

#endif // MATHEMATICALBUILDINGPRODUCT_H
