#ifndef MATHEMATICALTREEPRODUCT_H
#define MATHEMATICALTREEPRODUCT_H

#include <QPolygonF>

#include "treeproduct.h"
#include "Product/mathematicalproduct.h"
#include "dialogtreeproduct.h"

class MathematicalTreeProduct: public QPolygonF, public MathematicalProduct, public TreeProduct
{
public:
    MathematicalTreeProduct(QPolygonF poly, QPointF center);
    ~MathematicalTreeProduct() override;

    int getPosX() override;
    int getPosY() override;
    void setPosX(int) override;
    void setPosY(int) override;
    void newProperties() override;

    void update(QGraphicsItem *graphic) override;
    void openDialog() override;

private:
    QPointF m_center;
};

#endif // MATHEMATICALTREEPRODUCT_H
