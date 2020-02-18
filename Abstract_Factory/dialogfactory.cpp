#include "dialogfactory.h"

DialogFactory::DialogFactory(SceneObservable *graphicsfactory)
{
    m_graphicsfactory = graphicsfactory;
}

DialogFactory::~DialogFactory(){

}

void DialogFactory::receiveTransmitterProduct(TransmitterProduct* transmitterproduct){
    dynamic_cast<TransmitterProduct*>(m_graphiccomponent)->setPosX(transmitterproduct->getPosX());
    dynamic_cast<TransmitterProduct*>(m_graphiccomponent)->setPosY(transmitterproduct->getPosY());
    dynamic_cast<TransmitterProduct*>(m_graphiccomponent)->setOrientation(transmitterproduct->getOrientation());
    dynamic_cast<TransmitterProduct*>(m_graphiccomponent)->setFrequency(transmitterproduct->getFrequency());
    dynamic_cast<TransmitterProduct*>(m_graphiccomponent)->setPower(transmitterproduct->getPower());
}

void DialogFactory::receiveBuildingProduct(BuildingProduct* buildingproduct){
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setPosX(buildingproduct->getPosX());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setPosY(buildingproduct->getPosY());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setConductivity(buildingproduct->getConductivity());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setPermittivity(buildingproduct->getPermittivity());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setModel(buildingproduct->getModel());
    dynamic_cast<BuildingProduct*>(m_graphiccomponent)->setExtremities(buildingproduct->getExtremities());
}

TransmitterProduct* DialogFactory::createTransmitterProduct(){
    TransmitterProduct* graphic = dynamic_cast<TransmitterProduct*>(m_graphiccomponent);
    TransmitterProduct* dialog  = new DialogTransmitterProduct(graphic,this);
    return dialog;
}

ReceiverProduct* DialogFactory::createReceiverProduct(){

}

BuildingProduct* DialogFactory::createBuildingProduct(){
    BuildingProduct* graphic = dynamic_cast<BuildingProduct*>(m_graphiccomponent);
    BuildingProduct* dialog  = new DialogBuildingProduct(graphic,this);
    return dialog;
}

void DialogFactory::updateNewProperties(GraphicsComponent* graphicscomponent){
    m_graphiccomponent = graphicscomponent;
    switch(int (m_graphiccomponent->getType())){
        case int(GraphicsComponent::TransmitterProduct):
            createTransmitterProduct();
            break;
        case int(GraphicsComponent::BuildingProduct):
            createBuildingProduct();
            break;
    }
}

void DialogFactory::updateChangeProperties(GraphicsComponent* graphicscomponent){

}
