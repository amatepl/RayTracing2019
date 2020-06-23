#include "graphicstransmitterproduct.h"

GraphicsTransmitterProduct::GraphicsTransmitterProduct(int posX, int posY, double orientation, QMenu* productmenu, QGraphicsScene *scene)
{
    QPixmap icon(":/Images/Transmitter1.png");
    setPixmap(icon);
    setPos(posX,posY);
    //setOrientation(orientation);
    setOffset(-icon.width()/2,-icon.height()/2);
    setRotation(orientation);


    m_productmenu = productmenu;
    m_posx = posX;
    m_posy = posY;
    m_orientation = orientation;
    m_scene = scene;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    draw();

}

GraphicsTransmitterProduct::~GraphicsTransmitterProduct(){

}

QPixmap GraphicsTransmitterProduct::getImage(){
    QPixmap icon(":/Images/Transmitter1.png");
    return icon;
}

int GraphicsTransmitterProduct::getType(){
    return int(GraphicsComponent::TransmitterProduct);
}

bool GraphicsTransmitterProduct::graphicsSelected() {
    return isSelected();
}

void GraphicsTransmitterProduct::draw(){
    m_scene->addItem(this);
}

int GraphicsTransmitterProduct::getPosX(){return m_posx;}

int GraphicsTransmitterProduct::getPosY() {return m_posy;}



void GraphicsTransmitterProduct::setPosX(int posX)
{
    m_posx = posX;
    setPos(m_posx,m_posy);
}

void GraphicsTransmitterProduct::setPosY(int posY)
{
    m_posy = posY;
    setPos(m_posx,m_posy);
}



void GraphicsTransmitterProduct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
        //m_graphicsfactory->clearSelection();
        setSelected(true);
        m_productmenu->exec(event->screenPos());
}

void GraphicsTransmitterProduct::setMathematicalComponent(MathematicalComponent *mathematicalComponent){
    m_mathematicalComponent = mathematicalComponent;
}

MathematicalComponent* GraphicsTransmitterProduct::toMathematicalComponent(){
    return m_mathematicalComponent;
}
