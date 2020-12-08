#ifndef CHDATA_H
#define CHDATA_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */
#include <map>
#include <complex>
#include <vector>

//--------------------------------------------------------------------------------------------
//
//          Struct Data
//
//--------------------------------------------------------------------------------------------

/*!
 * \brief The Data struct
 * \struct Data
 *
 * Data is a struture used to share the channel data, known by the transmitter,
 * with the receiver in order to display it.
 *
 */
struct Data {
    double                                                          fq{0};
    double                                                          bw{0};
    double                                                          prx{0};
    double                                                          dstnc{0};
//    double                                                          dlySprd{0};
//    double                                                          coherenceBw{0};
//    double                                                          coherenceTm{0};
    std::complex<double>                                            indVoltage{0};
    std::complex<double>                                            eField{0};
    std::map<double /*tau*/, std::complex<double> /*impulseResp*/>  impulseResp;
    std::map<double, std::complex<double>>                          fqResp;
    std::map<double, std::complex<double>>                          dopplerSpctr;
    double                                                          pathLossP{0};
    std::complex<double>                                            interference{0};
    double                                                          angularSpred{0};
    double                                                          dopplerSpread{0};
    std::vector<double>                                             u;
    std::vector<double>                                             w;
//    std::map<double /*u*/, std::complex<double> /* a(u) */>         angularDistr;
    std::vector<std::complex<double> /* a(u) */>                    angularDistr;
    std::vector<std::complex<double> /* a(w) */>                    dopplerDistr;
    std::map<double /*u*/, double /* S(u) */>                       prxAngularSpctrMap;
    std::vector<double /* S(u) */>                                  prxAngularSpctr;
    std::vector<double /* S(w) */>                                  prxDopplerSpctr;
    double                                                          riceFactor{0};
    std::vector<double>                                             spaceCrltn;
    std::map<double, double>                                        spaceCrltnMap;
    std::vector<double>                                             timeCrltn;
    std::map<double, double>                                        timeCrltnMap;
    std::vector<double>                                             deltaZ;

};
#endif // CHDATA_H
