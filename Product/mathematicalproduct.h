#ifndef MATHEMATICALPRODUCT_H
#define MATHEMATICALPRODUCT_H

#include <QGraphicsItem>

class GraphicsProduct;

class MathematicalProduct
{
public:
    virtual ~MathematicalProduct(){}
    virtual void update(QGraphicsItem* graphic) = 0;
    std::string getType(){return m_type;}
    void attachObservable(GraphicsProduct* graphic) {m_graphic = graphic;}
    GraphicsProduct* toGraphicsProduct() {return m_graphic;}

protected:
    //GraphicsComponent* m_graphicsComponent = nullptr;
    std::string m_type;
    GraphicsProduct* m_graphic;
};

#endif // MATHEMATICALPRODUCT_H
