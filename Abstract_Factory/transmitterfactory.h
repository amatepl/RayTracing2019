#ifndef TRANSMITTERFACTORY_H
#define TRANSMITTERFACTORY_H

#include "scenefactory.h"
#include "Product/TransmitterProduct/graphicstransmitterproduct.h"
#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"

class TransmitterFactory: public SceneFactory
{
public:
    TransmitterFactory(QMenu *productmenu, QGraphicsScene* scene,const float scale);
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic) override;

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
    float px_to_meter;
};

#endif // TRANSMITTERFACTORY_H
