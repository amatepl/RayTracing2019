#ifndef GRAPHICSPRODUCT_H
#define GRAPHICSPRODUCT_H

#include <string>
#include <iostream>


#include "Product/mathematicalproduct.h"

using namespace std;

class QPixmap;

class GraphicsProduct
{
public:
    virtual ~GraphicsProduct(){cout<<"Gaphics product deleted!"<<endl;}

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
