#include "graphicstreeproduct.h"

GraphicsTreeProduct::GraphicsTreeProduct(QMenu * productmenu, QGraphicsScene *scene):
    m_scene(scene),m_productmenu(productmenu)
{
    QPixmap icon(":/Images/Tree.png");
    setPixmap(icon);
    setOffset(-icon.width()/2,-icon.height()/2);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    m_type = "tree";
    draw();
}

GraphicsTreeProduct::~GraphicsTreeProduct(){

}

QPixmap GraphicsTreeProduct::getImage(){
    QPixmap icon(":/Images/Tree.png");
    return icon;
}

void GraphicsTreeProduct::draw() {
    m_scene->addItem(this);
}

bool GraphicsTreeProduct::graphicsSelected() {
    return isSelected();
}

void GraphicsTreeProduct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    //m_graphicsfactory->clearSelection();
    setSelected(true);
    m_productmenu->exec(event->screenPos());
}

QVariant GraphicsTreeProduct::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        m_observer->update(this);
    }
    return value;
}

void GraphicsTreeProduct::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    m_observer->openDialog();
}

void GraphicsTreeProduct::notifyToGraphic(QPolygonF *poly, int centerx, int centery){
    setPos(centerx,centery);
}


