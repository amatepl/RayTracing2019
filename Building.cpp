#include "Building.h"

Building::Building(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, AbstractScene *scene):
    QRectF(x1,y1,x4-x1,y2-y1),m_scene(scene)
{

//    1----(4)----4
//    |           |
//   (1)         (3)
//    |           |
//    2----(2)----3


    //m_p1 = QPointF(x1,y1);m_p2 = QPointF(x2,y2);m_p3 = QPointF(x3,y3);m_p4 = QPointF(x4,y4);
    //m_initialPosition = topLeft();

//    Wall wall1(x1,y1,x2,y2,0.0,0.0,0.0,0),wall2(x2,y2,x3,y3,0.0,0.0,0.0,0),wall3(x3,y3,x4,y4,0.0,0.0,0.0,0),wall4(x4,y4,x1,y1,0.0,0.0,0.0,0);
    Wall *wall1 = new Wall(x1,y1,x2,y2,0.0,0.0,0.0,0);
    Wall *wall2 = new Wall(x2,y2,x3,y3,0.0,0.0,0.0,0);
    Wall *wall3 = new Wall(x3,y3,x4,y4,0.0,0.0,0.0,0);
    Wall *wall4 = new Wall(x4,y4,x1,y1,0.0,0.0,0.0,0);

    wall1->setBuilding(this);
    wall2->setBuilding(this);
    wall3->setBuilding(this);
    wall4->setBuilding(this);

    m_walls[0] = wall1;
    m_walls[1] = wall2;
    m_walls[2] = wall3;
    m_walls[3] = wall4;

    //QGraphicsRectItem graphicsBuidling((QRectF)*this);

    //m_view->draw(&graphicsBuidling);

    addToScene();

}

Building::Building(const QPointF &p1, const QPointF &p3, AbstractScene *scene): QRectF(p1,p3),m_scene(scene)
{

    //m_initialPosition = topLeft();

    QPointF p2(p1.x(),p3.y()), p4(p1.y(),p3.x());

    //m_p1 = p1;m_p2 = p2;m_p3 = p3;m_p4 = p4;

    //Wall wall1(p1,p2,0.0,0.0,0.0,0),wall2(p2,p3,0.0,0.0,0.0,0),wall3(p3,p4,0.0,0.0,0.0,0),wall4(p4,p1,0.0,0.0,0.0,0);
    Wall *wall1 = new Wall(p1,p2,0.0,0.0,0.0,0);
    wall1->setBuilding(this);
    Wall *wall2 = new Wall(p2,p3,0.0,0.0,0.0,0);
    wall2->setBuilding(this);
    Wall *wall3 = new Wall(p3,p4,0.0,0.0,0.0,0);
    wall3->setBuilding(this);
    Wall *wall4 = new Wall(p4,p1,0.0,0.0,0.0,0);
    wall4->setBuilding(this);


    m_walls[0] = wall1;
    m_walls[1] = wall2;
    m_walls[2] = wall3;
    m_walls[3] = wall4;

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
    m_walls[0]->~Wall();
    m_walls[1]->~Wall();
    m_walls[2]->~Wall();
    m_walls[3]->~Wall();
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

     m_scene->addToScene(m_graphicsBuilding);
    //m_scene->addItem(m_graphicsBuilding);

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
    moveWalls();
    cout<<"x: "<<x()<<"y: "<<y()<<endl;
}

void Building::moveWalls()
{
    m_walls[0]->setPoints(topLeft(),bottomLeft());
    m_walls[1]->setPoints(bottomLeft(),bottomRight());
    m_walls[2]->setPoints(bottomRight(),topRight());
    m_walls[3]->setPoints(topRight(),topLeft());

}

QPointF Building::closestPoint(const QPointF &point)
{
    array <QLineF,4> points = {QLineF(point, topLeft()),
                              QLineF(point, topRight()),
                              QLineF(point, bottomLeft()),
                              QLineF(point, bottomRight())};

    sort(points.begin(),points.end(),[](QLineF a, QLineF b){
       return a.length()<b.length();
    });
    return points[0].p2();
}

vector <Wall*>Building::nearestWalls(const QPointF &point)
{
    vector<Wall*> walls;
    if(point == topLeft()){

        walls.push_back(m_walls[3]);
        walls.push_back(m_walls[0]);
    }
    else if(point == bottomLeft()){
        walls.push_back(m_walls[0]);
        walls.push_back(m_walls[1]);
    }
    else if(point == bottomRight()){
        walls.push_back(m_walls[1]);
        walls.push_back(m_walls[2]);
    }
    else if(point == topRight()){
        walls.push_back(m_walls[2]);
        walls.push_back(m_walls[3]);
    }
    return walls;
}

Wall* Building::getWalls()
{
    return *m_walls;
}

QPolygonF Building::shadow(const QPointF &light){
    QPolygonF shadow;
    //shadow<<closestPoint(light);
    vector <QPointF> corners = extremities(light);
    //shadow<<corners.at(0);
    QLineF line1(light, corners.at(0));
    line1.setLength(50000);
    QLineF line2(light, corners.at(1));
    line2.setLength(50000);
    shadow<<closestPoint(light)
          <<corners.at(0)
          <<line1.p2()
          <<line2.p2()
          <<corners.at(1);

    return shadow;
}

vector <QPointF> Building::extremities(const QPointF &light){
    /*
     * Looking for the corners that will cast the shadow.
     * light    - ponctual source of light.
     */

    vector <Wall*> walls = nearestWalls(closestPoint(light));
    vector <QPointF> extremities;
    QPointF intersectionPoint;
    //cout<<"Number of walls: "<<walls.size()<<endl;
   if (walls.at(1)->intersect(QLineF(light,walls.at(0)->p1()),&intersectionPoint) == 1){
       extremities.push_back(walls.at(1)->p2());
       extremities.push_back(walls.at(1)->p1());
   }
   else if (walls.at(0)->intersect(QLineF(light,walls.at(1)->p2()),&intersectionPoint) == 1){
       extremities.push_back(walls.at(0)->p2());
       extremities.push_back(walls.at(0)->p1());
   }
   else {
       extremities.push_back(walls.at(1)->p2());
       extremities.push_back(walls.at(0)->p1());
   }
   return extremities;
}

QPointF Building::forDiffraction(Wall *wall, const QPointF &corner) const{
    QPointF p2;
    Wall *w = cornerSecondWall(wall,corner);
    if(w->p1() == corner){
        p2 = w->p2();
    }
    else{
        p2 = w->p1();
    }
    return p2;
}


Wall* Building::cornerSecondWall(Wall *wall,const QPointF &corner)const {
    /*
     * Get the second wall composing the corner of a building.
     * wall     - one of the walls at the corner
     * corner   - the position of the corner
     */

    bool cont = true;
    int i =0;
    while(i<4 && cont){
        if ((corner == m_walls[i]->p1() || corner == m_walls[i]->p2()) && wall != m_walls[i]){
            cont = false;
        }
        i+=1;
    }
    return m_walls[i-1];
}
