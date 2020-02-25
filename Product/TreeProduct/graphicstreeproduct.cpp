#include "graphicstreeproduct.h"

GraphicsTreeProduct::GraphicsTreeProduct(int posX, int posY,GraphicsFactory *graphicsfactory):
    m_graphicsfactory(graphicsfactory),m_posx(posX),m_posy(posY)
{
    QPixmap icon(":/Images/Tree.png");
    setPos(m_posx,m_posy);
    setPixmap(icon);
    setOffset(-icon.width()/2,-icon.height()/2);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    draw();
}

GraphicsTreeProduct::~GraphicsTreeProduct(){

}

QPixmap GraphicsTreeProduct::getImage(){
    QPixmap icon(":/Images/Tree.png");
    return icon;
}

void GraphicsTreeProduct::draw() {
    m_graphicsfactory->addItem(this);
}

bool GraphicsTreeProduct::graphicsSelected() {
    return isSelected();
}

int GraphicsTreeProduct::getType() {
    return int(GraphicsComponent::TreeProduct);
}

int GraphicsTreeProduct::getPosX() {
    return m_posx;
}

int GraphicsTreeProduct::getPosY() {
    return m_posy;
}

void GraphicsTreeProduct::setPosX(int posX) {
    m_posx = posX;
    setPos(m_posx,m_posy);
}

void GraphicsTreeProduct::setPosY(int posY) {
    m_posy = posY;
    setPos(m_posx,m_posy);
}
