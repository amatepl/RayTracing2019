#ifndef ANTENAIMAGE_H
#define ANTENAIMAGE_H

#include <QPointF>
#include <QLineF>
#include <QPolygonF>

class AntenaImage : public QPointF
{
public:
    AntenaImage(const QPointF &pos, const QLineF &wall);
    QPolygonF getIlluminationZone()const;

private:
    QLineF m_wall;
};

#endif // ANTENAIMAGE_H
