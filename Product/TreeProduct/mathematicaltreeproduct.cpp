#include "mathematicaltreeproduct.h"

MathematicalTreeProduct::MathematicalTreeProduct(QVector<QPointF> points) : QPolygonF(points)
{
    m_extremities = points;
    m_type = "Tree";
}

MathematicalTreeProduct::~MathematicalTreeProduct(){

}

void MathematicalTreeProduct::update(QGraphicsItem *graphic){

}

void MathematicalTreeProduct::openDialog(){

}
