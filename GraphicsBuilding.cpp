#include "GraphicsBuilding.h"

GraphicsBuilding::GraphicsBuilding(const QRectF &rect, MovableObject *building): QGraphicsRectItem(rect)
{
    m_building = building;
    QPen outlinePen(QColor(0, 0, 0, 255));
    outlinePen.setWidth(2);

    QBrush brush(Qt::BDiagPattern);

    setBrush(brush);
    setPen(outlinePen);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

GraphicsBuilding::GraphicsBuilding(qreal x, qreal y, qreal width, qreal height, MovableObject *building): QGraphicsRectItem(x,y,width,height)
{
    m_building = building;
    QPen outlinePen(QColor(0, 0, 0, 255));
    outlinePen.setWidth(2);

    QBrush brush(Qt::BDiagPattern);

    setBrush(brush);
    setPen(outlinePen);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

GraphicsBuilding::~GraphicsBuilding(void){}

QVariant GraphicsBuilding::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {

//        foreach (Arrow *arrow, arrows) {
//            arrow->updatePosition();
//        }
        //cout<<"ScenePos() x: "<<mapToScene(QPointF(0,0)).x()<<" y: "<<scenePos().y()<<endl;
        //m_building->moveToPosition(scenePos());
        //m_building->moveToPosition(mapToScene(QPointF(0,0)));
        m_building->moveToPosition(pos());

    }

    return value;
}
