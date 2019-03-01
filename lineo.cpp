#include "lineo.h"
#include"room.h"

/*
 * The lineo object will be the main analytical geometric tool, everything that is displayed in the graphical field is inherited from lineo
 *
 * itself inherits from QGraphicsLineItem
 */

lineo::lineo(int x01, int y01, int x02, int y02)
{
    x1 = x01;
    y1 = y01;
    x2 = x02;
    y2 = y02;

    def_Slope(x1,y1,x2,y2);
    def_YOrigin(x1,y1);
    setLength();


}

void lineo::def_Slope(qreal x01, qreal y01, qreal x02, qreal y02){
    if(x01 == x02){
        // If the line is vertically oriented, the slope is infinite
        a = INFINITY;
        angle = M_PI/2;
    }
    else{
        a =(y02 - y01)/(x02 - x01);
        angle = atan(a);
    }
}

void lineo::def_YOrigin(qreal x01, qreal y01){
    if(a != INFINITY){
        b = y01 - a*x01;
    }else{
        b = -1;
    }
}


void lineo::setLength(){
     d = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
}

//--> Getters && Setters

double lineo::getSlope(){return a;}
double lineo::getAngle(){return angle;}
double lineo::getYorigin(){return b;}
double lineo::getLength(){return d;}

int lineo::vectX(){return (x2-x1);}
int lineo::vectY(){return (y2-y1);}
int lineo::getX1(){return x1;}
int lineo::getY1(){return y1;}
int lineo::getX2(){return x2;}
int lineo::getY2(){return y2;}


void lineo::setX1(double x01){x1 = x01;
                             //this->setLine(x01,y1,x2,y2);
                              def_Slope(x01,y1,x2,y2);
                              def_YOrigin(x01,y1);}
void lineo::setY1(double y01){y1 = y01;
                             //this->setLine(x1,y01,x2,y2);
                              def_Slope(x1,y01,x2,y2);
                              def_YOrigin(x1,y01);}
void lineo::setX2(double x02){x2 = x02;
                             //this->setLine(x1,y1,x02,y2);
                              def_Slope(x1,y1,x02,y2);
                              def_YOrigin(x1,y1);}
void lineo::setY2(double y02){y2 = y02;
                             //this->setLine(x1,y1,x2,y02);
                              def_Slope(x1,y1,x2,y02);
                              def_YOrigin(x1,y1);}


void lineo::setSlope(double slope){a = slope;}
void lineo::setAngle(double angle){a = tan(angle);}

