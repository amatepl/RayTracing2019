#ifndef DIALOGTREEPRODUCT_H
#define DIALOGTREEPRODUCT_H

#include <QDialog>

#include "treeproduct.h"
#include "Abstract_Factory/dialogfactory.h"
#include "Product/TreeProduct/graphicstreeproduct.h"

class DialogTreeProduct: public QDialog, public TreeProduct
{
    Q_OBJECT
public:
    DialogTreeProduct(TreeProduct* mathematicalproduct);
    ~DialogTreeProduct() override;

    void createDialog();

    int getPosX() override;
    int getPosY() override;

    void setPosX(int) override;
    void setPosY(int) override;
    void newProperties() override;

private:
    TreeProduct* m_mathematicalproduct;
    QSpinBox* m_posx;
    QSpinBox* m_posy;

public slots:
    void saveProperties();
};

#endif // DIALOGTREEPRODUCT_H
