#ifndef WINDOWOMODELBSERVABLE_H
#define WINDOWOMODELBSERVABLE_H

#include "Product/sceneproduct.h"
#include <vector>

class MathematicalRayProduct;
class WholeRay;

using namespace std;

class WindowModelObservable{
public:
    virtual ~WindowModelObservable(){}
    virtual void modelAnswer(vector<MathematicalProduct *> sceneproducts) = 0;
    virtual void modelAnswer(vector<MathematicalRayProduct> *sceneproducts) = 0;
    virtual void modelNotify(vector<MathematicalProduct *> sceneproducts) = 0;
    virtual void modelNotify(vector<MathematicalRayProduct>* sceneproducts) = 0;
    virtual void modelNotify(vector<WholeRay*> sceneproducts) = 0;
};

#endif // WINDOWOMODELBSERVABLE_H
