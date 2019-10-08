#ifndef LINE_H
#define LINE_H

#include <QLineF>
#include <math.h>

class Line: public QLineF
{
public:
    Line(qreal x1, qreal y1, qreal x2, qreal y2);
    Line(const QPointF &p1,const QPointF &p2);
    double getAngleRad()const;
    double getSlope()const;

};

#endif // LINE_H
