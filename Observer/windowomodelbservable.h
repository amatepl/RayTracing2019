#ifndef WINDOWOMODELBSERVABLE_H
#define WINDOWOMODELBSERVABLE_H

#include "Product/SceneProduct.h"
#include <vector>

class MathematicalRayProduct;

using namespace std;

class WindowModelObservable{
public:
    virtual ~WindowModelObservable(){}
    virtual void modelAnswer(vector<MathematicalComponent *> sceneproducts) = 0;
    virtual void modelAnswer(vector<MathematicalRayProduct> *sceneproducts) = 0;
    virtual void modelNotify(vector<SceneProduct *> sceneproducts) = 0;
    virtual void modelNotify(vector<MathematicalRayProduct *> sceneproducts) = 0;
};

#endif // WINDOWOMODELBSERVABLE_H
