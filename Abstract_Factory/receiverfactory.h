#ifndef RECEIVERFACTORY_H
#define RECEIVERFACTORY_H

#include "scenefactory.h"
#include "Product/ReceiverProduct/graphicsreceiverproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"
#include "Widget/infowidget.h"

class ReceiverFactory: public SceneFactory
{
public:
    ReceiverFactory(QMenu *productmenu, InfoWidget *info, QGraphicsScene* scene);

    // Overrides
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic) override;
    MathematicalProduct * createMathematicalProduct(MathematicalProduct *original, bool linkgraphic) override;

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
    InfoWidget *info_widget;

};

#endif // RECEIVERFACTORY_H
