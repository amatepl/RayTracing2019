#ifndef MODELOBSERVER_H
#define MODELOBSERVER_H

class ModelObservable;

class ModelObserver
{
public:
    virtual void attachObservable(ModelObservable* modelObservable) = 0;
};

#endif // MODELOBSERVER_H
