#ifndef ABSTRACTRECEIVER_H
#define ABSTRACTRECEIVER_H

#include <vector>
class QPointF;

using namespace std;

class ray;

class AbstractReceiver
{
public:
    virtual void addWholeRay(vector <ray>* wholeRay) = 0;
    virtual QPointF getPosition()const = 0;
};

#endif // ABSTRACTRECEIVER_H
