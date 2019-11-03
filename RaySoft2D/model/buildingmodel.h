#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include <QObject>
#include <QWidget>

#include <usableobject.h>

#include <iostream>
using namespace std;

class BuildingModel : public UsableObject, public QRect
{
    public:
        BuildingModel(int x, int y, int width, int height,
                      double relPerm = 0.0, double cond = 0.0);
        ~BuildingModel();

        map<string,int>* getIntValues();
        void setIntValues(map<string,int>* values);
        map<string,double>* getDoubleValues();
        void setDoubleValues(map<string,double>* values);

    private:
        map<string,int>* m_intProperties;
        map<string,double>* m_doubleProperties;
};

#endif // BUILDINGMODEL_H
