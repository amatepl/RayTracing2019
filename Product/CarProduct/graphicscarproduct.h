#ifndef GRAPHICSCARPRODUCT_H
#define GRAPHICSCARPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "Abstract_Factory/graphicsfactory.h"
#include "Composite/graphicscomponent.h"
#include "carproduct.h"

class GraphicsCarProduct: public QGraphicsPixmapItem, public GraphicsComponent, public CarProduct
{
public:
    GraphicsCarProduct(int posX, int posY, double orientation, double speed, QMenu *productmenu,
                       GraphicsFactory *graphicsfactory);
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

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

public:
    GraphicsFactory* m_graphicsfactory;
    int m_posx, m_posy;
    double m_orientation, m_speed;

    QMenu *m_productmenu;
};

#endif // GRAPHICSCARPRODUCT_H
