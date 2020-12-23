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
    setTransformOriginPoint(QPointF(0.0,0.0));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    m_type = "car";
    draw();
}

GraphicsCarProduct::GraphicsCarProduct(const QPolygonF &poly, QMenu *productmenu, QGraphicsScene *scene):
    m_scene(scene),m_productmenu(productmenu)
{
    QPolygonF graphic = poly;
    QPointF p0 = graphic.at(0);
//    for (int i = 0; i < graphic.size()-1; i++){
//        if(p0.manhattanLength() > graphic.at(i+1).manhattanLength()){
//            p0 = graphic.at(i+1);
//        }
//    }
    graphic.translate(-p0);
    setPolygon(graphic);
    QLinearGradient linearGrad(graphic.at(0),graphic.at(3));
    linearGrad.setColorAt(0, Qt::white);
    linearGrad.setColorAt(0.5, Qt::blue);
    linearGrad.setColorAt(1, Qt::darkBlue);
    setBrush(linearGrad);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    m_type = "car";
    draw();
}

GraphicsCarProduct::~GraphicsCarProduct(){
    cout << "Graphics Car Product Deleted." << endl;
    delete m_observer;
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

void GraphicsCarProduct::notifyToGraphic(QPolygonF * rect, int centerx, int centery, double orientation){
    QPolygonF graphic = *rect;
    graphic.translate(-rect->at(0)-QPointF(11,11));
    setPolygon(graphic);
    setRotation(orientation);
    setPos(centerx, centery);
}

void GraphicsCarProduct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
//    m_graphicsfactory->clearSelection();
    setSelected(true);
    m_productmenu->exec(event->screenPos());
}

QVariant GraphicsCarProduct::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged
        || change == QGraphicsItem::ItemTransformHasChanged
        || change == QGraphicsItem::ItemRotationHasChanged) {
//        m_observer->update(this);
    }
    return value;
}

void GraphicsCarProduct::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/){
    m_observer->openDialog();
}

void GraphicsCarProduct::notifyToGraphicSig(QPolygonF *rect, int centerx, int centery, double /*orientation*/)
{
    QPolygonF graphic = *rect;
    QPointF p0 = graphic.at(0);

    for (int i = 0; i < graphic.size()-1; i++) {
        if (p0.manhattanLength() > graphic.at(i+1).manhattanLength()) {
            p0 = graphic.at(i+1);
        }
    }
    graphic.translate(-p0-QPointF(11.0,11.0));
    p0 = graphic.at(0);
    QPointF p1 = graphic.at(2);
    QLineF diag(p0,p1);
    QPointF center = diag.center();
    graphic.translate(-center);
    QLinearGradient linearGrad(graphic.at(0),graphic.at(3));
    linearGrad.setColorAt(0, Qt::white);
    linearGrad.setColorAt(0.5, Qt::blue);
    linearGrad.setColorAt(1, Qt::darkBlue);
    setBrush(linearGrad);
    setPolygon(graphic);
    setPos(centerx, centery);
}
