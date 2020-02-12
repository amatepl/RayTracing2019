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

TransmitterProduct* DialogFactory::createTransmitterProduct(){
    TransmitterProduct* graphic = dynamic_cast<TransmitterProduct*>(m_graphiccomponent);
    TransmitterProduct* dialog  = new DialogTransmitterProduct(graphic,this);
    return dialog;
}

ReceiverProduct* DialogFactory::createReceiverProduct(){
    /*
    ReceiverProduct* graphic = dynamic_cast<ReceiverProduct*>(m_graphiccomponent);
    ReceiverProduct* dialog  = new DialogReceiverProduct(graphic,this);
    return dialog;*/
}

void DialogFactory::update(GraphicsComponent* graphicscomponent){
    m_graphiccomponent = graphicscomponent;
    switch(int (m_graphiccomponent->getType())){
        case int(GraphicsComponent::TransmitterProduct):
            createTransmitterProduct();
            break;
    }
}
