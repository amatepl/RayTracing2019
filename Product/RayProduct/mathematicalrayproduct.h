#ifndef MATHEMATICALRAYPRODUCT_H
#define MATHEMATICALRAYPRODUCT_H

#include <math.h>

#include <Share/line.h>
#include "Composite/MathematicalComponent.h"

using namespace std;

class MathematicalRayProduct: public Line, public MathematicalComponent
{
private:
    int state;       // 0 for direct ray, 1 for transmitted ray, 2 for reflected ray, 3 for refracted ray

    // Coefficients

    double T;   // Transmission coefficient
    double G;   // Reflection coefficient

    int wallInd;
    double m_tetai ;
    double meterLength;
    int wallIBouncedOn;
    double theta;
    bool m_diffracted;

    //std::vector <Wall*> walls_intersected;   // Pas la meilleure approche, trop à enregsitrer.

    void updateMeterLength();
public:
    MathematicalRayProduct(const QPointF &p1 = QPointF(0,0), const QPointF &p2= QPointF(0,0), double Tetai = 0, int indWall = 0);

    double getCoefficient()const;
    int getWallInd()const;
    //void setCoefficient(double iAngle, Wall& inWall);
    double getTetai()const;
    void setTetai(double tetai);
    double getTheta()const;
    double getMeterLength()const;
    int getIndWall()const;
    void setDiffracted(bool diffracted);

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    int getPosX() override;
    int getPosY() override;
    virtual MathematicalComponent* toMathematicalComponent() = 0;

};

#endif // MATHEMATICALRAYPRODUCT_H
