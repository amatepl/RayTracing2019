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

    enum typeWall{wall, front, back};
    double getEpsilon() const{return thick;}
    double getSigma() const{return epsilon;}
    double getThick() const{return sigma;}
    int getIndWall() const{return indWall;}
    double getSpeed() const;
    double getOrientation() const;
    int getWallType() const;
    QLineF movement() const;

    void setWallType(int type);
    void setSpeed(double speed);
    void setOrientation(double orientation);
    void setBuilding(MathematicalBuildingProduct *building) {m_building = building;}
    MathematicalBuildingProduct* getBuilding()const {return m_building;}
    void setMovement(QLineF const movement);

    QPointF symetricalPoint(const QPointF &point);
    QPointF otherPoint(const QPointF &point)const;
    QPointF farestExtrem(const QPointF &point) const;

private:
    double thick;
    double epsilon;
    double sigma;
    int indWall;
    MathematicalBuildingProduct *m_building;
    QLineF m_movement;
    //double m_speed {0};
    //double m_orientation{0};
    int m_wallType{wall};
};

#endif // WALL_H
