#ifndef MATHEMATICALPRODUCT_H
#define MATHEMATICALPRODUCT_H

#include <QGraphicsItem>

class GraphicsProduct;

class MathematicalProduct//: public QObject
{
public:
    virtual ~MathematicalProduct(){}
    virtual void openDialog() = 0;
    std::string getType(){return m_type;}
    virtual std::string changeAppearance() {return "no appearance";}

    //MathematicalProduct act as an observer of GraphicsProduct
    virtual void attachObservable(GraphicsProduct* graphic) {m_graphic = graphic;}
    virtual void update(QGraphicsItem* graphic) = 0;
    GraphicsProduct* toGraphicsProduct() {return m_graphic;}

protected:
    std::string m_type;
    GraphicsProduct* m_graphic = nullptr;
    QDialog* m_dialog;
};

#endif // MATHEMATICALPRODUCT_H
