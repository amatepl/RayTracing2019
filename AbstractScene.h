#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <vector>

using namespace std;

class QGraphicsItem;
class ray;

class AbstractScene
{
public:
    virtual void addToScene(QGraphicsItem *item) = 0;
    virtual void drawRays(vector <ray>* rays) =0;
    virtual void clearRays() = 0;
    virtual void computeEMField(vector <ray>* rays) = 0; // Probably shouldent be done here.
    virtual void clearEMFIeld() =0; // Probably shouldent be done here.
};


#endif // ABSTRACTSCENE_H
