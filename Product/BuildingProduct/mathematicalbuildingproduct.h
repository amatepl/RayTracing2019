#ifndef MATHEMATICALBUILDINGPRODUCT_H
#define MATHEMATICALBUILDINGPRODUCT_H

#include <QPolygonF>
#include <array>

#include "buildingproduct.h"
#include "Product/mathematicalproduct.h"
#include "dialogbuildingproduct.h"
#include "Share/wall.h"

using namespace std;

class MathematicalBuildingProduct : public QPolygonF, public MathematicalProduct, public BuildingProduct
{
public:
    MathematicalBuildingProduct(QVector<QPointF> points);
    ~MathematicalBuildingProduct() override;

    // From BuildingProduct
    int getPosX() override {return m_posx;}
    int getPosY() override {return m_posy;}
    void setPosX(int posx) override {m_posx = posx;}
    void setPosY(int posy) override {m_posy = posy;}
    double getConductivity() override {return m_conductivity;}
    double getPermittivity() override {return m_permittivity;}
    void setConductivity(double sigma) override {m_conductivity = sigma;}
    void setPermittivity(double eps) override {m_permittivity = eps;}
    QVector<QPointF> getExtremities() override {return m_extremities;}
    std::string getModel() override {return m_model;}
    void setModel(std::string model) override;
    void setExtremities(QVector<QPointF> extremities) override;

    void moveToPosition(const QPointF &pos);
    void moveWalls(QPointF &moveDirection);
    Wall *getWalls() ;
    QPointF closestPoint(const QPointF &point);
    vector<Wall *> nearestWalls(const QPointF &point);
    QPolygonF shadow(const QPointF &light);
    vector <QPointF> extremities(const QPointF &light);
    Wall* cornerSecondWall(Wall *wall, const QPointF &corner)const;
    bool adjacentWall(const QLineF &line, Wall *&wall);
    QPointF forDiffraction(Wall *wall, const QPointF &corner)const;

    void newProperties() override;

    // From MathematicalProduct
    std::string changeAppearance() override {return m_model;}
    void update(QGraphicsItem* graphic) override;
    void openDialog() override;

protected:
    QVector<QPointF> m_extremities;
    int m_posx, m_posy; // Correspond to the up-left corner
    std::string m_model;
    double m_permittivity;
    double m_conductivity;
    vector<Wall*> m_walls; // Array of pointers.
};


#endif // MATHEMATICALBUILDINGPRODUCT_H
