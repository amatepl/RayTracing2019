#ifndef BUILDINGDIALOG_H
#define BUILDINGDIALOG_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>


#include <dialogableobject.h>

#include "buildingview.h"

class BuildingDialog :public DialogableObject
{
    Q_OBJECT
    public:
        BuildingDialog();
        ~BuildingDialog() {}

        map<string,int>* getIntValues();
        void setIntValues(map<string,int>* values);
        map<string,double>* getDoubleValues();
        void setDoubleValues(map<string,double>* values);

    private:
        QComboBox *buildingTypeBox;
        QSpinBox *posXBox,*posYBox,*heightBox,*widthBox,*orientation;
        QDoubleSpinBox *permittivityBox,*conductivityBox;


    public slots:
        void saveProperties();
        void changeType(QString buildingtype);

    signals:
        void propertiesChanged(map<string,int> *intValues, map<string,double>* doubleValues);
};

#endif // BUILDINGDIALOG_H
