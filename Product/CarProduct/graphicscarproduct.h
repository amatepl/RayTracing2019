#ifndef GRAPHICSCARPRODUCT_H
#define GRAPHICSCARPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include "Composite/graphicscomponent.h"
#include "carproduct.h"

class GraphicsCarProduct: public QGraphicsPixmapItem, public GraphicsComponent, public CarProduct
{
public:
    GraphicsCarProduct(int posX, int posY, double orientation, double speed, QMenu *productmenu,
                       QGraphicsScene *scene);
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

    void setMathematicalComponent(MathematicalComponent *mathematicalComponent) override;

    MathematicalComponent* toMathematicalComponent() override;

public:
    QGraphicsScene* m_scene;
    int m_posx, m_posy;
    double m_orientation, m_speed;
    MathematicalComponent *m_mathematicalComponent;

    QMenu *m_productmenu;
};

#endif // GRAPHICSCARPRODUCT_H
