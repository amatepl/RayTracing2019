#include "graphicstransmitterproduct.h"

GraphicsTransmitterProduct::GraphicsTransmitterProduct(QMenu* productmenu, QGraphicsScene *scene)
{
    QPixmap icon(":/Images/Transmitter1.png");
    setPixmap(icon);
    setOffset(-icon.width()/2,-icon.height()/2);


    m_productmenu = productmenu;
    m_scene = scene;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    m_type = "transmitter";
    draw();

}

GraphicsTransmitterProduct::~GraphicsTransmitterProduct(){

}

QPixmap GraphicsTransmitterProduct::getImage(){
    QPixmap icon(":/Images/Transmitter1.png");
    return icon;
}


bool GraphicsTransmitterProduct::graphicsSelected() {
    return isSelected();
}

void GraphicsTransmitterProduct::draw(){
    m_scene->addItem(this);
}


void GraphicsTransmitterProduct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
        //m_graphicsfactory->clearSelection();
        setSelected(true);
        m_productmenu->exec(event->screenPos());
}

QVariant GraphicsTransmitterProduct::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        //m_mathematicalProduct->setPosX(pos().x());
        //m_mathematicalProduct->setPosY(pos().y());
        m_observer->update(this);
    }
    return value;
}

void GraphicsTransmitterProduct::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    //DialogReceiverProduct *dialogProduct = new DialogReceiverProduct(this);
}
