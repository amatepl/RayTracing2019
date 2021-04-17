#include "ray.h"

Ray::Ray(const QPointF &p1, const QPointF &p2, double Tetai, const double epsilonWall):
      Line(p1,p2), m_tetai(Tetai), m_epsilonWall{epsilonWall}
{
    m_type = "Ray";
    updateMeterLength();
}


Ray::~Ray()
{
    //cout<<"Math ray nearly deleted"<<endl;
    delete m_graphic;
    //cout<<"Mathematical Ray Product Deleted." << endl;
}

/*
 * The scale chosen for the meter-pixels conversion is 1px = 1dm
 */


void Ray::updateMeterLength()
{
    meterLength = length()*0.1; // pxToMeter = 0.1
}


// --> Getters && Settets

int Ray::getWallInd() const
{
    return wallInd;
}


double Ray::getTetai() const
{
    return m_tetai;
}


double Ray::getTheta() const
{
    return m_theta;
}


int Ray::getIndWall() const
{
    return m_wallIBouncedOn;
}


//double Ray::getMeterLength()const{return meterLength;}


void Ray::setTetai(const double tetai)
{
    if (tetai > 180) {
        m_tetai = (tetai - 180)*M_PI/180;
    } else
        m_tetai = tetai*M_PI/180;
}


void Ray::setDiffracted(const bool diffracted)
{
    m_diffracted = diffracted;
}


bool Ray::getDiffracted() const
{
    return m_diffracted;
}


double Ray::getEpsilon() const
{
    return m_epsilonWall;
}


void Ray::draw()
{
    if(m_graphic != nullptr){
        m_graphic->draw();
    }
}


void Ray::erase()
{
    if(m_graphic != nullptr){
        m_graphic->erase();
    }
}


MathematicalProduct *Ray::toMathematicalComponent()
{
    return this;
}


void Ray::update(QGraphicsItem */*graphic*/)
{

}


void Ray::openDialog(QWidget *)
{

}
