#ifndef DIALOGFACTORY_H
#define DIALOGFACTORY_H

#include "scenefactory.h"
#include "Observer/sceneobserver.h"
#include "Observer/sceneobservable.h"
#include "Product/TransmitterProduct/transmitterproduct.h"
#include "Product/BuildingProduct/buildingproduct.h"
#include "Product/TransmitterProduct/dialogtransmitterproduct.h"
#include "Product/ReceiverProduct/dialogreceiverproduct.h"
#include "Product/BuildingProduct/dialogbuildingproduct.h"
#include "Product/TreeProduct/dialogtreeproduct.h"
#include "Product/CarProduct/dialogcarproduct.h"
#include "Product/graphicsproduct.h"

class DialogFactory : public SceneFactory, public SceneObserver
{
public:
    DialogFactory(SceneObservable *graphicsfactory);
    ~DialogFactory() override;

    void receiveTransmitterProduct(TransmitterProduct* transmitterproduct);
    void receiveBuildingProduct(BuildingProduct* buildingproduct);
    void receiveReceiverProduct(ReceiverProduct* receiverproduct);
    void receiveTreeProduct(TreeProduct* treeproduct);
    void receiveCarProduct(CarProduct* carproduct);

    void updateNewProperties(GraphicsProduct*) override;
    void updateChangeProperties(GraphicsProduct*) override;

private:
    SceneObservable *m_graphicsfactory;
    GraphicsProduct *m_graphiccomponent;
};

#endif // DIALOGFACTORY_H
