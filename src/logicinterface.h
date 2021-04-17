#ifndef LOGICINTERFACE_H
#define LOGICINTERFACE_H

#include <complex>
#include <map>

/*!
    This is a inteface draft for logic gui communications.

    The most basic functionnality of the logic is to compute the elctric field
    at a given position. All other functions are derived from this one.

    Communication with the logic follows a client server protocol where logic
    is the server. It answers clients requests. This approach might introduce
    some complexity in case the logic might generate time variation in the
    system but it looks like a minor drawback.

    The other results that the logic should provide are:

    - Impulse response
    - Frequency response
    - Interference pattern
    - Power Angular Spectrum
    - Power Doppler Spectrum
    - Spatial correlation
    - Time correlation
    - Power Delay Profile

    - Path-loss
    - Shadowing
    - Cell range
*/

std::complex<double> getElectricField();

double getReceivedPower();

std::map<double, double> getImpulseResponse();

std::map<double, double> getFrequencyResponse();

std::map<double, double> getPowerAngularSpectrum();

std::map<double, double> getPowerDopplerSpectrum();

std::map<double, double> getTimeCorrelation();

std::map<double, double> getSpaceCorrelation();

std::map<double, double> getPowerDelayProfile();

std::map<double, double> getReveivedPowerVsDistance();

std::map<double, double> getPathLoss();

std::map<double, double> getShadowing();

std::map<double, double> getCellRange();



#endif // LOGICINTERFACE_H
