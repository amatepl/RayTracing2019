#include "view/antennaview.h"

AntennaView::AntennaView(UsableObject *antenna, DialogableObject *dialog, QMenu *itemMenu) : QGraphicsPixmapItem()
{
    m_antennaModel = antenna;
    m_antennaDialog = dialog;
    m_intProperties = antenna->getIntValues();
    m_itemMenu = itemMenu;
    icon = new QPixmap(":/images/antenna.png");
    setPixmap(*icon);

    setOffset(-icon->width()/2,-icon->height()/2);
    setScale(scale()/icon->width()*(*m_intProperties)["width"]);
    setRotation((*m_intProperties)["orientation"]);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    connect(m_antennaDialog,SIGNAL(propertiesChanged(map<string,int>*,map<string,double>*)),
            this,SLOT(propertiesChanged(map<string,int>*,map<string,double>*)));
}

AntennaView::~AntennaView(){
    cout << "Antenna view has been removed" << endl;
    delete(m_antennaDialog);
    delete(m_antennaModel);
}

QPixmap AntennaView::image()
{
    QPixmap icon(":/images/antenna.png");
    return icon;
}

void AntennaView::changePos(QPointF &pos){
    setPos(pos);
    (*m_intProperties)["x center"]=int(pos.x());
    (*m_intProperties)["y center"]=int(pos.y());
    m_antennaModel->setIntValues(m_intProperties);
}

void AntennaView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_itemMenu->exec(event->screenPos());
}

void AntennaView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_antennaDialog->setIntValues(m_intProperties);
    m_antennaDialog->exec();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void AntennaView::propertiesChanged(map<string,int>* intValues,map<string,double>* doubleValues)
{
    QPointF pos((*intValues)["x center"],(*intValues)["y center"]);
    setPos(pos);
    setRotation((*intValues)["orientation"]);
    m_intProperties = intValues;
    m_antennaModel->setIntValues(m_intProperties);
}

bool AntennaView::isSelectedView()
{
    return isSelected();
}
