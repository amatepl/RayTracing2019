#ifndef USABLEOBJECT_H
#define USABLEOBJECT_H

#include <map>
#include <string>

using namespace std;

class UsableObject
{
    public:
        virtual ~UsableObject() {}

        virtual map<string,int>* getIntValues() = 0;
        virtual void setIntValues(map<string,int>* values) = 0;

        virtual map<string,double>* getDoubleValues() = 0;
        virtual void setDoubleValues(map<string,double>* values) = 0;
};

#endif // USABLEOBJECT_H
