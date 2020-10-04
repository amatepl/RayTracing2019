#include "graphicsbuilding.h"

GraphicsBuilding::GraphicsBuilding(QMenu* productmenu, QGraphicsScene *scene):
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


GraphicsBuilding::GraphicsBuilding(QPolygonF poly,QMenu* productmenu, QGraphicsScene *scene):QGraphicsPolygonItem(poly),
    m_scene(scene),m_productmenu(productmenu)
{
    //QRectF rect(0,0,50,50);
    //QPolygonF poly(rect);
    //setPolygon(poly);
    setModel("concrete");
    m_extremities = poly;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    m_type = "building";
    setBrush(QBrush(QColor(Qt::white)));

    draw();
}

GraphicsBuilding::~GraphicsBuilding(){
    cout << "Graphics Building Product Deleted." << endl;
    delete m_observer;
}

QPixmap GraphicsBuilding::getImage(){
    QPixmap pixmap(100,100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 10));
    QRectF rect(0,0,100,100);
    painter.drawRect(rect);

    return pixmap;
}


bool GraphicsBuilding::graphicsSelected(){
    return isSelected();
}

void GraphicsBuilding::draw(){
    m_scene->addItem(this);
}

void GraphicsBuilding::setModel(std::string model){
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

void GraphicsBuilding::setExtremities(QVector<QPointF> extremities){
    m_extremities = extremities;
    setPolygon(QPolygonF(m_extremities));
}

void GraphicsBuilding::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    //m_graphicsfactory->clearSelection();
    setSelected(true);
    m_productmenu->exec(event->screenPos());
}

QVariant GraphicsBuilding::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        m_observer->update(this);
    }
    return value;
}

void GraphicsBuilding::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/){
    m_observer->openDialog();
}

void GraphicsBuilding::notifyToGraphic(QPolygonF *poly, int posX, int posY){
    setPolygon(*poly);
    setX(posX);
    setY(posY);
    setModel(m_observer->changeAppearance());
    std::cout << posX << " and " << posY << std::endl;
}
