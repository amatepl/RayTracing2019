#include "graphicsreceiverproduct.h"

GraphicsReceiverProduct::GraphicsReceiverProduct(int posX, int posY,unsigned long frequency, bool enable, QMenu *menuproduct
                                                 ,GraphicsFactory *graphicsfactory)
{
    m_productmenu = menuproduct;
    m_sizex = 10;
    m_sizey = 10;
    m_graphicsfactory = graphicsfactory;
    m_posx = posX;
    m_posy = posY;
    enableReceiver(enable);
    m_frequency = frequency;

    draw();
}

GraphicsReceiverProduct::~GraphicsReceiverProduct(){

}

void GraphicsReceiverProduct::enableReceiver(bool enable){
    if (enable) {
        QPixmap icon(":/Images/Receiver1.png");
        setPixmap(icon);
        setOffset(-icon.width()/2,-icon.height()/2);
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }
    else {
        QPixmap pixmap(m_sizex,m_sizey);
        pixmap.fill(scaleColor(10,24,17));
        QPainter painter(&pixmap);
        painter.setPen(QPen(Qt::black, 0));
        setPixmap(pixmap);
        setOffset(-m_sizex/2,-m_sizey/2);
        setPos(m_posx,m_posy);
    }
}

QColor GraphicsReceiverProduct::scaleColor(double min, double max, double value){
    double interval = (max-min)/2;
    QColor color;
    if (value < min+interval){
       color.setRgb(255*(value-min)/interval,0,255);
    }
    else {
        color.setRgb(255,0,255*(max-value)/interval);
    }
    return color;
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

void GraphicsReceiverProduct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    m_graphicsfactory->clearSelection();
    setSelected(true);
    m_productmenu->exec(event->screenPos());
}
