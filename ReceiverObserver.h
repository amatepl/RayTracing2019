#ifndef RECEIVEROBSERVER_H
#define RECEIVEROBSERVER_H

#endif // RECEIVEROBSERVER_H

class QPointF;

class ReceiverObserver
{
  public:
    virtual void notifyObserver(const QPointF &pos) = 0;
    //virtual ~ReceiverObserver(void);

};
