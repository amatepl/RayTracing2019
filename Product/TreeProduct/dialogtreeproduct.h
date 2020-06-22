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
    DialogTreeProduct(TreeProduct* graphic, DialogFactory* factory);
    ~DialogTreeProduct() override;

    void createDialog();

    int getPosX() override;
    int getPosY() override;

    void setPosX(int) override;
    void setPosY(int) override;

private:
    DialogFactory* m_dialogfactory;
    QSpinBox* m_posx;
    QSpinBox* m_posy;

public slots:
    void newProperties();
};

#endif // DIALOGTREEPRODUCT_H
