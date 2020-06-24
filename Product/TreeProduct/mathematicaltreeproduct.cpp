#include "mathematicaltreeproduct.h"

MathematicalTreeProduct::MathematicalTreeProduct(QVector<QPointF> points) : QPolygonF(points)
{
    m_extremities = points;
}

MathematicalTreeProduct::~MathematicalTreeProduct(){

}

void MathematicalTreeProduct::update(QGraphicsItem *graphic){

}
