#ifndef GRAPHICSTREEPRODUCT_H
#define GRAPHICSTREEPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include "treeproduct.h"
#include "Product/graphicsproduct.h"


class GraphicsTreeProduct: public QGraphicsPixmapItem, public GraphicsProduct
{
public:
    GraphicsTreeProduct(QMenu *productmenu, QGraphicsScene *scene);
    ~GraphicsTreeProduct() override;

    static QPixmap getImage();

    void draw() override;
    bool graphicsSelected() override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QMenu *m_productmenu;
};

#endif // GRAPHICSTREEPRODUCT_H
