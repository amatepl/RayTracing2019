#ifndef WALL_H
#define WALL_H

#include <math.h>
#include "Share/line.h"
class MathematicalBuildingProduct;

class Wall: public Line
{
public:
    Wall(double x01 = 0 , double y01 = 0, double x02 = 0, double y02 = 0, double thickness = 0.0, double relEps = 0.0, double sig = 0.0, int listInd = 0);
    Wall(const QPointF &p1, const QPointF &p2, double thickness = 0.0, double relEps = 0.0, double sig = 0.0, int listInd = 0);
    ~Wall(void);

    double getEpsilon() const{return thick;}
    double getSigma() const{return epsilon;}
    double getThick() const{return sigma;}
    int getIndWall() const{return indWall;}
    void setBuilding(MathematicalBuildingProduct *building) {m_building = building;}
    MathematicalBuildingProduct* getBuilding()const {return m_building;}

    QPointF symetricalPoint(const QPointF &point);
    QPointF otherPoint(const QPointF &point)const;

private:
    double thick;
    double epsilon;
    double sigma;
    int indWall;
    MathematicalBuildingProduct *m_building;
};

#endif // WALL_H
