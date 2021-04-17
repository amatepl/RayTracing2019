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


enum class TxType {dipole, array, dipoleRefl, arrayRefl};


struct TxParams {
    double prx;
    double fq;
    double orien;
    char beam;
    double arrW;
    double arrH;
    TxType type;
};


u uMPC(double wvNbr, angle theta);


double omegaMPC(double v, double wvNbr,  angle angleRx);


double prxSpctrMPC(angle theta, double spectrum);


double prxSpctrMPC(std::complex<double> &angDistr, const double ampu, const u u);


std::complex<double> angDistrMPC(const std::complex<double> &h, const double theta, const double spectrum);


double spread(const vector<double> &psd, const vector<double> &u);


double spread(const map<double, double> &psd);

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

map<double, complex<double>> correlation(const map<double, double> &spctr, const vector<double> &domain);


complex <double> dipoleFactor(double phi);


complex <double> reflectorFactor(angle theta, angle phi, double fq, angle antOrien);


complex <double> reflectorFactor(angle theta, angle phi, const TxParams &txParams);


complex <double> arrayFactor(angle theta, angle phi,double fq, angle antOrien,
                            char beam, unsigned arrW, unsigned arrH);


complex <double> arrayFactor(angle theta, angle phi, const TxParams &txParams);


complex <double> totaleArrayFactor(double theta, double phi, double fq, angle antOrien,
                                  char beam, unsigned arrW, unsigned arrH, TxType type);


complex <double> totaleArrayFactor(double theta, double phi, const TxParams &txParams);


double electricalGain(complex<double> arrayFctr);


double powerGain(complex<double> arrayFctr);


double computeReflexionPer(double thetaI, double epsilonR);


double computeR(WholeRay *wholeRay);


double currentTx(const double power, const tuple<width, height> antArry);


std::complex <double> computeEMfield(const gsl::not_null<WholeRay*> rayLine,
                                    const std::tuple<width, height> antArry,
                                    double power,
                                    double wvNbr,
                                    double antOrien,
                                    char beam,
                                    TxType txType);


std::complex <double> computeEMfield(const gsl::not_null<WholeRay*> rayLine, const TxParams &txParams);


std::complex <double> inducedVoltage(const std::complex <double> field,
                                     const double anglerx,const double lambda);


double firstMinIdx(const map<double, double> &fct, const double th=0.2, const unsigned range=1);

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
vector<complex<double>> dft2(vector<T> &in,double bandwidth,double step)
{
    vector<complex<double>> out;

    complex<double> j (0., 1.);

    unsigned N = in.size();
    double margin = bandwidth*0.05;
    double kmax = round((bandwidth+margin)*(N*step*1e-9));
    for (unsigned n = 0; n < kmax; n++) {
        out.push_back(0);
        for (unsigned m = 0; m < N; m++) {
            out.at(n) += in.at(m) * exp(-j * 2. * M_PI * (double) n * (double) m / (double) N);
        }
    }
    for (unsigned n = N-kmax; n < N; n++){
        out.push_back(0);
        for (unsigned m = 0; m < N; m++) {
            out.at(kmax+n-(N-kmax)) += in.at(m) * exp(-j * 2. * M_PI * (double) n * (double) m / (double) N);
        }
    }

    return out;
}

template <typename T>
vector<complex<double>> idft(vector<T> &in, unsigned nidft=-1)
{
    vector<complex<double>> out;

    complex<double> j (0., 1.);

    unsigned N = in.size();

    if (nidft<0) {
        nidft = in.size();
    }

    for (unsigned n = 0; n < nidft; n++) {
        out.push_back(0);
        for (unsigned m = 0; m < N; m++) {
            out.at(n) += in.at(m) * exp(j * 2. * M_PI * (double) n * (double) m / (double) N) / (double) N;
        }
    }
    return out;
}

using cd = complex<double>;

void fft(vector<cd> &a, bool invert);


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
        val+=step;
    }

    if (x.size() != 0) {
        double xend = x.back();
        while (xend <= max) {
            res.push_back(Ty(0));
            xend += step;
        }
    }
    for (unsigned i =0; i< 1000; i++){
        res.push_back(Ty(0));
    }
    return res;
}

}
#endif // PHYSICS_H
