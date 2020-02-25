#ifndef DIALOGCARPRODUCT_H
#define DIALOGCARPRODUCT_H

#include <QDialog>

#include "carproduct.h"
#include "Abstract_Factory/dialogfactory.h"

class DialogCarProduct: public QDialog, public CarProduct
{
    Q_OBJECT
public:
    DialogCarProduct(CarProduct* graphic, DialogFactory* dialogfactory);
    ~DialogCarProduct() override;

    void createDialog();

    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    double getSpeed() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setSpeed(double) override;

private:
    DialogFactory* m_dialogfactory;
    QSpinBox* m_posx;
    QSpinBox* m_posy;
    QDoubleSpinBox* m_orientation;
    QDoubleSpinBox* m_speed;

public slots:
    void newProperties();
};

#endif // DIALOGCARPRODUCT_H
