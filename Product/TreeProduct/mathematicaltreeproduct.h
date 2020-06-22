#ifndef MATHEMATICALTREEPRODUCT_H
#define MATHEMATICALTREEPRODUCT_H

#include <QPolygonF>

#include "treeproduct.h"
#include "Composite/MathematicalComponent.h"

class MathematicalTreeProduct: public QPolygonF, public TreeProduct, public MathematicalComponent
{
public:
    MathematicalTreeProduct(TreeProduct* graphic);
    ~MathematicalTreeProduct() override;

    void newProperties();

    int getPosX() override;
    int getPosY() override;
    TreeProduct *getTreeProduct();

    void setPosX(int) override;
    void setPosY(int) override;
    void setTreeProduct(TreeProduct*);

    MathematicalComponent* toMathematicalComponent() override;

private:
    //MathematicalFactory* m_factory;
    TreeProduct* m_graphic;
    int m_posx,m_posy;
};

#endif // MATHEMATICALTREEPRODUCT_H
