#ifndef LINE_H
#define LINE_H

#include <QLineF>
#include <math.h>
#include <iostream>

class Line: public QLineF
{
public:
    Line(qreal x1, qreal y1, qreal x2, qreal y2);
    Line(const QPointF &p1,const QPointF &p2);
    double getAngleRad()const;
    double getSlope()const;
    QPointF symetricalPoint(const QPointF &point);
    QPointF symetricalPoint(const double x, const double y);
//    bool onLine(const QPointF &point);
    bool onLine(const QPointF &point, const double th=0.1);
    double getMeterLength()const;
    void setScale(float scale) {px_to_meter = scale;}

private:
    float px_to_meter;

};

#endif // LINE_H
