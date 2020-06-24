#ifndef PRODUCTOBSERVER_H
#define PRODUCTOBSERVER_H

#include <QPointF>

class ProductObservable;

class ProductObserver{

public:
    virtual void notify(const QPointF &pos) = 0;
    virtual void attachObservable(ProductObservable* productObservable)=0;
};

#endif // PRODUCTOBSERVER_H
