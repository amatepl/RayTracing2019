#include "mathematicalcarproduct.h"

MathematicalCarProduct::MathematicalCarProduct(QRectF rect)
{
    setRect(rect.topLeft().x(),rect.topLeft().y(),rect.width(),rect.height());
    m_type = "Car";
}

MathematicalCarProduct::~MathematicalCarProduct(){

}

double MathematicalCarProduct::getSpeed(){
    return m_speed;
}

double MathematicalCarProduct::getOrientation(){
    return m_orientation;

}

void MathematicalCarProduct::setSpeed(double speed){
    m_speed = speed;
}

int MathematicalCarProduct::getPosX(){return x();}
int MathematicalCarProduct::getPosY(){return y();}

void MathematicalCarProduct::setOrientation(double orientation){m_orientation = orientation;}
void MathematicalCarProduct::setPosX(int posX){moveCenter(QPointF(posX,center().y()));}
void MathematicalCarProduct::setPosY(int posY){moveCenter(QPointF(center().x(),posY));}

void MathematicalCarProduct::update(QGraphicsItem *graphic){
    moveCenter(QPointF(graphic->scenePos().x(),graphic->scenePos().y()));
    //QRectF rect = graphic->sceneBoundingRect();
    //setRect(rect.topLeft().x(),rect.topLeft().y(),rect.width(),rect.height());
}

void MathematicalCarProduct::openDialog(){
    new DialogCarProduct(this);
}

void MathematicalCarProduct::newProperties(){
    m_graphic->notifyToGraphic(this);
}
