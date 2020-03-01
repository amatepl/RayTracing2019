#ifndef GRAPHICSTRANSMITTERPRODUCT_H
#define GRAPHICSTRANSMITTERPRODUCT_H
#include <iostream>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "transmitterproduct.h"
#include "Composite/graphicscomponent.h"
#include "Abstract_Factory/graphicsfactory.h"

class GraphicsFactory;

using namespace std;

class GraphicsTransmitterProduct :public QGraphicsPixmapItem, public TransmitterProduct,public GraphicsComponent
{
public:
    GraphicsTransmitterProduct(int posX, int posY, double orientation,double power, unsigned long frequency,QMenu* productmenu
                               ,GraphicsFactory* graphicsfactory);
    ~GraphicsTransmitterProduct() override;

    int getType() override;
    bool graphicsSelected() override;
    void draw() override;

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
    void setModel(Model model) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;


private:
    GraphicsFactory *m_graphicsfactory;
    int m_posx,m_posy;
    double m_orientation,m_power;
    unsigned long m_frequency;

    QMenu* m_productmenu;
};

#endif // GRAPHICSTRANSMITTERPRODUCT_H
