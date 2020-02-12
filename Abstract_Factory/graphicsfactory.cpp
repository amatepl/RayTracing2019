#include "graphicsfactory.h"

GraphicsFactory::GraphicsFactory(QGraphicsView *view,WindowObservable* windowobservable)
{
    setSceneRect(0,0,400,400);
    m_view = view;

    m_view->setScene(this);
    m_graphicscomponent = new GraphicsComposite();
    m_mode = MoveItem;
    m_windowobservable = windowobservable;
}

GraphicsFactory::~GraphicsFactory(){

}

void GraphicsFactory::update(int mode){
    switch(mode){
        case int(WindowObservable::MoveItem):
            m_mode = MoveItem;
            break;
        case int(WindowObservable::InsertTransmitter):
            m_mode = InsertTransmitter;
            break;
        case int(WindowObservable::InsertReceiver):
            m_mode = InsertReceiver;
        break;
    }
}

void GraphicsFactory::notify(GraphicsComponent* graphicscomponent){
    for (unsigned long long i=0;i<m_sceneobserver.size();i++){
        m_sceneobserver.at(i)->update(graphicscomponent);
    }
}

void GraphicsFactory::attachObserver(SceneObserver *sceneobserver){
    m_sceneobserver.push_back(sceneobserver);
}

void GraphicsFactory::detachObserver(SceneObserver *sceneobserver){
    unsigned long long i = 0;
    for (m_sceneobserveriterator = m_sceneobserver.begin();
         m_sceneobserveriterator != m_sceneobserver.end();
         ++m_sceneobserveriterator){
        if (m_sceneobserver.at(i) == sceneobserver){
            m_sceneobserver.erase(m_sceneobserveriterator);
        }
        i++;
    }
}

TransmitterProduct* GraphicsFactory::createTransmitterProduct()
{
    TransmitterProduct* graphicstransmitter = new GraphicsTransmitterProduct(0,0,70,5.6,50e6,this);
    return graphicstransmitter;
}

ReceiverProduct* GraphicsFactory::createReceiverProduct()
{
    ReceiverProduct* graphicsReceiver = new GraphicsReceiverProduct(0,0,50e6,this);
    return graphicsReceiver;
}

void GraphicsFactory::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
                return;
    if (m_mode == InsertTransmitter){
        QPointF p(event->scenePos());
        TransmitterProduct* graphicstransmitter = createTransmitterProduct();
        graphicstransmitter->setPosX(int(p.x()));
        graphicstransmitter->setPosY(int(p.y()));
        m_graphicscomponent->add(dynamic_cast<GraphicsComponent*>(graphicstransmitter));
        m_windowobservable->answer();
    }
    if (m_mode == InsertReceiver){
        QPointF p(event->scenePos());
        ReceiverProduct* graphicsReceiver = createReceiverProduct();
        graphicsReceiver->setPosX(int(p.x()));
        graphicsReceiver->setPosY(int(p.y()));
        m_graphicscomponent->add(dynamic_cast<GraphicsComponent*>(graphicsReceiver));
        m_windowobservable->answer();
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsFactory::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (m_mode == MoveItem){
        QPointF p(event->scenePos());
        for(unsigned long long i = 0; i<m_graphicscomponent->getSize();i++){
            if (m_graphicscomponent->getGraphicsComponent(i)->graphicsSelected()){
                switch(m_graphicscomponent->getGraphicsComponent(i)->getType()){
                    case int(GraphicsComponent::TransmitterProduct):
                        dynamic_cast<TransmitterProduct*>(m_graphicscomponent->getGraphicsComponent(i))->setPosX(int(p.x()));
                        dynamic_cast<TransmitterProduct*>(m_graphicscomponent->getGraphicsComponent(i))->setPosY(int(p.y()));
                        break;
                    case int(GraphicsComponent::ReceiverProduct):
                        dynamic_cast<ReceiverProduct*>(m_graphicscomponent->getGraphicsComponent(i))->setPosX(int(p.x()));
                        dynamic_cast<ReceiverProduct*>(m_graphicscomponent->getGraphicsComponent(i))->setPosY(int(p.y()));
                        break;
                }
            }
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsFactory::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    for (unsigned long long i = 0; i<m_graphicscomponent->getSize();i++){
        if (m_graphicscomponent->getGraphicsComponent(i)->graphicsSelected()){
            notify(m_graphicscomponent->getGraphicsComponent(i));
        }
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}
