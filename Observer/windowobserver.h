#ifndef WINDOWOBSERVER_H
#define WINDOWOBSERVER_H

class WindowObserver{
public:
    virtual ~WindowObserver(){}
    virtual void update(int mode) = 0;
};

#endif // WINDOWOBSERVER_H
