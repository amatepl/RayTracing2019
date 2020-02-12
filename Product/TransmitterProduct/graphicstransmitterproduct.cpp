#include "graphicstransmitterproduct.h"

GraphicsTransmitterProduct::GraphicsTransmitterProduct(int posX, int posY, double orientation,double power
                                                       ,unsigned long frequency,GraphicsFactory *graphicsfactory)
{
    QPixmap icon(":/Images/Transmitter1.png");
    setPixmap(icon);
    setPos(posX,posY);
    setOrientation(orientation);
    setOffset(-icon.width()/2,-icon.height()/2);
    setRotation(orientation);

    m_graphicsfactory = graphicsfactory;
    m_posx = posX;
    m_posy = posY;
    m_orientation = orientation;
    m_power = power;
    m_frequency = frequency;

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
    m_graphicsfactory->addItem(this);
}

int GraphicsTransmitterProduct::getPosX(){return m_posx;}

int GraphicsTransmitterProduct::getPosY() {return m_posy;}

double GraphicsTransmitterProduct::getOrientation() {return m_orientation;}

double GraphicsTransmitterProduct::getPower() {return m_power;}

unsigned long GraphicsTransmitterProduct::getFrequency() {return m_frequency;}

int GraphicsTransmitterProduct::getRow(){

}

int GraphicsTransmitterProduct::getColumn() {

}
double GraphicsTransmitterProduct::getAntennaDistance() {

}
int GraphicsTransmitterProduct::getModel() {

}

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

void GraphicsTransmitterProduct::setOrientation(double orientation)
{
    m_orientation = orientation;
    setRotation(orientation);
}

void GraphicsTransmitterProduct::setPower(double power)
{
    m_power = power;
}

void GraphicsTransmitterProduct::setFrequency(unsigned long frequency)
{
    m_frequency = frequency;
}

void GraphicsTransmitterProduct::setRow(int row){

}

void GraphicsTransmitterProduct::setColumn(int column) {

}

void GraphicsTransmitterProduct::setAntennaDistance(double distance) {

}

void  GraphicsTransmitterProduct::setModel(Model model) {

}
