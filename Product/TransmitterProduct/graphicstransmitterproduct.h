#ifndef GRAPHICSTRANSMITTERPRODUCT_H
#define GRAPHICSTRANSMITTERPRODUCT_H
#include <iostream>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "transmitterproduct.h"
#include "Composite/graphicscomponent.h"
#include "Abstract_Factory/graphicsfactory.h"

class GraphicsFactory;

using namespace std;

class GraphicsTransmitterProduct :public QGraphicsPixmapItem, public TransmitterProduct,public GraphicsComponent
{
public:
    GraphicsTransmitterProduct(int posX, int posY, double orientation,double power, unsigned long frequency
                               ,GraphicsFactory* graphicsfactory);
    ~GraphicsTransmitterProduct() override;

    virtual int getType() override;
    virtual bool graphicsSelected() override;
    virtual void draw() override;

    static QPixmap getImage();
    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    double getPower() override;
    unsigned long getFrequency() override;
    int getRow() override;
    int getColumn() override;
    double getAntennaDistance() override;
    int getModel() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setPower(double power) override;
    void setFrequency(unsigned long frequency) override;
    void setRow(int row) override;
    void setColumn(int column) override;
    void setAntennaDistance(double distance) override;
    virtual void setModel(Model model) override;


private:
    GraphicsFactory *m_graphicsfactory;
    int m_posx,m_posy;
    double m_orientation,m_power;
    unsigned long m_frequency;
};

#endif // GRAPHICSTRANSMITTERPRODUCT_H
