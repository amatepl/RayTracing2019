#include "antena.h"

// Very basic antena type object

antena::antena(room *scene, QPointF p, int type):
QGraphicsEllipseItem()

{
    pos = p;
    this->setRect(pos.x(),pos.y(),1,1);
    antenaType = type;     // 0 for output (transmiter) 1 for input (receiver)
    myRoom = scene;
    QBrush noBrush(Qt::NoBrush);

    this->setBrush(noBrush);
    this->setPen(setColor());

    //myRoom->addItem(this);
}

antena::~antena(){

}


QPen antena::setColor(){

    /*
     * Changes the color according to the antena type, for more display visibility
     */

    QPen pen;
    if(antenaType == 0){
         QPen outlinePen(Qt::red);
          outlinePen.setWidth(2);
         pen = outlinePen;
    }
    else{
        QPen outlinePen(Qt::blue);
         outlinePen.setWidth(2);
        pen = outlinePen;
    }
    return pen;
}

// --> Getters && Setters

int antena::getPosX(){return pos.x();}
//int antena::getPosX(){return this->x();}
int antena::getPosY(){return pos.y();}

void antena::setPosi(QPointF posi){this->pos = posi;
            this->setRect(posi.x(),posi.y(),1,1);
            }
