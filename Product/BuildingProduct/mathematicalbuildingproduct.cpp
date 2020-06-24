#include "mathematicalbuildingproduct.h"

MathematicalBuildingProduct::MathematicalBuildingProduct(QVector<QPointF> points) : QPolygonF(points){
    //m_mathematicalfactory = mathematicalFactory;
    m_extremities = points;
    setModel("concrete");
    m_type = "Building";
}

MathematicalBuildingProduct::~MathematicalBuildingProduct(){

}

void MathematicalBuildingProduct::setExtremities(QVector<QPointF> extremities){
    m_extremities = extremities;
    QPolygonF poly = QPolygonF(m_extremities);
    swap(poly);
}

void MathematicalBuildingProduct::setModel(std::string model){
    m_model = model;
    if (model == "brick"){
        m_conductivity = 0.0014;
        m_permittivity = 4.6;
    }
    else if (model == "concrete"){
        m_conductivity = 0.014;
        m_permittivity = 5.0;
    }
}

void MathematicalBuildingProduct::update(QGraphicsItem *graphic){
    setPosX(graphic->x());
    setPosY(graphic->y());
}

void MathematicalBuildingProduct::openDialog(){
    new DialogBuildingProduct(this);
}

void MathematicalBuildingProduct::newProperties(){
    m_graphic->notifyToGraphic(this,m_posx,m_posy);
}
