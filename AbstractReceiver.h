#ifndef ABSTRACTRECEIVER_H
#define ABSTRACTRECEIVER_H

#include <vector>

using namespace std;

class ray;

class AbstractReceiver
{
public:
    virtual void addWholeRay(vector <ray>* wholeRay) = 0;
};

#endif // ABSTRACTRECEIVER_H
