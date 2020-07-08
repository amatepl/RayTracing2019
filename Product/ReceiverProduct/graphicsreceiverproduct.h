#ifndef GRAPHICSRECEIVERPRODUCT_H
#define GRAPHICSRECEIVERPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>

#include "Product/graphicsproduct.h"

class GraphicsReceiverProduct : public QGraphicsPixmapItem, public GraphicsProduct
{
public:
    GraphicsReceiverProduct(bool enable, QMenu *menuproduct, QGraphicsScene *scene);
    ~GraphicsReceiverProduct() override;

    void enableReceiver(bool enable);
    QColor scaleColor(double min, double max, double value);
    static QPixmap getImage();

    bool graphicsSelected() override;
    void draw() override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void notifyToGraphic(QPointF *) override;
    void notifyToGraphic(QPointF *, double) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QRgb m_color;
    QGraphicsScene *m_scene;
    QMenu *m_productmenu;
    int m_sizex, m_sizey; // Size of the cell if enable false
};
#endif // GRAPHICSRECEIVERPRODUCT_H
