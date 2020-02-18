#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "scenefactory.h"
#include "Product/TransmitterProduct/graphicstransmitterproduct.h"
#include "Product/ReceiverProduct/graphicsreceiverproduct.h"
#include "Product/BuildingProduct/graphicsbuildingproduct.h"
#include "Composite/graphicscomposite.h"
#include "Observer/windowobserver.h"
#include "Observer/windowobservable.h"
#include "Observer/sceneobservable.h"

class GraphicsFactory :public WindowObserver, public SceneObservable, public SceneFactory, public QGraphicsScene
{
public:
    enum Mode{MoveItem,InsertTransmitter,InsertReceiver,InsertBuilding};

    GraphicsFactory(QGraphicsView *view, WindowObservable* windowobservable);
    ~GraphicsFactory() override;

    void update(int mode) override;

    void notifyNewProperties(GraphicsComponent*) override;
    void notifyChangeProperties(GraphicsComponent *) override;
    void attachObserver(SceneObserver *) override;
    void detachObserver(SceneObserver *) override;

    TransmitterProduct* createTransmitterProduct() override;
    ReceiverProduct * createReceiverProduct() override;
    BuildingProduct * createBuildingProduct() override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsView* m_view;
    GraphicsComponent* m_graphicscomponent;
    Mode m_mode;
    WindowObservable *m_windowobservable;

    vector<SceneObserver*> m_sceneobserver;
    vector<SceneObserver*>::iterator m_sceneobserveriterator;
};

#endif // GRAPHICSFACTORY_H
