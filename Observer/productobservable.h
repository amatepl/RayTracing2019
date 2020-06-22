#ifndef PRODUCTOBSERVABLE_H
#define PRODUCTOBSERVABLE_H

#include "Observer/productobserver.h"

class ProductObservable{
public:
    virtual void attachObserver(ProductObserver* productObserver) = 0;
};

#endif // PRODUCTOBSERVABLE_H
