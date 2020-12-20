#ifndef CAR_H
#define CAR_H

#include <QRectF>
#include <iostream>
#include <thread>

#include "carproduct.h"
#include "Product/mathematicalproduct.h"
#include "Product/BuildingProduct/building.h"
#include "dialogcarproduct.h"
#include "Share/moveablegraphics.h"

using namespace std;

class Car:public QObject, public Building,
                               /*  public MathematicalProduct,*/ public CarProduct
{
    Q_OBJECT

public:
    Car(QPolygonF rect, QPointF center);
    ~Car() override;

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
    float getWidth() const;
    float getLength() const;
    QPointF topLeft() const;

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
    float m_width {1.8};
    float m_length {4};

signals:
    void positionChanged(Car* poly,int x, int y, double orientation);
    void signal();
};

#endif // MATHEMATICALCARPRODUCT_H
