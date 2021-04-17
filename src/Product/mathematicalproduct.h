#ifndef MATHEMATICALPRODUCT_H
#define MATHEMATICALPRODUCT_H

#include <QGraphicsItem>
#include "Model/algorithmInterface.h"

class GraphicsProduct;

class MathematicalProduct//: public QObject
{
public:
    virtual ~MathematicalProduct(){}
    virtual void openDialog(QWidget *parent=nullptr) = 0;
    std::string getType(){return m_type;}
    virtual std::string changeAppearance() {return "no appearance";}
    virtual void setScale(float scale) {px_to_meter = scale;}

    //MathematicalProduct act as an observer of GraphicsProduct
    virtual void attachObservable(GraphicsProduct* graphic) {m_graphic = graphic;}
    virtual void update(QGraphicsItem* graphic) = 0;
    virtual void updateInformation() {};
    GraphicsProduct* toGraphicsProduct() {return m_graphic;}

    // Method for mediator pattern. MathematicalProduct have a pointer to
    // AlgorithmInterface that we can set at a good time
    void setMediator(AlgorithmInterface* algorithm) {m_algorithm = algorithm;}

protected:
    std::string m_type;
    GraphicsProduct* m_graphic = nullptr;
    AlgorithmInterface *m_algorithm = nullptr;
    float px_to_meter;
};

#endif // MATHEMATICALPRODUCT_H
