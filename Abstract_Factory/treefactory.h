#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "scenefactory.h"
#include "Product/TreeProduct/graphicstreeproduct.h"
#include "Product/TreeProduct/mathematicaltreeproduct.h"

class TreeFactory: public SceneFactory
{
public:
    TreeFactory(QMenu *productmenu, QGraphicsScene* scene);
    GraphicsProduct * createGraphicsProduct(int posX, int posY) override;
    MathematicalProduct * createMathematicalProduct(int posX, int posY, bool linkgraphic) override;

private:
    QMenu *m_productmenu;
    QGraphicsScene *m_scene;
};

#endif // TREEFACTORY_H
