/*!
    \class RxDataHandler
    \brief Receiver Data Handler

    This is a container for sending data from transmitter to receiver.
*/

#ifndef RXDATAHANDLER_H
#define RXDATAHANDLER_H

//--------------------------------------------------------------------------------------------
//
//          General Includes
//
//--------------------------------------------------------------------------------------------

#include <map>
#include <complex>

//--------------------------------------------------------------------------------------------
//
//          Global Variables
//
//--------------------------------------------------------------------------------------------

using namespace std;
class ProductObservable;

//--------------------------------------------------------------------------------------------
//
//          Class RxDataHandler
//
//--------------------------------------------------------------------------------------------

class RxDataHandler
{
public:
    RxDataHandler();
private:
    map<ProductObservable *, map<double /*tau*/, complex<double> /*impulseResp*/>>
        m_receiversImpulse;
    map<ProductObservable *, map<double, complex<double>>> m_dopplerSpectrum;

};

#endif // RXDATAHANDLER_H
