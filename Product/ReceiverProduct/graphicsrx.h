#ifndef GRAPHICSRX_H
#define GRAPHICSRX_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>

#include "Product/graphicsproduct.h"

class GraphicsRx : public QGraphicsPixmapItem, public GraphicsProduct
{
public:
    GraphicsRx(bool enable, QMenu *menuproduct, QGraphicsScene *scene, QWidget *parent=nullptr);
    ~GraphicsRx() override;

    void enableReceiver(bool enable);
    QColor scaleColor(double min, double max, double value);
    static QPixmap getImage();

    bool graphicsSelected() override;
    void draw() override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void notifyToGraphic(QPointF *, float) override;
    void notifyToGraphic(QPointF *, double) override;

    void sendInformation() override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;

private:
//    QRgb m_color;
    QGraphicsScene *m_scene;
    QMenu *m_productmenu;
    int m_sizex, m_sizey; // Size of the cell if enable false
    QWidget *m_parent;
};
#endif // GRAPHICSRX_H
