#include "mathematicaltreeproduct.h"

MathematicalTreeProduct::MathematicalTreeProduct(QPolygonF poly, QPointF center) : QPolygonF(poly),
    m_center(center)
{
    m_type = "Tree";
}

MathematicalTreeProduct::~MathematicalTreeProduct(){

}

int MathematicalTreeProduct::getPosX(){return m_center.x();}
int MathematicalTreeProduct::getPosY(){return m_center.y();}

void MathematicalTreeProduct::setPosX(int posX) {
    QPointF offset = QPointF(posX,getPosY()) - m_center;
    m_center.setX(posX);
    translate(offset);
}

void MathematicalTreeProduct::setPosY(int posY){
    QPointF offset = QPointF(getPosX(),posY) - m_center;
    m_center.setY(posY);
    translate(offset);
}

void MathematicalTreeProduct::update(QGraphicsItem *graphic){
    QRectF rect = graphic->sceneBoundingRect();
    QPolygonF polyRect = QPolygonF(rect);
    swap(polyRect);
    m_center = graphic->pos();
}

void MathematicalTreeProduct::openDialog(){
    new DialogTreeProduct(this);
}

void MathematicalTreeProduct::newProperties(){
    m_graphic->notifyToGraphic(this, getPosX(), getPosY());
}

