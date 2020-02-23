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
    GraphicsReceiverProduct(int posX, int posY, unsigned long frequency, bool enable
                               ,GraphicsFactory* graphicsfactory);
    ~GraphicsReceiverProduct() override;

    void enableReceiver(bool enable);
    QColor scaleColor(double min, double max, double value);
    static QPixmap getImage();

    int getType() override;
    bool graphicsSelected() override;
    void draw() override;

    int getPosX() override;
    int getPosY() override;
    double getPower() override;
    unsigned long getFrequency() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setFrequency(unsigned long frequency) override; 

private:
    GraphicsFactory *m_graphicsfactory;
    QRgb m_color;
    int m_posx,m_posy,m_sizex,m_sizey;
    double m_power, m_efield;
    unsigned long m_frequency;
};

#endif // GRAPHICSRECEIVERPRODUCT_H
