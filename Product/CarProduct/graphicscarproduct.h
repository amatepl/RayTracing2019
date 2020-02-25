#ifndef GRAPHICSCARPRODUCT_H
#define GRAPHICSCARPRODUCT_H

#include <QGraphicsPixmapItem>

#include "Abstract_Factory/graphicsfactory.h"
#include "Composite/graphicscomponent.h"
#include "carproduct.h"

class GraphicsCarProduct: public QGraphicsPixmapItem, public GraphicsComponent, public CarProduct
{
public:
    GraphicsCarProduct(int posX, int posY, double orientation, double speed, GraphicsFactory *graphicsfactory);
    ~GraphicsCarProduct() override;

    static QPixmap getImage();

    int getType() override;
    bool graphicsSelected() override;
    void draw() override;

    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    double getSpeed() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double) override;
    void setSpeed(double) override;

public:
    GraphicsFactory* m_graphicsfactory;
    int m_posx, m_posy;
    double m_orientation, m_speed;

};

#endif // GRAPHICSCARPRODUCT_H
