#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPolygonF>
#include <QFile>
#include <QTextStream>

#include <iostream>

#include "model/antennamodel.h"
#include "dialog/antennadialog.h"
#include "view/antennaview.h"
#include "model/buildingmodel.h"
#include "dialog/buildingdialog.h"
#include "view/buildingview.h"
#include "model/wallmodel.h"
#include "dialog/walldialog.h"
#include "view/wallview.h"
#include "dialogableobject.h"
#include "usableobject.h"
#include "viewableobject.h"

using namespace std;

class MapView : public QGraphicsScene
{
    Q_OBJECT
    public:
        enum Mode {InsertWall,InsertBuilding,InsertAntenna,MoveItem};

        MapView(QMenu *itemMenu,QWidget *parent = nullptr);
        void setMode(Mode mode);
        void readExamples(const QString &fileName);
        void deleteObject();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    private:
        Mode myMode;
        QMenu *m_itemMenu;
        vector <ViewableObject*> m_viewableObject;
        vector <ViewableObject*>::iterator viewable;

    signals:
        void itemInserted(QGraphicsItem* item);
};

#endif // MAPVIEW_H
