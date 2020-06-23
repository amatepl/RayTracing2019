#ifndef GRAPHICSTRANSMITTERPRODUCT_H
#define GRAPHICSTRANSMITTERPRODUCT_H
#include <iostream>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <vector>

#include "transmitterproduct.h"
#include "Composite/graphicscomponent.h"

//class GraphicsFactory;

using namespace std;

class GraphicsTransmitterProduct :public QGraphicsPixmapItem, /*public TransmitterProduct,*/public GraphicsComponent
{
public:
    GraphicsTransmitterProduct(int posX, int posY, double orientation,QMenu* productmenu,
                               QGraphicsScene *scene);
    ~GraphicsTransmitterProduct() override;

    void drawRays(vector<GraphicsComponent*> rays);

    int getType() override;
    bool graphicsSelected() override;
    void draw() override;

    static QPixmap getImage();
    int getPosX() override;
    int getPosY() override;

    //int getModel() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;

    //void setModel(Model model) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void setMathematicalComponent(MathematicalComponent *mathematicalComponent) override;

    MathematicalComponent* toMathematicalComponent() override;

private:
    int m_posx,m_posy;
    double m_orientation;
    QGraphicsScene *m_scene;
    MathematicalComponent *m_mathematicalComponent;

    QMenu* m_productmenu;
};

#endif // GRAPHICSTRANSMITTERPRODUCT_H
