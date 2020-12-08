#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>
#include <complex>
#include <vector>
#include <Share/wholeray.h>
#include <gsl/pointers>
// #include "boost/compute/algorithm/max_element.hpp"

constexpr double  eps_air        =   8.864e-12      ;  // A²S⁴kg⁻1m⁻3
constexpr double  z_0            =   120 * M_PI     ;
constexpr double  u_air          =   4 * M_PI * 1e-7;  // Tm/A
constexpr double  c              =   2.998e+8       ;  // m/s
constexpr double  k_b            =   1.379e-23      ;  // Boltzmann's constant
constexpr double  t_0            =   290            ;  // K; reference temperature T_0
constexpr double  bw             =   100e+6         ;  // Hz
constexpr double  ant_hght       =   1.5            ;  // m
constexpr double  r_a            =   73.0           ;  // Ohms, its a typical resistance data for \lambda/2 emettors

namespace ph {

using u = double;
using amp_u = double;
using angle = double;
using width = double;
using height = double;

/*!
 * \enum TxType
 * \brief Transmitters types.
 */
enum class TxType {dipole, array, dipoleRefl, arrayRefl};

/*!
 * \struct TxParams
 * \brief Transmitter's parameters
 */
struct TxParams {
    double prx;
    double fq;
    double orien;
    char beam;
    double arrW;
    double arrH;
    TxType type;
};


/*!
 * \fn double uMPC(WholeRay *wholeRay)
 * \brief Return u parameter for a given MPC
 * \param wholeRay
 * \return
 *
 */
u uMPC(double wvNbr, angle theta);

/*!
 * \fn double omegaMPC(double v)
 * \brief return omega variable for Doppler Spectrum
 * \param v
 * \return
 */
double omegaMPC(double v, double wvNbr,  angle angleRx);

/*!
 * \fn double pasMPC (WholeRay *wholeRay);
 * \brief Computes Power Angular Spectrum for one MPC
 * \param complex<double> angDistr
 * \return Power Angular Sepctrum for one MPC
 */
double prxSpctrMPC(angle theta, double spectrum);

double prxSpctrMPC(std::complex<double> &angDistr, const double ampu, const u u);

/*!
 * \fn complex<double> angDistr()
 * \param h
 * \param theta
 * \param spectrum (Angular or Doppler)
 * \brief Returns tha angular distribution for one MPC
 * \return
 */
std::complex<double> angDistrMPC(const std::complex<double> &h, const double theta, const double spectrum);

/*!
 * \fn double angularSpread(const vector<double> &prxAngularSpread, const vector<double> &u)
 * \brief Returns the angular spread.
 * \param prxAngularSpread
 * \param u
 * \return
 */
double angularSpread(const vector<double> &prxAngularSpread, const vector<double> &u, const double ampu);

//BOOST_COMPUTE_FUNCTION(bool, compare_first, (const double &a, const double &b),
//{
//    return a < b;
//});

//BOOST_COMPUTE_FUNCTION(bool, compare_map, (const pair<double, double> &a, const pair<double, double> &b),
//{
//    return a.second < b.second;
//});

///*!
// * \fn void normalizePAS(vector<double> &pas)
// * \brief Normalizes the PAS.
// * \param pas
// *
// * For now its for tests
// */
//template <class T>
//void normalizePrxSpctr(T &pas)
//{
//    boost::compute::vector<double>::iterator max = max_element(pas.begin(), pas.end(), compare_first);
//    for (auto &p: pas) {
//        p = p / max;
//    }
//}
///*!
// * \fn void normalizePAS(vector<double> &pas)
// * \brief Normalizes the PAS.
// * \param pas
// *
// * For now its for tests
// */
//template <class T, typename C>
//void normalizeMap(map<T, C> &pas)
//{
//    boost::compute::vector<complex>::iterator max = max_element(pas.begin(), pas.end(), compare_first);
//    for (auto &p: pas) {
//        p = p / abs(max);
//    }
//}
/*!
 * \fn map<double, double> correlation(vector<double> &spctr)
 * \brief correlation
 * \param spctr
 * \return
 */
map<double, double> correlation(const vector<complex<double>> &spctr);

/*!
 * \brief dipoleFactor
 * \param phi
 * \return
 */
complex <double> dipoleFactor(double phi);

/*!
 * \brief reflectorFactor
 * \param theta
 * \param phi
 * \param fq
 * \param antOrien
 * \return
 */
complex <double> reflectorFactor(angle theta, angle phi, double fq, angle antOrien);
/*!
 * \brief reflectorFactor
 * \param theta
 * \param phi
 * \param fq
 * \param antOrien
 * \return
 */
complex <double> reflectorFactor(angle theta, angle phi, const TxParams &txParams);

/*!
 * \brief arrayFactor
 * \param theta
 * \param phi
 * \param fq
 * \param antOrien
 * \return
 */
complex <double> arrayFactor(angle theta, angle phi,double fq, angle antOrien,
                            char beam, unsigned arrW, unsigned arrH);

/*!
 * \brief arrayFactor
 * \param theta
 * \param phi
 * \param fq
 * \param antOrien
 * \return
 */
complex <double> arrayFactor(angle theta, angle phi, const TxParams &txParams);


/*!
 * \brief totaleArrayFactor
 * \param theta
 * \param phi
 * \param fq
 * \param antOrien
 * \return
 */
complex <double> totaleArrayFactor(double theta, double phi, double fq, angle antOrien,
                                  char beam, unsigned arrW, unsigned arrH, TxType type);

/*!
 * \brief totaleArrayFactor
 * \param theta
 * \param phi
 * \param fq
 * \param antOrien
 * \return
 */
complex <double> totaleArrayFactor(double theta, double phi, const TxParams &txParams);

/*!
 * \fn double electricalGain(double theta, double phi)
 * \brief Returns the elctrical gain.
 * \param arrayFactor
 * \return
 *
 * Computes the electrical gain for a antana with a given array factor.
 *
 */
double electricalGain(complex<double> arrayFctr);

/*!
 * \fn double powerGain(double theta, double phi)
 * \brief Return the power gain.
 * \param arrayFctr
 * \return
 */
double powerGain(complex<double> arrayFctr);

/*!
 * \fn computeReflexionPer(double thetaI, double epsilonR)
 * \brief Returns perpendicular reflection coefficient.
 * \param thetaI
 * \param epsilonR
 * \return
 *
 * Returns reflection coefficient for waves with perpendicular polarisation
 * to the normal of the reflective surface.
 *
 */
double computeReflexionPer(double thetaI, double epsilonR);

/*!
 * \brief computeR
 * \param wholeRay
 * \return
 */
double computeR(WholeRay *wholeRay);

/*!
 * \fn double currentTx(const double power, const tuple<width, height> antArry);
 * \brief Computes the current at the transmitter.
 * \param power
 * \param antArry
 * \return
 */
double currentTx(const double power, const tuple<width, height> antArry);

/*!
 * \brief computeEMfield
 * \param rayLine
 * \param antArry
 * \param power
 * \param wvNbr
 * \param array_fctr
 * \return
 */
std::complex <double> computeEMfield(const gsl::not_null<WholeRay*> rayLine,
                                    const std::tuple<width, height> antArry,
                                    double power,
                                    double wvNbr,
                                    double antOrien,
                                    char beam,
                                    TxType txType);

/*!
 * \brief computeEMfield overload
 * \param rayLine
 * \param antArry
 * \param power
 * \param wvNbr
 * \param array_fctr
 * \return
 */
std::complex <double> computeEMfield(const gsl::not_null<WholeRay*> rayLine, const TxParams &txParams);

/*!
 * \brief inducedVoltage
 * \param field due to reflections and diffraction
 * \param anglerx [rad]
 * \return Induced voltage at receiver due to EM field
 */
std::complex <double> inducedVoltage(const std::complex <double> field,
                                     const double anglerx,const double lambda);

template <typename T>
vector<complex<double>> dft(vector<T> &in)
{
    vector<complex<double>> out;

    complex<double> j (0., 1.);

    unsigned N = in.size();
    for (unsigned n = 0; n < N; n++) {
        out.push_back(0);
        for (unsigned m = 0; m < N; m++) {
            out.at(n) += in.at(m) * exp(-j * 2. * M_PI * (double) n * (double) m / (double) N);
        }
    }

    return out;
}

template <typename T>
vector<complex<double>> idft(vector<T> &in)
{
    vector<complex<double>> out;

    complex<double> j (0., 1.);

    unsigned N = in.size();
    for (unsigned n = 0; n < N; n++) {
        out.push_back(0);
        for (unsigned m = 0; m < N; m++) {
            out.at(n) += in.at(m) * exp(j * 2. * M_PI * (double) n * (double) m / (double) N) / (double) N;
        }
    }
    return out;
}

using cd = complex<double>;

void fft(vector<cd> &a, bool invert);

/*!
 * \fn upsample()(const vector<Tx> &x, const vector<Ty> &y, const double min,
 * const double max, const double step)
 *
 * \brief Upsample a vector.
 *
 * Upsample vector y function of x in a range [min, max] and with the given step.
 *
 */
template <typename Tx, typename Ty>
vector<Ty> upsample(const vector<Tx> &x, const vector<Ty> &y, const double min,
                   const double max, const double step=1)
{
    vector<Ty> res;
    double val = min;
    unsigned imax = x.size();
    for (unsigned idx = 0; idx < imax; idx++) {
        while (val < x.at(idx)) {
            res.push_back(Ty(0));
            val += step;
        }
        res.push_back(y.at(idx));
    }

    if (x.size() != 0) {
        double xend = x.back();
        while (xend <= max) {
            res.push_back(Ty(0));
            xend += step;
        }
    }
    return res;
}

}
#endif // PHYSICS_H
