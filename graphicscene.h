#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <vector>

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "Abstract_Factory/scenefactory.h"
#include "Observer/sceneobservable.h"
#include "Observer/windowobservable.h"
#include "Composite/graphicscomponent.h"

using namespace std;

class GraphicScene: public QGraphicsScene
{
public:
    enum Mode{MoveItem,InsertItem};
    GraphicScene(QGraphicsView *view, WindowObservable *windowobservable, QMenu* productmenu);
    ~GraphicScene();

    void setSceneFactory(SceneFactory *sceneFactory);

    // Overdrives
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Mode m_mode;
    QGraphicsView* m_view;
    QMenu *m_productmenu;
    WindowObservable *m_windowobesrvable;

    SceneFactory *m_sceneFactory = 0;

    vector<SceneObserver*> m_sceneobserver;
    vector<SceneObserver*>::iterator m_sceneobserveriterator;

};

#endif // GRAPHICSCENE_H
