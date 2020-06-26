#include "mathematicalbuildingproduct.h"

MathematicalBuildingProduct::MathematicalBuildingProduct(QVector<QPointF> points) : QPolygonF(points),
    m_posx(0),m_posy(0)
{
    //m_mathematicalfactory = mathematicalFactory;
    m_extremities = points;
    setModel("concrete");
    m_type = "Building";
    for(int i =0; i<size()-1;i++){
        Wall *wall = new Wall(this->at(i),this->at((i+1)%(size())),0.0,m_conductivity,m_permittivity,i);
        wall->setBuilding(this);
        m_walls.push_back(wall);
    }
}

MathematicalBuildingProduct::~MathematicalBuildingProduct(){
    for(int i=0;i<size();i++){
        delete m_walls.at(i);
    }
}

void MathematicalBuildingProduct::setExtremities(QVector<QPointF> extremities){
    m_extremities = extremities;
    QPolygonF poly = QPolygonF(m_extremities);
    swap(poly);
}

void MathematicalBuildingProduct::setModel(std::string model){
    m_model = model;
    if (model == "brick"){
        m_conductivity = 0.0014;
        m_permittivity = 4.6;
    }
    else if (model == "concrete"){
        m_conductivity = 0.014;
        m_permittivity = 5.0;
    }
}

void MathematicalBuildingProduct::update(QGraphicsItem *graphic){
    QPointF moveDirection = QPointF(graphic->x(),graphic->y()) - QPointF(m_posx,m_posy);

    cout<<"Move direction: "<<moveDirection.x()<<", "<<moveDirection.y()<<endl;
    cout<<"Graphic building: "<<graphic->x()<<", "<<graphic->y()<<endl;

    this->translate(moveDirection);
    cout<<"Math building: "<<m_posx<<", "<<m_posy<<endl;

    cout<<"Building position: "<<endl;
    for(int i=0;i<size();i++){
        cout<<this->at(i).x()<<", "<<this->at(i).y()<<endl;
    }
    cout<<"---------------------"<<endl;

    setPosX(graphic->scenePos().x());
    setPosY(graphic->scenePos().y());

    moveWalls(moveDirection);
    //m_extremities.swap(*this);

}

void MathematicalBuildingProduct::openDialog(){
    new DialogBuildingProduct(this);
}

void MathematicalBuildingProduct::newProperties(){
    m_graphic->notifyToGraphic(this,m_posx,m_posy);
}


void MathematicalBuildingProduct::moveToPosition(const QPointF &pos)
{
    //moveTopLeft(pos);
    QPointF moveDirection = pos - QPointF(m_posx,m_posy);
    moveWalls(moveDirection);
}

void MathematicalBuildingProduct::moveWalls(QPointF &moveDirection)
{
    for(int i=0;i<m_walls.size();i++){
        m_walls.at(i)->setPoints(m_walls.at(i)->p1() + moveDirection,m_walls.at(i)->p2() + moveDirection);
    }

}

QPointF MathematicalBuildingProduct::closestPoint(const QPointF &point)
{
    vector<QLineF> distances;

    for(int i=0;i<size()-1;i++){
        distances.push_back(QLineF(point,this->at(i)));
    }

    sort(distances.begin(),distances.end(),[](QLineF a, QLineF b){
       return a.length()<b.length();
    });
    return distances[0].p2();
}

vector <Wall*>MathematicalBuildingProduct::nearestWalls(const QPointF &point)
{
    vector<Wall*> walls;

    for(int i=0; i<size()-1;i++){
        if(point == m_walls.at(i)->p1() || point == m_walls.at(i)->p2()){
            walls.push_back(m_walls.at(i));
        }
    }
    return walls;
}

Wall* MathematicalBuildingProduct::getWalls()
{
//    return *m_walls;
}

QPolygonF MathematicalBuildingProduct::shadow(const QPointF &light){
    QPolygonF shadow;
    shadow<<closestPoint(light);
    vector <QPointF> corners = extremities(light);
    shadow<<corners.at(0);
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

vector <QPointF> MathematicalBuildingProduct::extremities(const QPointF &light){
    /*
     * Looking for the corners that will cast the shadow.
     * light    - ponctual source of light.
     */

    vector <Wall*> walls = nearestWalls(closestPoint(light));
    vector <QPointF> extremities;
    vector <QPointF> nonCommonPoints;
    QPointF intersectionPoint;

    if(walls.at(1)->p2() != walls.at(0)->p2() && walls.at(1)->p2() != walls.at(0)->p1()){
        nonCommonPoints.push_back(walls.at(1)->p2());
    }
    else{
        nonCommonPoints.push_back(walls.at(1)->p1());
    }

    if(walls.at(0)->p1() != walls.at(1)->p2() && walls.at(0)->p1() != walls.at(1)->p1()){
        nonCommonPoints.push_back(walls.at(0)->p1());
    }
    else{
        nonCommonPoints.push_back(walls.at(0)->p2());
    }


    if (walls.at(1)->intersect(QLineF(light,nonCommonPoints.at(1)),&intersectionPoint) == 1){
        extremities.push_back(walls.at(1)->p2());
        extremities.push_back(walls.at(1)->p1());
    }
    else if (walls.at(0)->intersect(QLineF(light,nonCommonPoints.at(0)),&intersectionPoint) == 1){
        extremities.push_back(walls.at(0)->p2());
        extremities.push_back(walls.at(0)->p1());
    }
    else {
         extremities = nonCommonPoints;
    }

    //cout<<"Number of walls: "<<walls.size()<<endl;
//   if (walls.at(1)->intersect(QLineF(light,walls.at(0)->p1()),&intersectionPoint) == 1){
//       extremities.push_back(walls.at(1)->p2());
//       extremities.push_back(walls.at(1)->p1());
//   }
//   else if (walls.at(0)->intersect(QLineF(light,walls.at(1)->p2()),&intersectionPoint) == 1){
//       extremities.push_back(walls.at(0)->p2());
//       extremities.push_back(walls.at(0)->p1());
//   }
//   else {
//        if(walls.at(1)->p2() != walls.at(0)->p2() && walls.at(1)->p2() != walls.at(0)->p1()){
//            extremities.push_back(walls.at(1)->p2());
//        }
//        else{
//            extremities.push_back(walls.at(1)->p1());
//        }

//        if(walls.at(0)->p1() != walls.at(1)->p2() && walls.at(0)->p1() != walls.at(1)->p1()){
//            extremities.push_back(walls.at(0)->p1());
//        }
//        else{
//            extremities.push_back(walls.at(0)->p2());
//        }


//   }
   return extremities;
}

QPointF MathematicalBuildingProduct::forDiffraction(Wall *wall, const QPointF &corner) const{
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


Wall* MathematicalBuildingProduct::cornerSecondWall(Wall *wall,const QPointF &corner)const {
    /*
     * Get the second wall composing the corner of a building.
     * wall     - one of the walls at the corner
     * corner   - the position of the corner
     */

    bool cont = true;
    int i =0;
    while(i<size() && cont){
        if ((corner == m_walls[i]->p1() || corner == m_walls[i]->p2()) && wall != m_walls[i]){
            cont = false;
        }
        i+=1;
    }
    return m_walls[i-1];
}
