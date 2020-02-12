#include "graphicsreceiverproduct.h"

GraphicsReceiverProduct::GraphicsReceiverProduct(int posX, int posY,unsigned long frequency,GraphicsFactory *graphicsfactory)
{
    QPixmap icon(":/Images/Receiver1.png");
    setPixmap(icon);
    setPos(posX,posY);
    setOffset(-icon.width()/2,-icon.height()/2);

    m_graphicsfactory = graphicsfactory;
    m_posx = posX;
    m_posy = posY;
    m_frequency = frequency;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    draw();
}

GraphicsReceiverProduct::~GraphicsReceiverProduct(){

}

QPixmap GraphicsReceiverProduct::getImage(){
    QPixmap icon(":/Images/Receiver1.png");
    return icon;
}

int GraphicsReceiverProduct::getType(){
    return int(GraphicsComponent::ReceiverProduct);
}

bool GraphicsReceiverProduct::graphicsSelected() {
    return isSelected();
}

void GraphicsReceiverProduct::draw(){
    m_graphicsfactory->addItem(this);
}

int GraphicsReceiverProduct::getPosX(){return m_posx;}

int GraphicsReceiverProduct::getPosY() {return m_posy;}


double GraphicsReceiverProduct::getPower() {return m_power;}

unsigned long GraphicsReceiverProduct::getFrequency() {return m_frequency;}

void GraphicsReceiverProduct::setPosX(int posX)
{
    m_posx = posX;
    setPos(m_posx,m_posy);
}

void GraphicsReceiverProduct::setPosY(int posY)
{
    m_posy = posY;
    setPos(m_posx,m_posy);
}

void GraphicsReceiverProduct::setFrequency(unsigned long frequency)
{
    m_frequency = frequency;
}
