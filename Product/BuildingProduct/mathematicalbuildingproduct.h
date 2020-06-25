#ifndef MATHEMATICALBUILDINGPRODUCT_H
#define MATHEMATICALBUILDINGPRODUCT_H

#include <QPolygonF>
#include <array>

#include "Product/mathematicalproduct.h"
#include "dialogbuildingproduct.h"
#include "Share/wall.h"

using namespace std;

class MathematicalBuildingProduct : public QPolygonF, public MathematicalProduct
{
public:
    MathematicalBuildingProduct(QVector<QPointF> points);
    ~MathematicalBuildingProduct() override;

    std::string changeAppearance() override {return m_model;}

    int getPosX() {return m_posx;}
    int getPosY() {return m_posy;}
    void setPosX(int posx) {m_posx = posx;}
    void setPosY(int posy) {m_posy = posy;}
    double getConductivity() {return m_conductivity;}
    double getPermittivity() {return m_permittivity;}
    void setConductivity(double sigma) {m_conductivity = sigma;}
    void setPermittivity(double eps) {m_permittivity = eps;}
    void setModel(std::string model);
    QVector<QPointF> getExtremities() {return m_extremities;}
    void setExtremities(QVector<QPointF> extremities);

    void moveToPosition(const QPointF &pos);
    void moveWalls(QPointF &moveDirection);
    Wall *getWalls() ;
    QPointF closestPoint(const QPointF &point);
    vector<Wall *> nearestWalls(const QPointF &point);
    QPolygonF shadow(const QPointF &light);
    vector <QPointF> extremities(const QPointF &light);
    Wall* cornerSecondWall(Wall *wall, const QPointF &corner)const;
    QPointF forDiffraction(Wall *wall, const QPointF &corner)const;

    void newProperties();
    void update(QGraphicsItem* graphic) override;
    void openDialog() override;

private:
    QVector<QPointF> m_extremities;
    int m_posx, m_posy; // Correspond to the up-left corner
    std::string m_model;
    double m_orientation,m_permittivity,m_conductivity;

    vector<Wall*> m_walls; // Array of pointers.
};


#endif // MATHEMATICALBUILDINGPRODUCT_H
