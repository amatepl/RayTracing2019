#ifndef MATHEMATICALFACTORY_H
#define MATHEMATICALFACTORY_H

#include <iostream>
#include <vector>

#include "scenefactory.h"
#include "Product/TransmitterProduct/transmitterproduct.h"
#include "Product/BuildingProduct/mathematicalbuildingproduct.h"
#include "Observer/sceneobserver.h"
#include "Observer/sceneobservable.h"
#include "Composite/graphicscomponent.h"

class MathematicalBuildingProduct;

class MathematicalFactory : public SceneFactory, public SceneObserver
{
public:
    MathematicalFactory(SceneObservable *graphicsfactory);
    ~MathematicalFactory() override;

    void receiveBuildingProduct(BuildingProduct*,BuildingProduct*);

    TransmitterProduct* createTransmitterProduct() override;
    ReceiverProduct * createReceiverProduct() override;
    BuildingProduct * createBuildingProduct() override;
    void updateNewProperties(GraphicsComponent*) override;
    void updateChangeProperties(GraphicsComponent *) override;

private:
    SceneObservable *m_graphicsfactory;
    GraphicsComponent *m_graphiccomponent;
    std::vector<MathematicalBuildingProduct*> m_mathbuildings;
    std::vector<MathematicalBuildingProduct*>::iterator m_mathbuildingsiterator;
};

#endif // MATHEMATICALFACTORY_H
