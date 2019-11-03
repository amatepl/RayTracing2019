#include "model/buildingmodel.h"

BuildingModel::BuildingModel(int x, int y, int width, int height,
                             double relPerm, double cond) : QRect(x,y,width,height)
{
    m_doubleProperties = new map<string,double>;
    (*m_doubleProperties)["relative permittivity"] = relPerm;
    (*m_doubleProperties)["conductivity"] = cond;

    m_intProperties = new map<string,int>;
    (*m_intProperties)["top left x"] = x;
    (*m_intProperties)["top left y"] = y;
    (*m_intProperties)["width"] = width;
    (*m_intProperties)["height"] = height;
    (*m_intProperties)["orientation"] = 0;
    (*m_intProperties)["type"] = 3;
}

BuildingModel::BuildingModel(int x, int y, int width, int height, int type) : QRect(x,y,width,height)
{
    m_doubleProperties = new map<string,double>;
    switch (type){
        case 1 :
            (*m_doubleProperties)["relative permittivity"] = 5.0;
            (*m_doubleProperties)["conductivity"] = 0.014;
            break;
        case 2 :
            (*m_doubleProperties)["relative permittivity"] = 4.6;
            (*m_doubleProperties)["conductivity"] = 0.0014;
            break;
        case 3 :
            (*m_doubleProperties)["relative permittivity"] = 0.0;
            (*m_doubleProperties)["conductivity"] = 0.0;
    }

    m_intProperties = new map<string,int>;
    (*m_intProperties)["top left x"] = x;
    (*m_intProperties)["top left y"] = y;
    (*m_intProperties)["width"] = width;
    (*m_intProperties)["height"] = height;
    (*m_intProperties)["orientation"] = 0;
    (*m_intProperties)["type"] = type;
}

BuildingModel::~BuildingModel(){
    cout << "Building model has been removed" << endl;
}

map<string,int>* BuildingModel::getIntValues(){
    return m_intProperties;
}

void BuildingModel::setIntValues(map<string,int>* values){
    m_intProperties = values;
}

map<string,double>* BuildingModel::getDoubleValues()
{
    return m_doubleProperties;
}

void BuildingModel::setDoubleValues(map<string,double>* values)
{
    m_doubleProperties = values;
}
