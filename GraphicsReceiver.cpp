#include "GraphicsReceiver.h"

GraphicsReceiver::GraphicsReceiver(QPointF pos, MovableObject *receiver):
    QGraphicsEllipseItem(pos.x(),pos.y(),5,5), m_receiver(receiver)
{
    QPen outlinePen(QColor(0, 0, 255, 255));
    outlinePen.setWidth(2);

    QBrush brush(Qt::blue);

    setBrush(brush);
    setPen(outlinePen);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QVariant GraphicsReceiver::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        m_receiver->moveToPosition(pos());
        //m_receiver->moveToPosition(scenePos());
    }
    return value;
}
