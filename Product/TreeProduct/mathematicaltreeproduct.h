#ifndef MATHEMATICALTREEPRODUCT_H
#define MATHEMATICALTREEPRODUCT_H

#include <QPolygonF>

#include "treeproduct.h"
#include "Product/mathematicalproduct.h"

class MathematicalTreeProduct: public QPolygonF, public MathematicalProduct
{
public:
    MathematicalTreeProduct(QVector<QPointF> points);
    ~MathematicalTreeProduct() override;

    QVector<QPointF> getExtremities() {return m_extremities;}
    void setExtremities(QVector<QPointF> points) {m_extremities = points;}

    void update(QGraphicsItem *graphic) override;
    void openDialog() override;

private:
    //MathematicalFactory* m_factory;
    QVector<QPointF> m_extremities;
};

#endif // MATHEMATICALTREEPRODUCT_H
