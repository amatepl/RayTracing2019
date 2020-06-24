#include "graphicsbuildingproduct.h"

GraphicsBuildingProduct::GraphicsBuildingProduct(QMenu* productmenu, QGraphicsScene *scene):
    m_scene(scene),m_productmenu(productmenu)
{
    QRectF rect(0,0,50,50);
    QPolygonF poly(rect);
    setPolygon(poly);
    setModel(concrete);
    m_extremities = poly;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    m_type = "building";

    draw();
}

GraphicsBuildingProduct::~GraphicsBuildingProduct(){

}

QPixmap GraphicsBuildingProduct::getImage(){
    QPixmap pixmap(100,100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 10));
    QRectF rect(0,0,100,100);
    painter.drawRect(rect);

    return pixmap;
}


bool GraphicsBuildingProduct::graphicsSelected(){
    return isSelected();
}

void GraphicsBuildingProduct::draw(){
    m_scene->addItem(this);
}

void GraphicsBuildingProduct::setModel(int model){
    QPen pen(Qt::black, 2);
    switch (model){
    case int(GraphicsBuildingProduct::brick) :
        pen.setColor(Qt::darkRed);
        setPen(pen);
        m_model = brick;
        break;
    case int(GraphicsBuildingProduct::concrete) :
        pen.setColor(Qt::gray);
        setPen(pen);
        m_model = concrete;
        break;
    case int (GraphicsBuildingProduct::none) :
        pen.setColor(Qt::black);
        setPen(pen);
        m_model = none;
        break;
    }
}

void GraphicsBuildingProduct::setExtremities(QVector<QPointF> extremities){
    m_extremities = extremities;
    setPolygon(QPolygonF(m_extremities));
}

void GraphicsBuildingProduct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    //m_graphicsfactory->clearSelection();
    setSelected(true);
    m_productmenu->exec(event->screenPos());
}

QVariant GraphicsBuildingProduct::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        m_observer->update(this);
    }
    return value;
}

void GraphicsBuildingProduct::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    //DialogReceiverProduct *dialogProduct = new DialogReceiverProduct(this);
}
