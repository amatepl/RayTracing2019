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

    struct TreeParams{float radius,length,density;};
    float getRadius()const;
    void setRadius(float radius);


    int getPosX() override;
    int getPosY() override;
    void setPosX(int) override;
    void setPosY(int) override;
    void newProperties() override;
    void attachObservable(GraphicsProduct *graphic) override;

    void update(QGraphicsItem *graphic) override;
    void openDialog() override;

private:
    QPointF m_center;
    float a;            // Radius (m)
//    float h;            // length (m) of branches and leafs
//    float epsilon_r;    // dielectric constant
//    float rho;          // density (m^{-3})
    vector<TreeParams> m_params;
};

#endif // MATHEMATICALTREEPRODUCT_H
