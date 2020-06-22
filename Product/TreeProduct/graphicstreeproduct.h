#ifndef GRAPHICSTREEPRODUCT_H
#define GRAPHICSTREEPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include "treeproduct.h"
#include "Composite/graphicscomponent.h"


class GraphicsTreeProduct: public QGraphicsPixmapItem, public TreeProduct,public GraphicsComponent
{
public:
    GraphicsTreeProduct(int posX, int posY, QMenu *productmenu, QGraphicsScene *scene);
    ~GraphicsTreeProduct() override;

    static QPixmap getImage();

    void draw() override;
    bool graphicsSelected() override;
    int getType() override;

    int getPosX() override;
    int getPosY() override;

    void setPosX(int) override;
    void setPosY(int) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void setMathematicalComponent(MathematicalComponent *mathematicalComponent) override;

    MathematicalComponent* toMathematicalComponent() override;

private:
    QGraphicsScene *m_scene;
    int m_posx,m_posy;
    MathematicalComponent *m_mathematicalComponent;

    QMenu *m_productmenu;
};

#endif // GRAPHICSTREEPRODUCT_H
