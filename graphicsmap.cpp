#include "graphicsmap.h"

GraphicsMap::GraphicsMap(QGraphicsView *view, AppInterface *app, QMenu *productmenu)
{
    int width = 700;
    int height = 700;
    setSceneRect(0,0,width, height);
    m_view = view;
    //m_view->setFixedSize(width+2*m_view->frameWidth(), height+2*m_view->frameWidth());
    m_productmenu = productmenu;
    m_view->setScene(this);
    m_app = app;
    m_mode = MoveItem;
}

GraphicsMap::~GraphicsMap(){}

void GraphicsMap::setSceneFactory(SceneFactory *sceneFactory){
    m_sceneFactory = sceneFactory;
    m_mode = InsertItem;
}

void GraphicsMap::deleteItem(){
    QList<QGraphicsItem *> items = selectedItems();
    foreach (QGraphicsItem* item, items) {
        removeItem(item);
        m_app->deleteAnswer(dynamic_cast<GraphicsProduct*>(item));
        delete item;
    }
}

// Overrides

void GraphicsMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
                return;
    else if(m_sceneFactory != 0 && m_mode == InsertItem){
        QPointF p(event->scenePos());
        GraphicsProduct *graphicsproduct = m_sceneFactory->createGraphicsProduct(int(p.x()),int(p.y()));
        m_app->answer(graphicsproduct);
        m_mode = MoveItem;
    }
    m_app->resetToolInfo();
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsMap::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QPointF pos = event->scenePos();
    m_app->moveMouse(pos);
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsMap::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseDoubleClickEvent(event);
}
