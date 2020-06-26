#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>

#include "Product/mathematicalproduct.h"
#include "Observer/productobservable.h"
#include "Observer/windowomodelbservable.h"
#include "Observer/modelobservable.h"
#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"
#include "Model/algorithmInterface.h"
#include "Abstract_Factory/abstractalgorithmfactory.h"

using namespace std;

class Model: public ModelObservable
{
public:
    Model(WindowModelObservable* windowModelObservable);
    ~Model();
    void addMathematicalComponent(MathematicalProduct* mathematicalProduct);
    void setObservableProducts();
    void setModelObservers();
    void launchAlgorithm(AlgorithmInterface* algorithm);
    MathematicalTransmitterProduct* selectTransmitter();
    void notify(MathematicalTransmitterProduct* transmitter) override;

private:
    map<string,vector<MathematicalProduct*>> m_mathematicalComponents;
    WindowModelObservable* m_windowModelObservable;
    AlgorithmInterface* m_algorithm;
};

#endif // MODEL_H
