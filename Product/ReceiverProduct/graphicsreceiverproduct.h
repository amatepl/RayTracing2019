#ifndef GRAPHICSRECEIVERPRODUCT_H
#define GRAPHICSRECEIVERPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "receiverproduct.h"
#include "Composite/graphicscomponent.h"
#include "Abstract_Factory/graphicsfactory.h"

class GraphicsFactory;

class GraphicsReceiverProduct :public QGraphicsPixmapItem, public ReceiverProduct,public GraphicsComponent
{
public:
    GraphicsReceiverProduct(int posX, int posY, unsigned long frequency
                               ,GraphicsFactory* graphicsfactory);
    ~GraphicsReceiverProduct() override;

    virtual int getType() override;
    virtual bool graphicsSelected() override;
    virtual void draw() override;

    static QPixmap getImage();
    int getPosX() override;
    int getPosY() override;
    double getPower() override;
    unsigned long getFrequency() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setFrequency(unsigned long frequency) override;

private:
    GraphicsFactory *m_graphicsfactory;
    int m_posx,m_posy;
    double m_power;
    unsigned long m_frequency;
};

#endif // GRAPHICSRECEIVERPRODUCT_H
