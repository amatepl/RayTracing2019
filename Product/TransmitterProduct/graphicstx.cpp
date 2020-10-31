#include "graphicstx.h"

GraphicsTx::GraphicsTx(QMenu* productmenu, QGraphicsScene *scene)
{
    QPixmap icon(":/Images/Transmitter1.png");
    setPixmap(icon);
    setOffset(-icon.width()/2,-icon.height()/2);


    m_productmenu = productmenu;
    m_scene = scene;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    m_type = "transmitter";
    draw();

}

GraphicsTx::~GraphicsTx(){
    cout << "Graphics Transmitter Product Deleted." << endl;
    delete m_observer;
}

QPixmap GraphicsTx::getImage(){
    QPixmap icon(":/Images/Transmitter1.png");
    return icon;
}


bool GraphicsTx::graphicsSelected() {
    return isSelected();
}

void GraphicsTx::draw(){
    m_scene->addItem(this);
}

void GraphicsTx::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
        //m_graphicsfactory->clearSelection();
        setSelected(true);
        m_productmenu->exec(event->screenPos());
}

QVariant GraphicsTx::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged || change == QGraphicsItem::ItemRotationChange) {
        m_observer->update(this);
    }
    return value;
}

void GraphicsTx::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/){
//    m_observer->openDialog();
    m_dialog.release();
    m_dialog = m_dialogFctry->create();
}

void GraphicsTx::notifyToGraphic(QPointF *point, double orientation){
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setPos(*point);
    setRotation(orientation);
}

void GraphicsTx::setDialogFctry(DialogWinFctry<QDialog> *dialogFctry)
{
    m_dialogFctry = dialogFctry;
}
