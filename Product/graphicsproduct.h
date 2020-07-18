#ifndef GRAPHICSPRODUCT_H
#define GRAPHICSPRODUCT_H

#include <string>
#include <iostream>


#include "Product/mathematicalproduct.h"

using namespace std;

class QPixmap;

class GraphicsProduct /*public QObject*/
{
//    Q_OBJECT

public:
    virtual ~GraphicsProduct(){/*cout<<"Gaphics product deleted!"<<endl;*/}

    virtual void draw() = 0;
    virtual void erase(){};
    virtual bool graphicsSelected() {return false;}
    std::string getType() {return m_type;}

    // GraphicsProduct act has an observable with MathematicalProduct
    void attachObserver(MathematicalProduct* product){m_observer = product;};
    MathematicalProduct* toMathematicalProduct(){return m_observer;};

    // Depends on the mathematical product
    virtual void notifyToGraphic(QPointF*) {};
    virtual void notifyToGraphic(QPointF*, float) {};
    virtual void notifyToGraphic(QPointF*, double) {};
    virtual void notifyToGraphic(QRect*, double) {};
    virtual void notifyToGraphic(QPolygonF*,int,int) {};
    virtual void sendInformation() {};


protected:
    MathematicalProduct* m_observer;
    std::string m_type;

//public slots:
//    virtual void notifyToGraphicSig(QPolygonF*,int,int,double) {};
};

#endif // GRAPHICSPRODUCT_H
