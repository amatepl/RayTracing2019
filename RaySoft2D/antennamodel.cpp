#include "antennamodel.h"

AntennaModel::AntennaModel(int x, int y, int width, int height) : QRect(x,y,width,height)
{
    m_intProperties = new map<string,int>;
    (*m_intProperties)["orientation"] = 90;
    (*m_intProperties)["x center"] = x + lround(width/2);
    (*m_intProperties)["y center"] = y + lround(height/2);
    (*m_intProperties)["width"] = width;
    (*m_intProperties)["height"] = height;
}


map<string,int>* AntennaModel::getIntValues(){
    return m_intProperties;
}

void AntennaModel::setIntValues(map<string,int>* values){
    m_intProperties = values;
}

map<string,double>* AntennaModel::getDoubleValues()
{

}
void AntennaModel::setDoubleValues(map<string,double>* values)
{

}
