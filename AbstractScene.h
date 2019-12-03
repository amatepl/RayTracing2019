#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <vector>
#include <complex>
#include "AbstractAntena.h"

using namespace std;

class QGraphicsItem;
class ray;

class AbstractScene
{
public:
    virtual void addToScene(QGraphicsItem *item) = 0;
    virtual void drawRays(vector <ray>* rays) =0;
    virtual void drawChosenRays(vector<vector <ray>*>* rays, AbstractAntena* antena) =0;
    virtual void drawChosenRays() =0;
    virtual void clearRays() = 0;
    //virtual void computeEMField(vector <ray>* rays) = 0; // Probably shouldent be done here.
    virtual void clearEMFIeld() =0; // Probably shouldent be done here.
    virtual complex <double> computeEMField(vector <ray>* rays) =0;
    virtual double computePrx(complex <double> totalEfield,AbstractAntena* transmit)=0;
};


#endif // ABSTRACTSCENE_H
