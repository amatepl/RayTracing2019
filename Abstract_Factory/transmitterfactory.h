#ifndef TRANSMITTERFACTORY_H
#define TRANSMITTERFACTORY_H

#include "scenefactory.h"
#include "Product/TransmitterProduct/graphicstransmitterproduct.h"
#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"

class TransmitterFactory: public SceneFactory
{
public:
    TransmitterFactory();
    GraphicsComponent * createGraphicsComponent(int posX, int posY, QMenu *productmenu, QGraphicsScene* scene) override;
};

#endif // TRANSMITTERFACTORY_H
