#include "mathematicalrayproduct.h"

MathematicalRayProduct::MathematicalRayProduct(const QPointF &p1, const QPointF &p2, double Tetai, const double epsilonWall):
      Line(p1,p2), m_tetai(Tetai), m_epsilonWall{epsilonWall}
{
    m_type = "Ray";
    updateMeterLength();
}


MathematicalRayProduct::~MathematicalRayProduct()
{
    //cout<<"Math ray nearly deleted"<<endl;
    delete m_graphic;
    //cout<<"Mathematical Ray Product Deleted." << endl;
}

/*
 * The scale chosen for the meter-pixels conversion is 1px = 1dm
 */


void MathematicalRayProduct::updateMeterLength()
{
    meterLength = length()*0.1; // pxToMeter = 0.1
}


// --> Getters && Settets

int MathematicalRayProduct::getWallInd() const
{
    return wallInd;
}


double MathematicalRayProduct::getTetai() const
{
    return m_tetai;
}


double MathematicalRayProduct::getTheta() const
{
    return m_theta;
}


int MathematicalRayProduct::getIndWall() const
{
    return m_wallIBouncedOn;
}


//double MathematicalRayProduct::getMeterLength()const{return meterLength;}


void MathematicalRayProduct::setTetai(const double tetai)
{
    if (tetai > 180) {
        m_tetai = (tetai - 180)*M_PI/180;
    } else
        m_tetai = tetai*M_PI/180;
}


void MathematicalRayProduct::setDiffracted(const bool diffracted)
{
    m_diffracted = diffracted;
}


bool MathematicalRayProduct::getDiffracted() const
{
    return m_diffracted;
}


double MathematicalRayProduct::getEpsilon() const
{
    return m_epsilonWall;
}


void MathematicalRayProduct::draw()
{
    if(m_graphic != nullptr){
        m_graphic->draw();
    }
}


void MathematicalRayProduct::erase()
{
    if(m_graphic != nullptr){
        m_graphic->erase();
    }
}


MathematicalProduct *MathematicalRayProduct::toMathematicalComponent()
{
    return this;
}


void MathematicalRayProduct::update(QGraphicsItem */*graphic*/)
{

}


void MathematicalRayProduct::openDialog()
{

}
