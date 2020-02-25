#include "graphicsbuildingproduct.h"

GraphicsBuildingProduct::GraphicsBuildingProduct(int posX, int posY, double orientation, GraphicsFactory *graphicsfactory):
    m_graphicsfactory(graphicsfactory),m_posx(posX),m_posy(posY),m_orientation(orientation)
{
    QRectF rect(m_posx,m_posy,50,50);
    QPolygonF poly(rect);
    setPolygon(poly);
    setModel(concrete);
    setOrientation(m_orientation);
    setPos(m_posx,m_posy);
    m_conductivity = 0.0;
    m_permittivity = 0.0;
    m_extremities = poly;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

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

int GraphicsBuildingProduct::getType(){
    return int(GraphicsComponent::BuildingProduct);
}

bool GraphicsBuildingProduct::graphicsSelected(){
    return isSelected();
}

void GraphicsBuildingProduct::draw(){
    m_graphicsfactory->addItem(this);
}

int GraphicsBuildingProduct::getPosX(){
    return m_posx;
}

int GraphicsBuildingProduct::getPosY(){
    return m_posy;
}

double GraphicsBuildingProduct::getOrientation(){
    return m_orientation;
    setOrientation(m_orientation);
}

double GraphicsBuildingProduct::getConductivity(){
    return m_conductivity;
}

double GraphicsBuildingProduct::getPermittivity(){
    return m_permittivity;
}

int GraphicsBuildingProduct::getModel(){
    return int(m_model);
}

QVector<QPointF> GraphicsBuildingProduct::getExtremities(){
    return m_extremities;
}

void GraphicsBuildingProduct::setPosX(int posX){
    m_posx = posX;
    setPos(m_posx,m_posy);
}
void GraphicsBuildingProduct::setPosY(int posY){
    m_posy = posY;
    setPos(m_posx,m_posy);
}
void GraphicsBuildingProduct::setOrientation(double orientation){
    m_orientation = orientation;
}
void GraphicsBuildingProduct::setConductivity(double sigma){
    m_conductivity = sigma;
}
void GraphicsBuildingProduct::setPermittivity(double eps){
    m_permittivity = eps;
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
