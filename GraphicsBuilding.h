#ifndef GRAPHICSBUILDIING_H
#define GRAPHICSBUILDIING_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <iostream>
#include "MovableObject.h"


using namespace std;


class GraphicsBuilding: public QGraphicsRectItem
{
public:
    GraphicsBuilding(const QRectF &rect, MovableObject *building);
    GraphicsBuilding(qreal x, qreal y, qreal width, qreal height, MovableObject *building);
    ~GraphicsBuilding(void);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

private:

    MovableObject *m_building;
};

#endif // GRAPHICSBUILDIING_H
