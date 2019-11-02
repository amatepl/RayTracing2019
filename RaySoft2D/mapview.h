#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPolygonF>


#include "antennamodel.h"
#include "antennadialog.h"
#include "antennaview.h"
#include "buildingmodel.h"
#include "buildingdialog.h"
#include "buildingview.h"
#include "wallmodel.h"
#include "walldialog.h"
#include "wallview.h"
#include "dialogableobject.h"
#include "usableobject.h"
#include "viewableobject.h"

class MapView : public QGraphicsScene
{
    Q_OBJECT
    public:
        enum Mode {InsertWall,InsertBuilding,InsertAntenna,MoveItem};

        MapView(QWidget *parent = nullptr);
        void setMode(Mode mode);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    private:
        Mode myMode;
        vector <ViewableObject*> m_viewableObject;

    signals:
        void itemInserted(QGraphicsItem *item);
};

#endif // MAPVIEW_H
