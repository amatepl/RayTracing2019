#ifndef GRAPHICSBUILDING_H
#define GRAPHICSBUILDING_H

#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <iostream>

#include "Product/graphicsproduct.h"

class GraphicsBuilding : public QGraphicsPolygonItem, public GraphicsProduct
{
public:
    GraphicsBuilding(QMenu *menuproduct, QGraphicsScene *scene);
    GraphicsBuilding(QPolygonF poly, QMenu *menuproduct, QGraphicsScene *scene);
    ~GraphicsBuilding() override;

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
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;

private:
    QGraphicsScene *m_scene;
    QVector<QPointF> m_extremities;
    std::string m_model;
    QMenu* m_productmenu;
};

#endif // GRAPHICSBUILDING_H
