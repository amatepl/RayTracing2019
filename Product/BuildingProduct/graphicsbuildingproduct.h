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
    ~GraphicsBuildingProduct() override;

    static QPixmap getImage();

    bool graphicsSelected() override;
    void draw() override;
    QVector<QPointF> getExtremities();

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void setExtremities(QVector<QPointF> extremities);
    void setModel(std::string model);
    int getModel();

    void notifyToGraphic(QPolygonF *,int,int) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QVector<QPointF> m_extremities;
    //int m_posx,m_posy;
    //double m_orientation,m_permittivity,m_conductivity;
    //MathematicalComponent *m_mathematicalComponent;
    std::string m_model;
    QMenu* m_productmenu;
};

#endif // GRAPHICSBUILDINGPRODUCT_H
