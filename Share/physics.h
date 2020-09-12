#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>
#include <complex>
#include <vector>
#include <Share/wholeray.h>
#include <gsl/gsl>

constexpr double  eps_air        =   8.864e-12      ;  // A²S⁴kg⁻1m⁻3
constexpr double  z_0            =   120 * M_PI     ;
constexpr double  u_air          =   4 * M_PI * 1e-7;  // Tm/A
constexpr double  C              =   2.998e+8       ;  // m/s
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
double angularSpread(const vector<double> &prxAngularSpread, const vector<double> &u);


/*!
 * \fn void normalizePAS(vector<double> &pas)
 * \brief Normalizes the PAS.
 * \param pas
 *
 * For now its for tests
 */
template <class T>
void normalizePrxSpctr(T &pas)
{
    double nbrMPCs = pas.size();
    for (auto &p: pas) {
        p = p / nbrMPCs;
    }
}

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

}
#endif // PHYSICS_H
