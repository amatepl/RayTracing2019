#ifndef TRANSMITTERFACTORY_H
#define TRANSMITTERFACTORY_H

#include "scenefactory.h"
#include "Product/TransmitterProduct/graphicstx.h"
#include "Product/TransmitterProduct/tx.h"
#include "Share/dialogfctry.h"

class TransmitterFactory: public SceneFactory
{
public:
    TransmitterFactory(QMenu *productmenu, QGraphicsScene* scene,const float scale);
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic) override;
    void setScale(const double &px_to_m) override;

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
    float px_to_meter;
    DerivedDialogWinFctry <int, int, int> *p;
};

#endif // TRANSMITTERFACTORY_H
