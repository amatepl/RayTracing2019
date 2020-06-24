#ifndef MATHEMATICALPRODUCT_H
#define MATHEMATICALPRODUCT_H

#include <QGraphicsItem>

class GraphicsProduct;

class MathematicalProduct
{
public:
    virtual ~MathematicalProduct(){}
    virtual void openDialog() = 0;
    virtual void update(QGraphicsItem* graphic) = 0;
    std::string getType(){return m_type;}
    virtual std::string changeAppearance() {return "no appearance";}
    void attachObservable(GraphicsProduct* graphic) {m_graphic = graphic;}
    GraphicsProduct* toGraphicsProduct() {return m_graphic;}

protected:
    std::string m_type;
    GraphicsProduct* m_graphic;
    QDialog* m_dialog;
};

#endif // MATHEMATICALPRODUCT_H
