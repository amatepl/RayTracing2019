#include "mathematicalbuildingproduct.h"

MathematicalBuildingProduct::MathematicalBuildingProduct(BuildingProduct* graphic) : QPolygonF(){
    //m_mathematicalfactory = mathematicalFactory;
    setBuildingProduct(graphic);
}

MathematicalBuildingProduct::~MathematicalBuildingProduct(){

}

void MathematicalBuildingProduct::newProperties(){
    //m_mathematicalfactory->receiveBuildingProduct(this,m_graphic);
}

int MathematicalBuildingProduct::getPosX(){
    return m_posx;
}

int MathematicalBuildingProduct::getPosY(){
    return m_posy;
}

double MathematicalBuildingProduct::getOrientation(){
    return m_orientation;
    setOrientation(m_orientation);
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

BuildingProduct* MathematicalBuildingProduct::getBuildingProduct(){
    return m_graphic;
}

void MathematicalBuildingProduct::setPosX(int posX){
    m_posx = posX;
}
void MathematicalBuildingProduct::setPosY(int posY){
    m_posy = posY;
}
void MathematicalBuildingProduct::setOrientation(double orientation){
    m_orientation = orientation;
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

void MathematicalBuildingProduct::setBuildingProduct(BuildingProduct* graphic){
    m_graphic = graphic;
    setPosX(graphic->getPosX());
    setPosY(graphic->getPosY());
    setOrientation(graphic->getOrientation());
    setModel(graphic->getModel());
    setExtremities(graphic->getExtremities());
}

MathematicalComponent* MathematicalBuildingProduct::toMathematicalComponent(){
    return this;
}
