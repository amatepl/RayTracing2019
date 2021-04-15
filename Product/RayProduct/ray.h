#ifndef RAY_H
#define RAY_H

#include <math.h>

#include <Share/line.h>
#include "Product/mathematicalproduct.h"
#include "Product/graphicsproduct.h"

using namespace std;

class Ray: public Line, public MathematicalProduct
{
private:
    int state;       // 0 for direct ray, 1 for transmitted ray, 2 for reflected ray, 3 for refracted ray

    // Coefficients

    double T;   // Transmission coefficient
    double G;   // Reflection coefficient

    int wallInd;
    double m_tetai ;
    double meterLength;
    int m_wallIBouncedOn;
    double m_theta;
    bool m_diffracted = false;
    double m_epsilonWall;

    void updateMeterLength();
public:
    Ray(const QPointF &p1 = QPointF(0,0), const QPointF &p2= QPointF(0,0), double Tetai = 0, const double epsilonWall = 5);
    ~Ray();

    /* Getters */
    double getCoefficient() const;
    int getWallInd() const;
    double getTetai() const;
    double getTheta() const;
    int getIndWall() const;
    bool getDiffracted() const;
    double getEpsilon() const;

    /* Modifiers */
    void setTetai(const double tetai);
    void setDiffracted(const bool diffracted);

    /* Utility */
    void draw();
    void erase();
    void update(QGraphicsItem *) override;

    /* Miscellaneous */
    MathematicalProduct* toMathematicalComponent();
    void openDialog(QWidget *) override;
};

#endif // RAY_H
