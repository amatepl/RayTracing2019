#ifndef ANTENNAMODEL_H
#define ANTENNAMODEL_H

#include <QObject>
#include <QWidget>
#include <QRect>

#include <usableobject.h>
#include <cmath>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class AntennaModel :public UsableObject, public QRect
{
    public:
        AntennaModel(int x, int y, int width, int height);
        ~AntennaModel();

        map<string,int>* getIntValues();
        void setIntValues(map<string,int>* values);
        map<string,double>* getDoubleValues();
        void setDoubleValues(map<string,double>* values);

    private:
        map<string,int>* m_intProperties;
};

#endif // ANTENNAMODEL_H
