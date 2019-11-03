#include "view/wallview.h"

WallView::WallView(UsableObject *wall, DialogableObject *dialog, QMenu *itemMenu) : QGraphicsLineItem()
{
    m_wallModel = wall;
    m_wallDialog = dialog;
    m_intProperties = wall->getIntValues();
    m_itemMenu = itemMenu;
    setLine((*m_intProperties)["x1"],(*m_intProperties)["y1"],
            (*m_intProperties)["x2"],(*m_intProperties)["y2"]);
    typeProperties((*m_intProperties)["type"]);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    connect(m_wallDialog,SIGNAL(propertiesChanged(map<string,int>*,map<string,double>*)),
            this,SLOT(propertiesChanged(map<string,int>*,map<string,double>*)));
}

WallView::~WallView(){
    cout << "Wall view has been removed" << endl;
    delete(m_wallDialog);
    delete(m_wallModel);
}

QPixmap WallView::image()
{
    QPixmap pixmap(50,50);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 10));
    painter.translate(25, 0);
    QLineF line(0,0,0,50);
    painter.drawLine(line);

    return pixmap;
}

void WallView::typeProperties(int type)
{
    QPen pen(Qt::black, 5);
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

void WallView::changePos(QPointF &pos){
    setPos(pos);
    int diffInX = int(pos.x())-(*m_intProperties)["x1"];
    int diffInY = int(pos.y())-(*m_intProperties)["y1"];
    (*m_intProperties)["x1"]=int(pos.x());
    (*m_intProperties)["y1"]=int(pos.y());
    (*m_intProperties)["x2"]=(*m_intProperties)["x2"]+diffInX;
    (*m_intProperties)["y2"]=(*m_intProperties)["y2"]+diffInY;
    m_wallModel->setIntValues(m_intProperties);
}

void WallView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_wallDialog->setIntValues(m_intProperties);
    m_wallDialog->setDoubleValues(m_wallModel->getDoubleValues());
    m_wallDialog->exec();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void WallView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_itemMenu->exec(event->screenPos());
}

void WallView::propertiesChanged(map<string,int>* intValues,map<string,double>* doubleValues)
{
    QPointF pos((*intValues)["x1"],(*intValues)["y1"]);
    setPos(pos);
    typeProperties((*intValues)["type"]);
    setLine(0,0,(*intValues)["x2"]-(*intValues)["x1"],(*intValues)["y2"]-(*intValues)["y1"]);
    m_intProperties = intValues;
    m_wallModel->setIntValues(m_intProperties);
    m_wallModel->setDoubleValues(doubleValues);
}

bool WallView::isSelectedView()
{
    return isSelected();
}

