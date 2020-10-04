#include "Product/abstractantena.h"

void AbstractAntena::notifyCarDetected()
{

}

QPolygonF AbstractAntena::getIlluminatedZone() const
{
    return m_zone;
};


void AbstractAntena::setIlluminatedZone(const QPolygonF &zone)
{
    m_zone = zone;
};


void AbstractAntena::setRayFactory(AbstractRayFactory *rayFactory)
{
    m_rayFactory = rayFactory;
};


Building *AbstractAntena::getBuilding() const
{
    return m_building;

};


void AbstractAntena::setBuilding(Building *building)
{
    m_building = building;
}


void AbstractAntena::setWallType(int type)
{
    m_wallType = type;
}


QLineF AbstractAntena::movement() const
{
    return m_movement;
}


void AbstractAntena::setMovement(QLineF const movement)
{
    m_movement = movement;
}


bool AbstractAntena::carInIlluminatedCars(MathematicalCarProduct *car, int *idx)
{
    for (unsigned i = 0; i < m_illuminatedCars.size(); i++) {
        if (m_illuminatedCars.at(i) == car) {
            *idx = i;
            return true;
        }
    }
    return false;
}

bool AbstractAntena::inIlluminatedCars(MathematicalCarProduct *car, int *idx)
{
    for (unsigned i = 0; i < m_illuminatedCars.size(); i++) {
        if (m_illuminatedCars.at(i) == car) {
            *idx = i;
            return true;
        }
    }
    return false;
}

//void AbstractAntena::carMoved(QPolygonF *car,int x, int y, double orientation)
//{
//    if (m_zone.intersects(*car)) {

//        cout << "Abstract A emitting signal" << endl;
////        emit detectsCar(this);
//    }
//}
