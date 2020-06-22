#ifndef PRODUCTOBSERVER_H
#define PRODUCTOBSERVER_H

#include <QPointF>

class ProductObserver{

public:
    virtual void notify(const QPointF &pos) = 0;
};

#endif // PRODUCTOBSERVER_H
