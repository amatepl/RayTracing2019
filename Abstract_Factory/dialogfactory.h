#ifndef DIALOGFACTORY_H
#define DIALOGFACTORY_H

#include "scenefactory.h"
#include "Observer/sceneobserver.h"
#include "Observer/sceneobservable.h"
#include "Product/TransmitterProduct/transmitterproduct.h"
#include "Product/TransmitterProduct/dialogtransmitterproduct.h"
#include "Composite/graphicscomponent.h"

class DialogFactory : public SceneFactory, public SceneObserver
{
public:
    DialogFactory(SceneObservable *graphicsfactory);
    ~DialogFactory() override;

    void receiveTransmitterProduct(TransmitterProduct* transmitterproduct);

    TransmitterProduct* createTransmitterProduct() override;
    ReceiverProduct* createReceiverProduct() override;
    void update(GraphicsComponent*) override;

private:
    SceneObservable *m_graphicsfactory;
    GraphicsComponent *m_graphiccomponent;
};

#endif // DIALOGFACTORY_H
