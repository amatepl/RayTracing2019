#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>

#include "Product/mathematicalproduct.h"
#include "Observer/productobservable.h"

using namespace std;

class Model
{
public:
    Model();
    ~Model();
    void addMathematicalComponent(string type, MathematicalProduct* mathematicalComponent);
    void setObservableProducts();

private:
    map<string,vector<MathematicalProduct*>> m_mathematicalComponents;

};

#endif // MODEL_H
