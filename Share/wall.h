#ifndef WALL_H
#define WALL_H

#include <math.h>
#include "Share/line.h"
class MathematicalBuildingProduct;

class Wall: public Line
{
public:
    Wall(double x01 = 0 , double y01 = 0, double x02 = 0, double y02 = 0, double thickness = 0.0, double relEps = 0.0, double sig = 0.0, int indWall = 0);
    Wall(const QPointF &p1, const QPointF &p2, double thickness = 0.0, double relEps = 0.0, double sig = 0.0, int indWall = 0);
    ~Wall(void);

    enum typeWall{wall, front, back};

    /* Access */
    double getEpsilon() const {return m_epsilon;}
    double getSigma() const {return m_sigma;}
    double getThick() const {return m_thick;}
    int getIndWall() const {return m_indWall;}
    double getSpeed() const;
    double getOrientation() const;
    int getWallType() const;
    QLineF movement() const;
    QPointF otherPoint(const QPointF &point)const;
    MathematicalBuildingProduct* getBuilding()const {return m_building;}

    /* Modifiers */
    void setWallType(int type);
    void setSpeed(double speed);
    void setOrientation(double orientation);
    void setBuilding(MathematicalBuildingProduct *building) {m_building = building;}
    void setMovement(QLineF const movement);
    void setPoints(const QPointF &p0, const QPointF &p1);

    /* Miscellaneous */
    QPointF symetricalPoint(const QPointF &point); 
    QPointF farestExtrem(const QPointF &point) const;

private:
    double m_thick;
    double m_epsilon;
    double m_sigma;
    int m_indWall;
    MathematicalBuildingProduct *m_building;
    QLineF m_movement       {QLineF(.0,.0,.0,.0)};
    //double m_speed {0};
    //double m_orientation{0};
    int m_wallType{wall};
};

#endif // WALL_H
