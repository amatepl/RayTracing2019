#include "mathematicaltreeproduct.h"

MathematicalTreeProduct::MathematicalTreeProduct(QPolygonF poly, QPointF center) : QPolygonF(poly),
    m_center(center),a(10)
{
    QPolygonF crown;

    this->clear();

    this->shrink_to_fit();

    for(int i=0;i<16;i++){
        crown<<QPointF(getPosX()+a*cos(M_PI*i/8),getPosY()+a*sin(M_PI*i/8));
    }

    this->swap(crown);

    m_type = "Tree";
    TreeParams branch1;
    branch1.radius = 11.4;
    branch1.length = 131;
    branch1.density = 0.013;
    m_params.push_back(branch1);

    TreeParams branch2;
    branch2.radius = 6.0;
    branch2.length = 99;
    branch2.density = 0.073;
    m_params.push_back(branch2);

    TreeParams branch3;
    branch3.radius = 2.8;
    branch3.length = 82;
    branch3.density = 0.41;
    m_params.push_back(branch3);

    TreeParams branch4;
    branch4.radius = 0.7;
    branch4.length = 54;
    branch4.density = 5.1;
    m_params.push_back(branch4);

    TreeParams branch5;
    branch5.radius = 0.2;
    branch5.length = 12;
    branch5.density = 56;
    m_params.push_back(branch5);

    TreeParams leaf;
    leaf.radius = 3.7;
    leaf.length = 0.02;
    leaf.density = 420;
    m_params.push_back(leaf);
}


float MathematicalTreeProduct::getRadius() const{
    return a;
}


void MathematicalTreeProduct::setRadius(float radius){a = radius;}

MathematicalTreeProduct::~MathematicalTreeProduct(){
    cout << "Matheatical Tree Product Deleted." << endl;
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

    //QRectF rect = graphic->sceneBoundingRect();
    //QPolygonF polyRect = QPolygonF(rect);
    //swap(polyRect);
    //m_center = graphic->pos();
    //translate(graphic->pos() - m_center);
}


void MathematicalTreeProduct::openDialog(){
    new DialogTreeProduct(this);
}


void MathematicalTreeProduct::newProperties(){
    m_graphic->notifyToGraphic(this, getPosX(), getPosY());
}


void MathematicalTreeProduct::attachObservable(GraphicsProduct *graphic){
    m_graphic = graphic;
    m_graphic->notifyToGraphic(this,getPosX(),getPosY());

}
