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


void MathematicalFactory::receiveReceiverProduct(ReceiverProduct *buildingproduct, ReceiverProduct *graphic){
    m_graphiccomponent = dynamic_cast<GraphicsComponent*>(graphic);
    dynamic_cast<ReceiverProduct*>(m_graphiccomponent)->setPosX(buildingproduct->getPosX());
    dynamic_cast<ReceiverProduct*>(m_graphiccomponent)->setPosY(buildingproduct->getPosY());
}

TransmitterProduct* MathematicalFactory::createTransmitterProduct(){

}

ReceiverProduct* MathematicalFactory::createReceiverProduct(){
    ReceiverProduct* graphic = dynamic_cast<ReceiverProduct*>(m_graphiccomponent);
    ReceiverProduct* receiver  = new MathematicalReceiverProduct(graphic,this);
    m_mathreceivers.push_back(dynamic_cast<MathematicalReceiverProduct*>(receiver));
    return receiver;
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
    case int(GraphicsComponent::ReceiverProduct):
        for (m_mathreceiversiterator = m_mathreceivers.begin(); m_mathreceiversiterator != m_mathreceivers.end(); ++m_mathreceiversiterator){
            if (m_mathreceivers.at(i)->getReceiverProduct() == dynamic_cast<ReceiverProduct*>(m_graphiccomponent)){
                m_mathreceivers.at(i)->setReceiverProduct(dynamic_cast<ReceiverProduct*>(m_graphiccomponent));
                exist = true;
                break;
            }
            i++;
        }
        if (!exist){
            createReceiverProduct();
        }
        break;
    }
}

void MathematicalFactory::updateNewProperties(GraphicsComponent *graphicscomponent){

}
