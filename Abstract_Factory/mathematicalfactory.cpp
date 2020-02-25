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

void MathematicalFactory::receiveTreeProduct(TreeProduct *treeproduct, TreeProduct *graphic){
    m_graphiccomponent = dynamic_cast<GraphicsComponent*>(graphic);
    dynamic_cast<TreeProduct*>(m_graphiccomponent)->setPosX(treeproduct->getPosX());
    dynamic_cast<TreeProduct*>(m_graphiccomponent)->setPosY(treeproduct->getPosY());
}

void MathematicalFactory::receiveCarProduct(CarProduct *carproduct, CarProduct *graphic){
    m_graphiccomponent = dynamic_cast<GraphicsComponent*>(graphic);
    dynamic_cast<CarProduct*>(m_graphiccomponent)->setPosX(carproduct->getPosX());
    dynamic_cast<CarProduct*>(m_graphiccomponent)->setPosY(carproduct->getPosY());
    dynamic_cast<CarProduct*>(m_graphiccomponent)->setOrientation(carproduct->getOrientation());
    dynamic_cast<CarProduct*>(m_graphiccomponent)->setSpeed(carproduct->getSpeed());
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

TreeProduct* MathematicalFactory::createTreeProduct(){
    TreeProduct* graphic = dynamic_cast<TreeProduct*>(m_graphiccomponent);
    TreeProduct* tree  = new MathematicalTreeProduct(graphic,this);
    m_mathtrees.push_back(dynamic_cast<MathematicalTreeProduct*>(tree));
    return tree;
}

CarProduct* MathematicalFactory::createCarProduct(){
    CarProduct* graphic = dynamic_cast<CarProduct*>(m_graphiccomponent);
    CarProduct* car  = new MathematicalCarProduct(graphic,this);
    m_mathcars.push_back(dynamic_cast<MathematicalCarProduct*>(car));
    return car;
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
    case int(GraphicsComponent::TreeProduct):
        for (m_mathtreesiterator = m_mathtrees.begin(); m_mathtreesiterator != m_mathtrees.end(); ++m_mathtreesiterator){
            if (m_mathtrees.at(i)->getTreeProduct() == dynamic_cast<TreeProduct*>(m_graphiccomponent)){
                m_mathtrees.at(i)->setTreeProduct(dynamic_cast<TreeProduct*>(m_graphiccomponent));
                exist = true;
                break;
            }
            i++;
        }
        if (!exist){
            createTreeProduct();
        }
        break;
    case int(GraphicsComponent::CarProduct):
        for (m_mathcarsiterator = m_mathcars.begin(); m_mathcarsiterator != m_mathcars.end(); ++m_mathcarsiterator){
            if (m_mathcars.at(i)->getCarProduct() == dynamic_cast<CarProduct*>(m_graphiccomponent)){
                m_mathcars.at(i)->setCarProduct(dynamic_cast<CarProduct*>(m_graphiccomponent));
                exist = true;
                break;
            }
            i++;
        }
        if (!exist){
            createCarProduct();
        }
        break;
    }
}

void MathematicalFactory::updateNewProperties(GraphicsComponent *graphicscomponent){

}
