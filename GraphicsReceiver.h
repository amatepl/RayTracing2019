#ifndef GRAPHICSRECEIVER_H
#define GRAPHICSRECEIVER_H

#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include <iostream>
#include "MovableObject.h"
#include <QPointF>


class GraphicsReceiver: public QGraphicsEllipseItem
{
public:
    GraphicsReceiver(QPointF pos, MovableObject *receiver);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

private:
    MovableObject* m_receiver;
};

#endif // GRAPHICSRECEIVER_H
