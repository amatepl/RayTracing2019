#ifndef RECEIVERFACTORY_H
#define RECEIVERFACTORY_H

#include "scenefactory.h"
#include "Product/ReceiverProduct/graphicsrx.h"
#include "Product/ReceiverProduct/rx.h"
#include "Widget/infowidget.h"

class ReceiverFactory: public SceneFactory
{
public:
    ReceiverFactory(QMenu *productmenu, InfoWidget *info, QGraphicsScene* scene, const float scale, QWidget *parent=nullptr);

    // Overrides
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic) override;
    MathematicalProduct * createMathematicalProduct(MathematicalProduct *original, bool linkgraphic) override;

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
    InfoWidget *info_widget;
    float px_to_meter;
    QWidget *m_parent;
};

#endif // RECEIVERFACTORY_H
