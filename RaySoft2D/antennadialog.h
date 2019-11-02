#ifndef ANTENNADIALOG_H
#define ANTENNADIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QString>
#include <dialogableobject.h>

#include "antennaview.h"

class AntennaDialog :public DialogableObject
{
    Q_OBJECT
    public:
        AntennaDialog();
        ~AntennaDialog() {}

        map<string,int>* getIntValues();
        void setIntValues(map<string,int>* values);
        map<string,double>* getDoubleValues();
        void setDoubleValues(map<string,double>* values);

    private:
        QSpinBox *angleSpinBox;
        QSpinBox *posX;
        QSpinBox *posY;

    public slots:
        void saveProperties();

    signals:
        void propertiesChanged(map<string,int>* intValues, map<string,double>* doubleValues);

};

#endif // ANTENNADIALOG_H
