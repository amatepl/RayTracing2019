#ifndef GRAPHICSMAP_H
#define GRAPHICSMAP_H

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

using namespace std;

class GraphicsMap: public QGraphicsScene
{
public:
    enum Mode{MoveItem,InsertItem};
    GraphicsMap(QGraphicsView *view, AppInterface *windowobservable, QMenu* productmenu);
    ~GraphicsMap();

    void setSceneFactory(SceneFactory *sceneFactory);

    // Overdrives
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Mode m_mode;
    QGraphicsView* m_view;
    QMenu *m_productmenu;
    AppInterface *m_app;

    SceneFactory *m_sceneFactory = 0;
};

#endif // GRAPHICSMAP_H
