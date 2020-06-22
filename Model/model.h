#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>

#include "Composite/MathematicalComponent.h"
#include "Observer/productobservable.h"

using namespace std;

class Model
{
public:
    Model();
    ~Model();
    void addMathematicalComponent(string type, MathematicalComponent* mathematicalComponent);
    void setObservableProducts();

private:
    map<string,vector<MathematicalComponent*>> m_mathematicalComponents;

};

#endif // MODEL_H
