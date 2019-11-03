#include "mapview.h"

MapView::MapView(QMenu *itemMenu,QWidget *parent) : QGraphicsScene(parent)
{
    m_itemMenu = itemMenu;
    myMode = MoveItem;
    setSceneRect(QRect(0,0,3000,3000));
}

void MapView::setMode(Mode mode)
{
    myMode = mode;
}

void MapView::readExamples(const QString &fileName){
    QFile example(fileName);
    if (!example.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

    clear();
    QTextStream in(&example);
    int x1,y1,x2,y2,width,height,type;
    QString item;
    in >> width >> height;
    setSceneRect(QRectF(0,0,width,height));
    while (!in.atEnd()) {
        in >> item;
        if (item == "building") {
            in >> x1>> y1 >> width >> height >> type;
            QPointF pos(x1,y1);
            UsableObject *m_building = new BuildingModel(0,0,width,height,type);
            DialogableObject *m_dialog = new BuildingDialog();
            BuildingView *m_buildingView = new BuildingView(m_building,m_dialog,m_itemMenu);
            m_buildingView->changePos(pos);
            addItem(m_buildingView);
            m_viewableObject.push_back(m_buildingView);
        }
        else if (item == "wall") {
            in >> x1>> y1 >> x2 >> y2 >> type;
            QPointF pos(x2,y2);
            UsableObject *m_wallModel = new WallModel(0,0,x1,y1,type);
            DialogableObject *m_dialog = new WallDialog();
            WallView *m_wallView = new WallView(m_wallModel,m_dialog,m_itemMenu);
            m_wallView->changePos(pos);
            addItem(m_wallView);
            m_viewableObject.push_back(m_wallView);
        }
    }
    example.close();
}

void MapView::deleteObject()
{
    const QList<QGraphicsItem *> items = selectedItems();
    viewable=m_viewableObject.begin();
    for (unsigned long long i = 0; i <m_viewableObject.size(); i++){
        if (m_viewableObject.at(i)->isSelectedView()){
            delete(m_viewableObject.at(i));
            m_viewableObject.erase(viewable);
        }
        ++viewable;
    }
}


void MapView::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
            return;
    QPointF p(mouseEvent->scenePos());
    if (myMode == InsertAntenna)
    {
        UsableObject *m_antenna = new AntennaModel(0,0,20,20);
        DialogableObject *m_dialog = new AntennaDialog();
        AntennaView *m_antennaView = new AntennaView(m_antenna,m_dialog,m_itemMenu);
        addItem(m_antennaView);
        m_antennaView->changePos(p);
        m_viewableObject.push_back(m_antennaView);
        emit itemInserted(m_antennaView);
    }
    else if (myMode == InsertWall)
    {
        UsableObject *m_wall = new WallModel(0,0,0,20);
        DialogableObject *m_dialog = new WallDialog();
        WallView *m_wallView = new WallView(m_wall,m_dialog,m_itemMenu);
        addItem(m_wallView);
        m_wallView->changePos(p);
        m_viewableObject.push_back(m_wallView);
        emit itemInserted(m_wallView);
    }
    else if (myMode == InsertBuilding)
    {
        UsableObject *m_building = new BuildingModel(0,0,50,50);
        DialogableObject *m_dialog = new BuildingDialog();
        BuildingView *m_buildingView = new BuildingView(m_building,m_dialog,m_itemMenu);
        addItem(m_buildingView);
        m_buildingView->changePos(p);
        emit itemInserted(m_buildingView);
        m_viewableObject.push_back(m_buildingView);
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void MapView::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF p(mouseEvent->scenePos());
    if (myMode == MoveItem){
        const QList<QGraphicsItem *> items = selectedItems();
        for (unsigned long long i = 0; i <m_viewableObject.size(); i++){
            if (m_viewableObject.at(i)->isSelectedView()){
                m_viewableObject.at(i)->changePos(p);
            }
        }
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}
