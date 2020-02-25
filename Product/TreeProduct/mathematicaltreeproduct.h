#ifndef MATHEMATICALTREEPRODUCT_H
#define MATHEMATICALTREEPRODUCT_H

#include <QPolygonF>

#include "treeproduct.h"
#include "Abstract_Factory/mathematicalfactory.h"


class MathematicalTreeProduct: public QPolygonF, public TreeProduct
{
public:
    MathematicalTreeProduct(TreeProduct* graphic, MathematicalFactory* factory);
    ~MathematicalTreeProduct() override;

    void newProperties();

    int getPosX() override;
    int getPosY() override;
    TreeProduct *getTreeProduct();

    void setPosX(int) override;
    void setPosY(int) override;
    void setTreeProduct(TreeProduct*);

private:
    MathematicalFactory* m_factory;
    TreeProduct* m_graphic;
    int m_posx,m_posy;
};

#endif // MATHEMATICALTREEPRODUCT_H
