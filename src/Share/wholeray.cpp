#include "wholeray.h"

WholeRay::WholeRay()
{

}

WholeRay::~WholeRay()
{

}

length WholeRay::directDistance() const
{
    QLineF dirPath(this->front()->p2(), this->back()->p1());
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
    angle a = this->front()->angle();
    a = a > 180 ? a - 180: a + 180;
    return a;
}

angle WholeRay::angleTx() const
{
    return this->back()->angle();
}
