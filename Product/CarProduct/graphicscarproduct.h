#ifndef GRAPHICSCARPRODUCT_H
#define GRAPHICSCARPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include "Product/graphicsproduct.h"

class GraphicsCarProduct: public QGraphicsPixmapItem, public GraphicsProduct
{
public:
    GraphicsCarProduct(QMenu *productmenu, QGraphicsScene *scene);
    ~GraphicsCarProduct() override;

    static QPixmap getImage();

    bool graphicsSelected() override;
    void draw() override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void notifyToGraphic(QRectF *) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

public:
    QGraphicsScene* m_scene;
    QMenu *m_productmenu;
};

#endif // GRAPHICSCARPRODUCT_H
