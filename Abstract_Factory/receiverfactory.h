#ifndef RECEIVERFACTORY_H
#define RECEIVERFACTORY_H

#include "scenefactory.h"
#include "Product/ReceiverProduct/graphicsreceiverproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"

class ReceiverFactory: public SceneFactory
{
private:
    QMenu *m_productmenu;
public:
    ReceiverFactory(QMenu *productmenu);

    // Overrides
    GraphicsComponent * createGraphicsComponent(int posX, int posY, QMenu *productmenu, QGraphicsScene* scene) override;

};

#endif // RECEIVERFACTORY_H
