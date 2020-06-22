#include "graphicscene.h"

GraphicScene::GraphicScene(QGraphicsView *view, WindowObservable *windowobservable, QMenu *productmenu)
{
    setSceneRect(0,0,5000,5000);
    m_view = view;
    m_productmenu = productmenu;
    m_view->setScene(this);
    m_windowobesrvable = windowobservable;
    m_mode = MoveItem;
}

GraphicScene::~GraphicScene(){}

void GraphicScene::setSceneFactory(SceneFactory *sceneFactory){
    m_sceneFactory = sceneFactory;
    m_mode = InsertItem;
}



// Overrides

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
                return;
    else if(m_sceneFactory != 0 && m_mode == InsertItem){
        QPointF p(event->scenePos());
        GraphicsComponent *graphicsComponent = m_sceneFactory->createGraphicsComponent(0,0,m_productmenu,this);
        graphicsComponent->setPosX(int(p.x()));
        graphicsComponent->setPosY(int(p.y()));
        m_windowobesrvable->answer(graphicsComponent);
        m_mode = MoveItem;
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
//    if(m_mode == MoveItem){
//        QPointF p(event->scenePos());

//    }

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseDoubleClickEvent(event);
}
