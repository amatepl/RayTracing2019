#ifndef GRAPHICSBUILDINGPRODUCT_H
#define GRAPHICSBUILDINGPRODUCT_H

#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <iostream>

#include "Product/graphicsproduct.h"

class GraphicsBuildingProduct : public QGraphicsPolygonItem, public GraphicsProduct
{
public:
    GraphicsBuildingProduct(QMenu *menuproduct, QGraphicsScene *scene);
    GraphicsBuildingProduct(QPolygonF poly, QMenu *menuproduct, QGraphicsScene *scene);
    ~GraphicsBuildingProduct() override;

    static QPixmap getImage();
    QVector<QPointF> getExtremities() {return m_extremities;}
    void setExtremities(QVector<QPointF> extremities);
    void setModel(std::string model);
    std::string getModel() {return m_model;}

    // From GraphicsItem
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    // From GraphicsProduct
    bool graphicsSelected() override;
    void draw() override;
    void notifyToGraphic(QPolygonF *,int,int) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QVector<QPointF> m_extremities;
    std::string m_model;
    QMenu* m_productmenu;
};

#endif // GRAPHICSBUILDINGPRODUCT_H
