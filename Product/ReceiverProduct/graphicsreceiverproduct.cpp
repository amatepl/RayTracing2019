#include "graphicsreceiverproduct.h"

GraphicsReceiverProduct::GraphicsReceiverProduct(bool enable, QMenu *menuproduct, QGraphicsScene *scene)
{
    m_productmenu = menuproduct;
    m_sizex = 10;
    m_sizey = 10;
    enableReceiver(enable);
    m_scene = scene;
    draw();
    m_type = "receiver";
}

GraphicsReceiverProduct::~GraphicsReceiverProduct(){
    cout << "Graphics Receiver Product Deleted." << endl;
    delete m_observer;
}

void GraphicsReceiverProduct::enableReceiver(bool enable){
    if (enable) {
        QPixmap icon(":/Images/Receiver1.png");
        setPixmap(icon);
        setOffset(-icon.width()/2,-icon.height()/2);
        this->setFlag(QGraphicsItem::ItemIsMovable);
        this->setFlag(QGraphicsItem::ItemIsSelectable);
        this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }
    else {
        QPixmap pixmap(m_sizex,m_sizey);
        pixmap.fill(scaleColor(10,24,17));
        QPainter painter(&pixmap);
        painter.setPen(QPen(Qt::black, 0));
        setPixmap(pixmap);
        setOffset(-m_sizex/2,-m_sizey/2);
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

QVariant GraphicsReceiverProduct::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        //m_mathematicalProduct->setPosX(pos().x());
        //m_mathematicalProduct->setPosY(pos().y());
        m_observer->update(this);
    }
    return value;
}

void GraphicsReceiverProduct::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    m_observer->openDialog();
}

bool GraphicsReceiverProduct::graphicsSelected() {
    return isSelected();
}

void GraphicsReceiverProduct::draw(){
    m_scene->addItem(this);
}


void GraphicsReceiverProduct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    //m_graphicsfactory->clearSelection();
    setSelected(true);
    m_productmenu->exec(event->screenPos());
}

void GraphicsReceiverProduct::notifyToGraphic(QPointF *point, float orientation){
    setPos(*point);
    setRotation(360-orientation);
}

void GraphicsReceiverProduct::notifyToGraphic(QPointF *point, double power){

//    cout<<"Goiong strong in GraphicsRceiverProduct"<<endl;
    setPos(*point);
    QColor color;
    if((-20 - power)*3>=0){color.setHsv((-20 - power)*3,255,255 - (-20 - power),255);}
    else if(power == 0){
        color.setHsv(240,150,80,255);
    }
    else{color.setHsv(0,255,255,255);}

    QPixmap pixmap(m_sizex,m_sizey);
    pixmap.fill(color);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 0));
    setPixmap(pixmap);
    setOffset(-m_sizex/2,-m_sizey/2);

    //draw();
//    brush->setColor(color);
}

void GraphicsReceiverProduct::sendInformation(){
    m_observer->updateInformation();
}

void GraphicsReceiverProduct::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (event->button() != Qt::LeftButton){
        return;
    }
    else{
        sendInformation();
    }
    QGraphicsItem::mousePressEvent(event);
}

void GraphicsReceiverProduct::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    sendInformation();
    QGraphicsItem::mouseMoveEvent(event);
}
