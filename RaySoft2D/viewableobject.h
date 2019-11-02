#ifndef VIEWABLEOBJECT_H
#define VIEWABLEOBJECT_H

#include <QPointF>

#include <map>
#include <string>

using namespace std;

class ViewableObject
{
    public:
        virtual ~ViewableObject() {}
        virtual void changePos(QPointF &pos)=0;
        virtual void propertiesChanged(map<string,int>* intValues, map<string,double>* doubleValues) = 0;
        virtual bool isSelectedView() = 0;
};

#endif // VIEWABLEOBJECT_H
