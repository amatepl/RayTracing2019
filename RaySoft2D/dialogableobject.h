#ifndef DIALOGABLEOBJECT_H
#define DIALOGABLEOBJECT_H
#include <usableobject.h>
#include <QDialog>

#include <map>
#include <string>

using namespace std;

class DialogableObject : public UsableObject, public QDialog
{
    public:
        virtual ~DialogableObject() {}

        virtual void saveProperties() = 0;
        virtual void propertiesChanged(map<string,int> *intValues, map<string,double>* doubleValues) = 0;
};

#endif // DIALOGABLEOBJECT_H
