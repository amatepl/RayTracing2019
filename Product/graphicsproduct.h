#ifndef GRAPHICSPRODUCT_H
#define GRAPHICSPRODUCT_H

#include <string>

#include "Product/mathematicalproduct.h"

class QPixmap;

class GraphicsProduct
{
public:
    virtual ~GraphicsProduct() {}

    virtual void draw() = 0;
    virtual bool graphicsSelected() {return false;}
    std::string getType() {return m_type;}
    void attachObserver(MathematicalProduct* product){m_observer = product;};
    MathematicalProduct* toMathematicalProduct(){return m_observer;};

protected:
    MathematicalProduct* m_observer;
    std::string m_type;

};

#endif // GRAPHICSPRODUCT_H
