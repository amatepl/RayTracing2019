#ifndef GRAPHICSCARPRODUCT_H
#define GRAPHICSCARPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include "Product/graphicsproduct.h"
#include "Share/moveablegraphics.h"

class GraphicsCarProduct:public MoveableGraphics, public GraphicsProduct, public QGraphicsPixmapItem
{
public:
    GraphicsCarProduct(QMenu *productmenu, QGraphicsScene *scene);
    ~GraphicsCarProduct() override;

    static QPixmap getImage();

    bool graphicsSelected() override;
    void draw() override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

public:
    QGraphicsScene* m_scene;
    QMenu *m_productmenu;

public slots:
    void notifyToGraphicSig(QPolygonF *, int, int, double) override;




};

#endif // GRAPHICSCARPRODUCT_H
