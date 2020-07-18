#ifndef PRODUCTOBSERVER_H
#define PRODUCTOBSERVER_H

#include <QPointF>

class ProductObservable;

class ProductObserver{

public:
    //virtual void update(const QPointF *pos,const float speed, const float direction) = 0;
    virtual void update(ProductObservable* productObservable,const float speed, const float direction) = 0;
    virtual void compute(ProductObservable* productObservable) {};
    virtual void drawRays(ProductObservable* productObservable, bool draw){}
    virtual void attachObservable(ProductObservable* productObservable)=0;
};

#endif // PRODUCTOBSERVER_H
