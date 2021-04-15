#ifndef WHOLERAY_H
#define WHOLERAY_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

#include <vector>

/* Project Specigic */

#include "Product/RayProduct/ray.h"

//--------------------------------------------------------------------------------------------
//
//          Defines
//
//--------------------------------------------------------------------------------------------

using namespace std;

using length = double;
using angle = double;

//--------------------------------------------------------------------------------------------
//
//          Class WholeRay
//
//--------------------------------------------------------------------------------------------

/*!
 * \class WholeRay
 * \brief The WholeRay class
 *
 * Container for rays. It represent the entire path of a wave from transmitter to receiever.
 *
 * vector argument should be a unique_ptr
 */
class WholeRay: public vector<unique_ptr<Ray>>
{
public:
    WholeRay();
    ~WholeRay();

    /*!
     * \fn WholeRay::directDistance()
     * \brief Returns the distance as the crow flies between the receiver and the transmitter.
     * \return length
     */
    length directDistance() const;

    /*!
     * \fn WholeRay::totalLength()
     * \brief Returns the total length of the ray.
     * \return length
     */
    length totalLength() const;

    /*!
     * \fn WholeRay::angleRx()
     * \brief Returns the incidance angle at the receiver.
     * \return angle
     */
    angle angleRx() const;

    /*!
     * \fn WholeRay::angleTx()
     * \brief Returns the departure angle from the transmitter.
     * \return angle
     */
    angle angleTx() const;


};

#endif // WHOLERAY_H
