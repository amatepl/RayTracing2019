#ifndef RECEIVERFACTORY_H
#define RECEIVERFACTORY_H

#include "scenefactory.h"
#include "Product/ReceiverProduct/graphicsreceiverproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"

class ReceiverFactory: public SceneFactory
{
public:
    ReceiverFactory(QMenu *productmenu, QGraphicsScene* scene);

    // Overrides
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic) override;

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;

};

#endif // RECEIVERFACTORY_H
