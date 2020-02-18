#ifndef GRAPHICSBUILDINGPRODUCT_H
#define GRAPHICSBUILDINGPRODUCT_H

#include <QGraphicsPolygonItem>

#include "buildingproduct.h"
#include "Composite/graphicscomponent.h"
#include "Abstract_Factory/graphicsfactory.h"

class GraphicsBuildingProduct : public QGraphicsPolygonItem, public BuildingProduct,public GraphicsComponent
{
public:
    GraphicsBuildingProduct(int posX, int posY, double orientation, GraphicsFactory *graphicsfactory);
    ~GraphicsBuildingProduct() override;

    static QPixmap getImage();

    int getType() override;
    bool graphicsSelected() override;
    void draw() override;

    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    double getConductivity() override;
    double getPermittivity() override;
    int getModel() override;
    QVector<QPointF> getExtremities() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setConductivity(double sigma) override;
    void setPermittivity(double eps) override;
    void setModel(int model) override;
    void setExtremities(QVector<QPointF> extremities) override;

private:
    GraphicsFactory *m_graphicsfactory;
    QVector<QPointF> m_extremities;
    Model m_model;
    int m_posx,m_posy;
    double m_orientation,m_permittivity,m_conductivity;
};

#endif // GRAPHICSBUILDINGPRODUCT_H
