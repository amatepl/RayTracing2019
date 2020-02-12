#ifndef DIALOGOBSERVABLE_H
#define DIALOGOBSERVABLE_H

#include "dialogobserver.h"

class DialogObservable{

public:
    virtual ~DialogObservable(){}

    virtual void attachObserver(DialogObserver*) = 0;
    virtual void detachObserver(DialogObserver*) = 0;
    virtual void notify() = 0;
};

#endif // DIALOGOBSERVABLE_H
