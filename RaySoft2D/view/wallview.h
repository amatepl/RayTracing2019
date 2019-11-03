#ifndef WALLVIEW_H
#define WALLVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

#include <viewableobject.h>
#include <iostream>

#include "dialogableobject.h"
#include "usableobject.h"

#include <iostream>
using namespace std;

class WallView : public QObject, public ViewableObject, public QGraphicsLineItem
{
    Q_OBJECT
    public:
        WallView(UsableObject *wall, DialogableObject *dialog, QMenu *itemMenu);
        ~WallView();

        static QPixmap image();
        void typeProperties(int type);

        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
        void changePos(QPointF &pos);
        bool isSelectedView();

    private:
        UsableObject *m_wallModel;
        DialogableObject *m_wallDialog;
        QMenu *m_itemMenu;
        map<string,int>* m_intProperties;

     private slots:
        void propertiesChanged(map<string,int>* intValues,map<string,double>* doubleValues);
};

#endif // WALLVIEW_H
