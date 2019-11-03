#ifndef WALLDIALOG_H
#define WALLDIALOG_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>

#include <dialogableobject.h>

#include "view/wallview.h"

#include <iostream>
using namespace std;

class WallDialog : public DialogableObject
{
    Q_OBJECT
    public:
        WallDialog();
        ~WallDialog();

        map<string,int>* getIntValues();
        void setIntValues(map<string,int>* values);
        map<string,double>* getDoubleValues();
        void setDoubleValues(map<string,double>* values);

    private:
        QComboBox *wallTypeBox;
        QSpinBox *posX1Box,*posY1Box, *posX2Box,*posY2Box;
        QDoubleSpinBox *permittivityBox,*conductivityBox;

    public slots:
        void saveProperties();
        void changeType(QString walltype);

    signals:
        void propertiesChanged(map<string,int> *intValues, map<string,double>* doubleValues);
};

#endif // WALLDIALOG_H
