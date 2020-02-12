#ifndef DIALOGOBSERVER_H
#define DIALOGOBSERVER_H

class DialogObserver{

public:
    virtual ~DialogObserver(){}
    virtual void update() = 0;
};

#endif // DIALOGOBSERVER_H
