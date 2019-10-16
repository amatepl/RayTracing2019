#ifndef MOVABLEOBJECT
#define MOVABLEOBJECT

class QPointF;

class MovableObject
{
public:
    virtual void moveToPosition(const QPointF &pos) = 0;
};


#endif // MOVABLEOBJECT



