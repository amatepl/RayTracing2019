#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QGraphicsItem>


class Visualizer
{
public:
    virtual void draw(QGraphicsItem *item) = 0;
};

#endif // VISUALIZER_H
