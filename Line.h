#ifndef LINE_H
#define LINE_H

#include <QLineF>

class Line: public QLineF
{
public:
    Line(qreal x1, qreal y1, qreal x2, qreal y2);
    double getAngleRad()const;
    double getSlope()const;

};

#endif // LINE_H
