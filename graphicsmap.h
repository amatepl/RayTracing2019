#ifndef GRAPHICSMAP_H
#define GRAPHICSMAP_H

#include <iostream>

#include <vector>

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "Abstract_Factory/scenefactory.h"
#include "Observer/sceneobservable.h"
#include "Observer/AppInterface.h"
#include "Product/graphicsproduct.h"
#include "Product/graphicsheatmap.h"

using namespace std;

class GraphicsMap: public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode{MoveItem,InsertItem};
    GraphicsMap(QGraphicsView *view, AppInterface *windowobservable, QMenu* productmenu);
    ~GraphicsMap();

    void setSceneFactory(SceneFactory *sceneFactory);
    void deleteItem();
    void addHeatMap(HeatMap *heatMap);
    void clearHeatMap();

    // Overdrives
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void eField(double eField);

public slots:
    void updateEField(double eField);

private:
    Mode m_mode;
    QGraphicsView* m_view;
    QMenu *m_productmenu;
    AppInterface *m_app;
    unique_ptr<GraphicsHeatMap> m_heatMap;

    SceneFactory *m_sceneFactory = 0;
};

#endif // GRAPHICSMAP_H
