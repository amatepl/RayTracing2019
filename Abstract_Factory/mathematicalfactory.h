#ifndef MATHEMATICALFACTORY_H
#define MATHEMATICALFACTORY_H

#include "scenefactory.h"
#include "Product/TransmitterProduct/transmitterproduct.h"

class MathematicalFactory : public SceneFactory
{
public:
    MathematicalFactory();
    ~MathematicalFactory() override;

    TransmitterProduct* createTransmitterProduct() override;
};

#endif // MATHEMATICALFACTORY_H
