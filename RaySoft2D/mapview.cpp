#include "mapview.h"

MapView::MapView(QWidget *parent) : QGraphicsScene(parent)
{
    myMode = MoveItem;
}

void MapView::setMode(Mode mode)
{
    myMode = mode;
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
        AntennaView *m_antennaView = new AntennaView(m_antenna,m_dialog);
        addItem(m_antennaView);
        m_antennaView->changePos(p);
        m_viewableObject.push_back(m_antennaView);
        emit itemInserted(m_antennaView);
    }
    else if (myMode == InsertWall)
    {
        UsableObject *m_wall = new WallModel(0,0,0,20);
        DialogableObject *m_dialog = new WallDialog();
        WallView *m_wallView = new WallView(m_wall,m_dialog);
        addItem(m_wallView);
        m_wallView->changePos(p);
        m_viewableObject.push_back(m_wallView);
        emit itemInserted(m_wallView);
    }
    else if (myMode == InsertBuilding)
    {
        UsableObject *m_building = new BuildingModel(0,0,50,50);
        DialogableObject *m_dialog = new BuildingDialog();
        BuildingView *m_buildingView = new BuildingView(m_building,m_dialog);
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
