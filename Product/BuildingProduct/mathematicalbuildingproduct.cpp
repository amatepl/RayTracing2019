#include "mathematicalbuildingproduct.h"

MathematicalBuildingProduct::MathematicalBuildingProduct(QVector<QPointF> points) : QPolygonF(points){
    //m_mathematicalfactory = mathematicalFactory;
    m_extremities = points;
}

MathematicalBuildingProduct::~MathematicalBuildingProduct(){

}

double MathematicalBuildingProduct::getConductivity(){
    return m_conductivity;
}

double MathematicalBuildingProduct::getPermittivity(){
    return m_permittivity;
}

int MathematicalBuildingProduct::getModel(){
    return int(m_model);
}

QVector<QPointF> MathematicalBuildingProduct::getExtremities(){
    return m_extremities;
}

void MathematicalBuildingProduct::setConductivity(double sigma){
    m_conductivity = sigma;
}
void MathematicalBuildingProduct::setPermittivity(double eps){
    m_permittivity = eps;
}

void MathematicalBuildingProduct::setModel(int model){

}

void MathematicalBuildingProduct::setExtremities(QVector<QPointF> extremities){
    m_extremities = extremities;
    QPolygonF poly = QPolygonF(m_extremities);
    swap(poly);
}

void MathematicalBuildingProduct::update(QGraphicsItem *graphic){

}
