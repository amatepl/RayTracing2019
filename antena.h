#ifndef ANTENA_H
#define ANTENA_H
#include "room.h"

class room;

class antena: public QGraphicsEllipseItem
{
public:
    antena(room *scene = 0, QPointF p = QPointF() , int type = 0);
    ~antena();
    int getPosX();
    int getPosY();

private:
    room *myRoom;
    QPointF pos;
    int antenaType;
    QPen setColor();
};

#endif // ANTENA_H
