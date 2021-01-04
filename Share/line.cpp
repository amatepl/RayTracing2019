#include "line.h"

Line::Line(qreal x1, qreal y1, qreal x2, qreal y2): QLineF(x1, y1, x2, y2)
{

}

Line::Line(const QPointF &p1, const QPointF &p2): QLineF(p1, p2)
{

}

double Line::getAngleRad() const
{
    double angle_in_radians;
    if (angle() > 180) {
        angle_in_radians = (angle() - 180)*M_PI/180;
    } else
        angle_in_radians = angle()*M_PI/180;
    return angle_in_radians;
}

double Line::getSlope() const
{
    double slope;
    if (dx() != 0) {
        slope = dy()/dx();
    } else
        if (dy() > 0) {
            slope = -INFINITY;
        }
        else
            slope = INFINITY;
    return slope;
}

QPointF Line::symetricalPoint(const QPointF &point) {

//    qreal ray_vector_length = sqrt(pow(point.y() - y2(), 2) + pow(point.x() - x2(), 2));
//    qreal virtual_slope;

//    if (point.y() - y2() < 0 && point.x() - x2()){
//        virtual_slope = -acos((point.x() - x2())/ray_vector_length);
//    } else {
//        virtual_slope = acos((point.x() - x2())/ray_vector_length);
//    }

//    qreal ray_slope = 2*getAngleRad() - virtual_slope;
//    qreal ray_vector[2] ={cos(ray_slope), sin(ray_slope)};
//    qreal x2 = ray_vector_length * ray_vector[0];
//    qreal y2 = ray_vector_length * ray_vector[1];
//    qreal transmitterImagePosX = this->x2() + x2;
//    qreal transmitterImagePosY = this->y2() + y2;
//    return QPointF(transmitterImagePosX, transmitterImagePosY);

    QLineF finalVector(p1(), point);
    double theta = angleTo(finalVector);
    finalVector.setAngle(angle() - theta);
    return finalVector.p2();


}

QPointF Line::symetricalPoint(const double x, const double y){

    qreal ray_vector_length = sqrt(pow(y - y2(), 2) + pow(x - x2(), 2));
    qreal virtual_slope;

    if (y - y2() < 0 && x - x2()) {
        virtual_slope = -acos((x - x2())/ray_vector_length);
    } else {
        virtual_slope = acos((x - x2())/ray_vector_length);
    }

    qreal ray_slope = 2*getAngleRad() - virtual_slope;
    qreal ray_vector[2] ={cos(ray_slope) , sin(ray_slope)};
    qreal x2 = ray_vector_length * ray_vector[0];
    qreal y2 = ray_vector_length * ray_vector[1];
    qreal transmitterImagePosX = this->x2() + x2;
    qreal transmitterImagePosY = this->y2() + y2;

    return QPointF(transmitterImagePosX, transmitterImagePosY);
}

bool Line::onLine(const QPointF &point)
{
    /*
     * Check if the given point is on the line.
     *
     */

    QLineF testLine1(point,p2());
    QLineF testLine2(point,p1());

    return (intersects(testLine1,nullptr) == 0
            && testLine1.length() <= length()
            && testLine2.length() <= length());
}

double Line::getMeterLength() const
{
    return length()*px_to_meter;
}
