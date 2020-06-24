#include "graphicsbuildingproduct.h"

GraphicsBuildingProduct::GraphicsBuildingProduct(QMenu* productmenu, QGraphicsScene *scene):
    m_scene(scene),m_productmenu(productmenu)
{
    QRectF rect(0,0,50,50);
    QPolygonF poly(rect);
    setPolygon(poly);
    setModel("concrete");
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

void GraphicsBuildingProduct::setModel(std::string model){
    QPen pen(Qt::black, 2);
    if (model == "brick") {
        pen.setColor(Qt::darkRed);
        setPen(pen);
    }
    else if (model == "concrete"){
        pen.setColor(Qt::gray);
        setPen(pen);
    }
    else {
        pen.setColor(Qt::black);
        setPen(pen);
    }
    m_model = model;
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
    m_observer->openDialog();
}

void GraphicsBuildingProduct::notifyToGraphic(QPolygonF *poly, int posX, int posY){
    setPolygon(*poly);
    setX(posX);
    setY(posY);
    setModel(m_observer->changeAppearance());
}
