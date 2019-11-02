#ifndef BUILDINGVIEW_H
#define BUILDINGVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QPainter>
#include <viewableobject.h>
#include <iostream>

#include "dialogableobject.h"
#include "usableobject.h"

using namespace std;

class BuildingView :  public QObject, public ViewableObject, public QGraphicsRectItem
{
    Q_OBJECT
    public:
        BuildingView(UsableObject *building, DialogableObject *dialog);

        static QPixmap image();
        void typeProperties(int type);

        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
        void changePos(QPointF &pos);
        bool isSelectedView();

    private:
        UsableObject *m_buildingModel;
        DialogableObject *m_buildingDialog;
        map<string,int>* m_intProperties;

   private slots:
        void propertiesChanged(map<string,int>* intValues,map<string,double>* doubleValues);
};

#endif // BUILDINGVIEW_H
