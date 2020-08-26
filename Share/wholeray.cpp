#include "wholeray.h"

WholeRay::WholeRay()
{

}

WholeRay::~WholeRay()
{

}

length WholeRay::directDistance() const
{
    QLineF dirPath(this->front()->p1(), this->back()->p2());
    return dirPath.length();
}

length WholeRay::totalLength() const
{
    length lenRay = 0;
    for (const auto &ray: *this) {
        lenRay += ray->getMeterLength();
    }
    return lenRay;
}

angle WholeRay::angleRx() const
{
    return this->front()->angle();
}

angle WholeRay::angleTx() const
{
    return this->back()->angle();
}
