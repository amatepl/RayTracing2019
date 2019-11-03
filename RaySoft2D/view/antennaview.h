#ifndef ANTENNAVIEW_H
#define ANTENNAVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

#include <iostream>
#include <map>
#include <string>
#include <viewableobject.h>

#include "usableobject.h"
#include "dialogableobject.h"

using namespace std;

class AntennaView : public QObject, public ViewableObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        AntennaView(UsableObject *antenna, DialogableObject *dialog, QMenu *itemMenu);
        ~AntennaView();
        static QPixmap image();

        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
        void changePos(QPointF &pos);
        bool isSelectedView();

    private:
        UsableObject *m_antennaModel;
        DialogableObject *m_antennaDialog;
        QMenu *m_itemMenu;
        map<string,int>* m_intProperties;
        QPixmap *icon;

   private slots:
        void propertiesChanged(map<string,int>* intValues, map<string,double>* doubleValues);
};

#endif // ANTENNAVIEW_H
