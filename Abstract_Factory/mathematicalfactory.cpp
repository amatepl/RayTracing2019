#include "mathematicalfactory.h"

MathematicalFactory::MathematicalFactory(SceneObservable *graphicsfactory)
{
    m_graphicsfactory = graphicsfactory;
}

MathematicalFactory::~MathematicalFactory(){

}

void MathematicalFactory::receiveBuildingProduct(BuildingProduct *buildingproduct, BuildingProduct *graphic){
    m_graphiccomponent = dynamic_cast<GraphicsComponent*>(graphic);
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setPosX(buildingproduct->getPosX());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setPosY(buildingproduct->getPosY());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setConductivity(buildingproduct->getConductivity());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setPermittivity(buildingproduct->getPermittivity());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setModel(buildingproduct->getModel());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setExtremities(buildingproduct->getExtremities());
}

TransmitterProduct* MathematicalFactory::createTransmitterProduct(){

}

ReceiverProduct* MathematicalFactory::createReceiverProduct(){

}

BuildingProduct* MathematicalFactory::createBuildingProduct(){
    BuildingProduct* graphic = dynamic_cast<BuildingProduct*>(m_graphiccomponent);
    BuildingProduct* building  = new MathematicalBuildingProduct(graphic,this);
    m_mathbuildings.push_back(dynamic_cast<MathematicalBuildingProduct*>(building));
    return building;
}

void MathematicalFactory::updateChangeProperties(GraphicsComponent* graphicscomponent){
    m_graphiccomponent = graphicscomponent;
    unsigned long long i = 0;
    bool exist = false;
    switch(int (m_graphiccomponent->getType())){
    case int(GraphicsComponent::BuildingProduct):
        for (m_mathbuildingsiterator = m_mathbuildings.begin(); m_mathbuildingsiterator != m_mathbuildings.end(); ++m_mathbuildingsiterator){
            if (m_mathbuildings.at(i)->getBuildingProduct() == dynamic_cast<BuildingProduct*>(m_graphiccomponent)){
                m_mathbuildings.at(i)->setBuildingProduct(dynamic_cast<BuildingProduct*>(m_graphiccomponent));
                exist = true;
                break;
            }
            i++;
        }
        if (!exist){
            createBuildingProduct();
        }
        break;
    case int(GraphicsComponent::TransmitterProduct):
        createTransmitterProduct();
        break;
    }
}

void MathematicalFactory::updateNewProperties(GraphicsComponent *graphicscomponent){

}
