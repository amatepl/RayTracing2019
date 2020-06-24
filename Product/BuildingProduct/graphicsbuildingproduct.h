#ifndef GRAPHICSBUILDINGPRODUCT_H
#define GRAPHICSBUILDINGPRODUCT_H

#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>

#include "Product/graphicsproduct.h"

class GraphicsBuildingProduct : public QGraphicsPolygonItem, public GraphicsProduct
{
    enum Model{brick,concrete,none};
public:
    GraphicsBuildingProduct(QMenu *menuproduct, QGraphicsScene *scene);
    ~GraphicsBuildingProduct() override;

    static QPixmap getImage();

    bool graphicsSelected() override;
    void draw() override;
    /*
    int getType() override;
    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    double getConductivity() override;
    double getPermittivity() override;
    QVector<QPointF> getExtremities() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setConductivity(double sigma) override;
    void setPermittivity(double eps) override;
    */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void setExtremities(QVector<QPointF> extremities);
    void setModel(int model);
    int getModel();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QVector<QPointF> m_extremities;
    Model m_model;
    //int m_posx,m_posy;
    //double m_orientation,m_permittivity,m_conductivity;
    //MathematicalComponent *m_mathematicalComponent;

    QMenu* m_productmenu;
};

#endif // GRAPHICSBUILDINGPRODUCT_H
