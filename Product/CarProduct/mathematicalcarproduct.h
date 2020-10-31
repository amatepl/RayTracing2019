#ifndef MATHEMATICALCARPRODUCT_H
#define MATHEMATICALCARPRODUCT_H

#include <QRectF>
#include <iostream>
#include <thread>

#include "carproduct.h"
#include "Product/mathematicalproduct.h"
#include "Product/BuildingProduct/building.h"
#include "dialogcarproduct.h"
#include "Share/moveablegraphics.h"

using namespace std;

class MathematicalCarProduct:public QObject, public Building,
                               /*  public MathematicalProduct,*/ public CarProduct
{
    Q_OBJECT

public:
    MathematicalCarProduct(QPolygonF rect, QPointF center);
    ~MathematicalCarProduct() override;

    void runCar();
    static void moveCar();
    void setRoad(QLineF *road);
    QLineF *getRoad();

    void setMovement(QLineF &road);
    QLineF getMovement();
    void setPos(QPointF pos);
    QPointF getPos() const;

    void attachObservable(GraphicsProduct* graphic)override;
    double getSpeed() override;
    double getOrientation() override;
    int getPosX() override;
    int getPosY() override;

    void setSpeed(double) override;
    void setOrientation(double orientation) override;
    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void update(QGraphicsItem *graphic) override;
    void openDialog(QWidget *) override;
    void newProperties() override;

private:
    QPointF m_center;
    QLineF m_movement;
    QLineF *m_street;

signals:
    void positionChanged(MathematicalCarProduct* poly,int x, int y, double orientation);
    void signal();
};

#endif // MATHEMATICALCARPRODUCT_H
