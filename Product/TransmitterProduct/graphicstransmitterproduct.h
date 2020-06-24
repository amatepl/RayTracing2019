#ifndef GRAPHICSTRANSMITTERPRODUCT_H
#define GRAPHICSTRANSMITTERPRODUCT_H
#include <iostream>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <vector>

#include "transmitterproduct.h"
#include "Product/graphicsproduct.h"


using namespace std;

class GraphicsTransmitterProduct :public QGraphicsPixmapItem, public GraphicsProduct
{
public:
    GraphicsTransmitterProduct(QMenu* productmenu, QGraphicsScene *scene);
    ~GraphicsTransmitterProduct() override;

    void drawRays(vector<GraphicsProduct*> rays);

    bool graphicsSelected() override;
    void draw() override;

    static QPixmap getImage();

    //int getModel() override;

    //void setModel(Model model) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QMenu* m_productmenu;
};

#endif // GRAPHICSTRANSMITTERPRODUCT_H
