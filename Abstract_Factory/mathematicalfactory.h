#ifndef MATHEMATICALFACTORY_H
#define MATHEMATICALFACTORY_H

#include <iostream>
#include <vector>

#include "scenefactory.h"
#include "Product/TransmitterProduct/transmitterproduct.h"
#include "Product/BuildingProduct/mathematicalbuildingproduct.h"
#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"
#include "Product/TreeProduct/mathematicaltreeproduct.h"
#include "Product/CarProduct/mathematicalcarproduct.h"
#include "Observer/sceneobserver.h"
#include "Observer/sceneobservable.h"
#include "Composite/graphicscomponent.h"

class MathematicalBuildingProduct;
class MathematicalReceiverProduct;
class MathematicalTreeProduct;
class MathematicalCarProduct;
class MathematicalTransmitterProduct;

class MathematicalFactory : public SceneFactory, public SceneObserver
{
public:
    MathematicalFactory(SceneObservable *graphicsfactory);
    ~MathematicalFactory() override;

    void receiveBuildingProduct(BuildingProduct*,BuildingProduct*);
    void receiveTransmitterProduct(TransmitterProduct*, TransmitterProduct*);
    void receiveReceiverProduct(ReceiverProduct*,ReceiverProduct*);
    void receiveTreeProduct(TreeProduct*,TreeProduct*);
    void receiveCarProduct(CarProduct*, CarProduct*);

    TransmitterProduct* createTransmitterProduct() override;
    ReceiverProduct * createReceiverProduct() override;
    BuildingProduct * createBuildingProduct() override;
    TreeProduct * createTreeProduct() override;
    CarProduct *createCarProduct() override;

    void updateNewProperties(GraphicsComponent*) override;
    void updateChangeProperties(GraphicsComponent *) override;

private:
    SceneObservable *m_graphicsfactory;
    GraphicsComponent *m_graphiccomponent;

    std::vector<MathematicalBuildingProduct*> m_mathbuildings;
    std::vector<MathematicalBuildingProduct*>::iterator m_mathbuildingsiterator;
    std::vector<MathematicalReceiverProduct*> m_mathreceivers;
    std::vector<MathematicalReceiverProduct*>::iterator m_mathreceiversiterator;
    std::vector<MathematicalTransmitterProduct*> m_mathtransmitters;
    std::vector<MathematicalTransmitterProduct*>::iterator m_mathtransmittersiterator;
    std::vector<MathematicalTreeProduct*> m_mathtrees;
    std::vector<MathematicalTreeProduct*>::iterator m_mathtreesiterator;
    std::vector<MathematicalCarProduct*> m_mathcars;
    std::vector<MathematicalCarProduct*>::iterator m_mathcarsiterator;
};

#endif // MATHEMATICALFACTORY_H
