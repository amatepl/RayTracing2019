#include "graphicscarproduct.h"

GraphicsCarProduct::GraphicsCarProduct(QMenu *productmenu,QGraphicsScene *scene):
    m_scene(scene),m_productmenu(productmenu)
{
    // QPixmap icon(":/Images/Car.png");
    // setPixmap(icon);
    // setOffset(-icon.width()/2,-icon.height()/2);
    QPolygonF poly = QPolygonF();
    poly << QPointF(0.0,0.0)
         << QPointF(22.0,0.0)
         << QPointF(22.0,22.0)
         << QPointF(0.0,22.0)
         << QPointF(0.0,0.0);
    setPolygon(poly);
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(22.0, 22));
    linearGrad.setColorAt(0, Qt::black);
    linearGrad.setColorAt(1, Qt::white);
    //QColor color = QColor(255,0,0);
    setBrush(linearGrad);
    setTransformOriginPoint(QPointF(11.0,11.0));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    m_type = "car";
    draw();
}

GraphicsCarProduct::~GraphicsCarProduct(){

}

QPixmap GraphicsCarProduct::getImage(){
    QPixmap icon(":/Images/Car.png");
    return icon;
}


bool GraphicsCarProduct::graphicsSelected(){
    return isSelected();
}

void GraphicsCarProduct::draw(){
    m_scene->addItem(this);
}


void GraphicsCarProduct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
//    m_graphicsfactory->clearSelection();
    setSelected(true);
    m_productmenu->exec(event->screenPos());
}

QVariant GraphicsCarProduct::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged ||
        change == QGraphicsItem::ItemTransformHasChanged ||
        change == QGraphicsItem::ItemRotationHasChanged) {
        m_observer->update(this);
    }
    return value;
}

void GraphicsCarProduct::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    m_observer->openDialog();
}

void GraphicsCarProduct::notifyToGraphicSig(QPolygonF *rect, int centerx, int centery, double orientation){
    cout<<"Center position: "<<centerx<<", "<<centery<<endl;
    setPolygon(polygon());
    //setPos(centerx,centery);
    //setX(centerx);
    //setY(centery);
    //setRotation(orientation);
//    cout<<"Center position: "<<centerx<<", "<<centery<<endl;
    setPos(centerx - 11, centery - 11);
}
