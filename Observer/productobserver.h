#ifndef PRODUCTOBSERVER_H
#define PRODUCTOBSERVER_H

#include <QPointF>
#include <QLineF>

class ProductObservable;

class ProductObserver{

public:
    //virtual void update(const QPointF *pos,const float speed, const float direction) = 0;
    virtual void update(ProductObservable* productObservable,QLineF const movement) = 0;
    virtual void drawRays(ProductObservable* productObservable, bool draw){}
    virtual void attachObservable(ProductObservable* productObservable)=0;
};

#endif // PRODUCTOBSERVER_H
