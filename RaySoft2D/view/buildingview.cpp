#include "view/buildingview.h"

BuildingView::BuildingView(UsableObject *building, DialogableObject *dialog, QMenu *itemMenu) : QGraphicsRectItem()
{
    m_buildingModel = building;
    m_buildingDialog = dialog;
    m_intProperties = building->getIntValues();
    m_itemMenu = itemMenu;
    setRect((*m_intProperties)["top left x"],(*m_intProperties)["top left y"],
            (*m_intProperties)["width"],(*m_intProperties)["height"]);
    setRotation((*m_intProperties)["orientation"]);
    typeProperties((*m_intProperties)["type"]);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    connect(m_buildingDialog,SIGNAL(propertiesChanged(map<string,int>*,map<string,double>*)),
            this,SLOT(propertiesChanged(map<string,int>*,map<string,double>*)));
}

BuildingView::~BuildingView(){
    cout << "Building view has been removed" << endl;
    delete(m_buildingDialog);
    delete(m_buildingModel);
}

QPixmap BuildingView::image()
{
    QPixmap pixmap(50,50);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 10));
    QRectF rect(0,0,50,50);
    painter.drawRect(rect);

    return pixmap;
}

void BuildingView::typeProperties(int type)
{
    QPen pen(Qt::black, 2);
    switch(type){
        case 1 :
            pen.setColor(Qt::gray);
            setPen(pen);
            break;
        case 2 :
            pen.setColor(Qt::darkRed);
            setPen(pen);
        break;
        case 3:
            pen.setColor(Qt::black);
            setPen(pen);
        break;
    }
}

void BuildingView::changePos(QPointF &pos){
    setPos(pos);
    (*m_intProperties)["top left x"]=int(pos.x());
    (*m_intProperties)["top left y"]=int(pos.y());
    m_buildingModel->setIntValues(m_intProperties);
}

void BuildingView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_buildingDialog->setIntValues(m_intProperties);
    m_buildingDialog->setDoubleValues(m_buildingModel->getDoubleValues());
    m_buildingDialog->exec();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void BuildingView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_itemMenu->exec(event->screenPos());
}

void BuildingView::propertiesChanged(map<string,int>* intValues,map<string,double>* doubleValues)
{
    QPointF pos((*intValues)["top left x"],(*intValues)["top left y"]);
    setPos(pos);
    setRotation((*intValues)["orientation"]);
    typeProperties((*intValues)["type"]);
    setRect(0,0,(*intValues)["width"],(*intValues)["height"]);
    m_intProperties = intValues;
    m_buildingModel->setIntValues(m_intProperties);
    m_buildingModel->setDoubleValues(doubleValues);
}

bool BuildingView::isSelectedView()
{
    return isSelected();
}
