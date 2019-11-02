#include "wallmodel.h"

WallModel::WallModel(int x1, int y1, int x2, int y2,
                     double relPerm, double cond) : QLine(x1,y1,x2,y2)
{
    m_doubleProperties = new map<string,double>;
    (*m_doubleProperties)["relative permittivity"] = relPerm;
    (*m_doubleProperties)["conductivity"] = cond;

    m_intProperties = new map<string,int>;
    (*m_intProperties)["x1"] = x1;
    (*m_intProperties)["y1"] = y1;
    (*m_intProperties)["x2"] = x2;
    (*m_intProperties)["y2"] = y2;
    (*m_intProperties)["type"] = 3;
}

map<string,int>* WallModel::getIntValues(){
    return m_intProperties;
}

void WallModel::setIntValues(map<string,int>* values){
    m_intProperties = values;
}

map<string,double>* WallModel::getDoubleValues()
{
    return m_doubleProperties;
}

void WallModel::setDoubleValues(map<string,double>* values)
{
    m_doubleProperties = values;
}

