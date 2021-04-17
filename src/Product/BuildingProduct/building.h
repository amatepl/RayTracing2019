#ifndef BUILDING_H
#define BUILDING_H

#include <QPolygonF>
#include <array>

#include "buildingproduct.h"
#include "Product/mathematicalproduct.h"
#include "dialogbuildingproduct.h"
#include "Share/wall.h"

using namespace std;

class Building : public QPolygonF, public MathematicalProduct, public BuildingProduct
{
public:
    Building(QVector<QPointF> points);
    ~Building() override;

    // From BuildingProduct
    int getPosX() override {return m_pos.x();}
    int getPosY() override {return m_pos.y();}
    void setPosX(int posx) override {m_pos.setX(posx);}
    void setPosY(int posy) override {m_pos.setY(posy);}
    double getConductivity() override {return m_conductivity;}
    double getPermittivity() override {return m_permittivity;}
    void setConductivity(double sigma) override {m_conductivity = sigma;}
    void setPermittivity(double eps) override;
    QVector<QPointF> getExtremities() override {return m_extremities;}
    std::string getModel() override {return m_model;}
    void setModel(std::string model) override;
    void setExtremities(QVector<QPointF> extremities) override;

    void moveToPosition(const QPointF &pos);
    void moveWalls(QPointF &moveDirection);
    void changeWalls();
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
    void openDialog(QWidget *) override;

protected:
    QVector<QPointF> m_extremities;
    QPointF m_leftupcorner = QPointF(0,0);
    QPointF m_pos; // Correspond to the up-left corner
    bool to_translate = true;
    std::string m_model;
    double m_permittivity;
    double m_conductivity;
    vector<Wall*> m_walls; // Array of pointers.
};


#endif // BUILDING_H
