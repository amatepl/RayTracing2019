#include "Building.h"

Building::Building(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, QGraphicsScene *scene):
    QRectF(x1,y1,x4-x1,y2-y1),m_scene(scene)
{

//    1----(4)----4
//    |           |
//   (1)         (3)
//    |           |
//    2----(2)----3

    //m_scene = scene;

    //m_p1 = QPointF(x1,y1);m_p2 = QPointF(x2,y2);m_p3 = QPointF(x3,y3);m_p4 = QPointF(x4,y4);
    //m_initialPosition = topLeft();

    Wall wall1(x1,y1,x2,y2,0.0,0.0,0.0,0),wall2(x2,y2,x3,y3,0.0,0.0,0.0,0),wall3(x3,y3,x4,y4,0.0,0.0,0.0,0),wall4(x4,y4,x1,y1,0.0,0.0,0.0,0);

    m_walls[0] = &wall1;
    m_walls[1] = &wall2;
    m_walls[2] = &wall3;
    m_walls[3] = &wall4;

    //QGraphicsRectItem graphicsBuidling((QRectF)*this);

    //m_view->draw(&graphicsBuidling);
//    QPen outlinePen(QColor(0, 0, 0, 255));
//    outlinePen.setWidth(2);

//    QBrush brush(Qt::BDiagPattern);



//    QGraphicsRectItem *rect = scene->addRect(*this, outlinePen, brush );
//    rect->setFlag(QGraphicsItem::ItemIsMovable, true);
//    rect->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    rect->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    addToScene();

}

Building::Building(const QPointF &p1, const QPointF &p3, QGraphicsScene *scene): QRectF(p1,p3),m_scene(scene)
{
    //m_view = view;
    //m_scene = scene;
    //m_initialPosition = topLeft();

    QPointF p2(p1.x(),p3.y()), p4(p1.y(),p3.x());

    //m_p1 = p1;m_p2 = p2;m_p3 = p3;m_p4 = p4;

    Wall wall1(p1,p2,0.0,0.0,0.0,0),wall2(p2,p3,0.0,0.0,0.0,0),wall3(p3,p4,0.0,0.0,0.0,0),wall4(p4,p1,0.0,0.0,0.0,0);

    m_walls[0] = &wall1;
    m_walls[1] = &wall2;
    m_walls[2] = &wall3;
    m_walls[3] = &wall4;

    //QGraphicsRectItem graphicsBuidling((QRectF)*this);

    addToScene();


    //m_view->draw(&graphicsBuidling);
//    QPen outlinePen(QColor(0, 0, 0, 255));
//    outlinePen.setWidth(2);

//    QBrush brush(Qt::BDiagPattern);

//    QGraphicsRectItem *rect = scene->addRect(*this, outlinePen, brush );
//    rect->setFlag(QGraphicsItem::ItemIsMovable, true);
//    rect->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    rect->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

}

Building::~Building(void){
    m_graphicsBuilding->~GraphicsBuilding();
}

void Building::addToScene()
{
//    QPen outlinePen(QColor(0, 0, 0, 255));
//    outlinePen.setWidth(2);

//    QBrush brush(Qt::BDiagPattern);

    //GraphicsBuilding *rect = new GraphicsBuilding(*this, this);
    //m_graphicsBuilding = new GraphicsBuilding(*this, this);
    m_graphicsBuilding = new GraphicsBuilding(0,0,width(),height(), this);

//    m_graphicsBuilding->setBrush(brush);
//    m_graphicsBuilding->setPen(outlinePen);
     m_graphicsBuilding->setPos(topLeft());
   //  m_graphicsBuilding->setPos();
    //QGraphicsItem *it = m_graphicsBuilding->parentItem();
    m_scene->addItem(m_graphicsBuilding);

    //cout<<"Before x: "<<m_graphicsBuilding->scenePos().x()<< " y: "<<m_graphicsBuilding->scenePos().y()<<endl;
    //cout<<"Before x: "<<m_graphicsBuilding->mapToScene(m_graphicsBuilding->pos()).x()<<" y: "<<m_graphicsBuilding->scenePos().y()<<endl;
//    m_graphicsBuilding->setFlag(QGraphicsItem::ItemIsMovable, true);
//    m_graphicsBuilding->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    m_graphicsBuilding->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void Building::moveToPosition(const QPointF &pos)
{
    cout<<"Before x: "<<x()<<"y: "<<y()<<endl;
    moveTopLeft(pos);
    cout<<"x: "<<x()<<"y: "<<y()<<endl;
}
