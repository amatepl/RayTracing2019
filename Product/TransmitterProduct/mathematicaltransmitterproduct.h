#ifndef MATHEMATICALTRANSMITTERPRODUCT_H
#define MATHEMATICALTRANSMITTERPRODUCT_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

#include "math.h"
#include "complex.h"
#include <iostream>
#include <QPointF>
#include <QPolygonF>
#include <vector>
#include <ratio>
#include <gsl/pointers>

/* Project Specific includes */

#include "transmitterproduct.h"
#include "dialogtransmitterproduct.h"
#include "Product/mathematicalproduct.h"
#include "Abstract_Factory/abstractrayfactory.h"

#include "Observer/productobserver.h"
#include "Observer/productobservable.h"
#include "Observer/modelobserver.h"
#include "Observer/modelobservable.h"

#include <Product/RayProduct/mathematicalrayproduct.h>
#include "Product/TreeProduct/mathematicaltreeproduct.h"
#include <Product/abstractantena.h>
#include "Product/CarProduct/mathematicalcarproduct.h"


//--------------------------------------------------------------------------------------------
//
//          Global Variables
//
//--------------------------------------------------------------------------------------------

#define NDEBUG

using namespace std;
using namespace gsl;
//using WholeRay = vector<MathematicalRayProduct *>;

//template <class Period = std::ratio<1>> struct Length {
//    unsigned long long value;
//};

//auto operator ""_m(unsigned long long n)
//{
//    return Length<>{n};
//}

//Length metre = 13_m;

//--------------------------------------------------------------------------------------------
//
//          Class MathematicalTransmitterProduct
//
//--------------------------------------------------------------------------------------------
/*!
 * \class MathematicalTransmitterProduct
 * \brief The MathematicalTransmitterProduct class
 *
 * Represent the transmitter mathematical object
 * Contains the parameters of the transmitter
 *
 * Create rays
 * Computes the power and the electric field
 * Computes channel characteristics
 */
class MathematicalTransmitterProduct : public QPointF,
                                       public ProductObserver, public ModelObserver,
                                       public AbstractAntena, public TransmitterProduct,
                                       public MathematicalProduct
{


public:
    MathematicalTransmitterProduct(int posX, int posY);
    ~MathematicalTransmitterProduct() override;

    void appendTree(MathematicalTreeProduct *tree);

    void drawRays();
    QPolygonF buildCoverage() const;

    //virtual void setModel(Model model) override;
    complex<double> computeImpulseGroundReflection(ProductObservable *copy_receiver, double direction, QLineF local_region);
    complex <double> computeEfieldGround(const ProductObservable *receiver, const double direction,
                                         const bool properties);
    /*!
     * \fn double uMPC(WholeRay *wholeRay)
     * \brief Return u parameter for a given MPC
     * \param wholeRay
     * \return
     *
     */
    double uMPC(angle angleRx);

    /*!
     * \fn double omegaMPC(double v)
     * \brief return omega variable for Doppler Spectrum
     * \param v
     * \return
     */
    double omegaMPC(double v, double angleRx);

    /*!
     * \fn double pasMPC (WholeRay *wholeRay);
     * \brief Computes Power Angular Spectrum for one MPC
     * \param complex<double> angDistr
     * \return Power Angular Sepctrum for one MPC
     */
    double prxSpctrMPC (complex<double> &angDistr, double theta, double spectrum);

    /*!
     * \fn complex<double> angDistr()
     * \param h
     * \param theta
     * \param spectrum (Angular or Doppler)
     * \brief Returns tha angular distribution for one MPC
     * \return
     */
    complex<double> angDistrMPC(complex<double> &h, double theta, double spectrum);

    /*!
     * \fn void normalizePAS(vector<double> &pas)
     * \brief Normalizes the PAS.
     * \param pas
     *
     * For now its for tests
     */
    void normalizePAS(vector<double> &pas);

    /*!
     * \fn  complex<double> computeEMfield(WholeRay *rayLine, ProductObservable* receiver,bool properties);
     * \brief computeEMfield - computes the electric field
     * \param rayLine
     * \param receiver
     * \param properties
     * \return EMfield
     *
     * Computes the electric field
     *
     */
    complex<double> computeEMfield(const not_null<WholeRay *> rayLine, const ProductObservable *, const bool);

    /*!
     * \fn MathematicalTransmitterProduct::computeR(WholeRay *wholeRay)
     * \brief Computes the R factor
     * \param wholeRay
     * \return R
     */
    double computeR(WholeRay *wholeRay) const;

    /*!
     * \fn MathematicalTransmitterProduct::estimateCh(ProductObservable *rx)
     * \brief Estimates channel characteristics for a given receiver
     * \param rx
     */
    void estimateCh(ProductObservable *rx);

    /*!
     * \brief MathematicalTransmitterProduct::vecSpeed
     * \param length
     * \param angle
     * \return vector speed under QLineF shape
     */
    QLineF vecSpeed(double length, double angle);

    /*!
     * \brief resultant
     * \param line1
     * \param line2
     * \return Compute resultant under QLineF shape
     *
     * The p1 of the return is (0.0)
     */
    QLineF resultant(QLineF line1, QLineF line2);

    complex<double>computeImpulseReflection(WholeRay *ray_line, QLineF local_region);

    double distance(const ProductObservable *receiver);
    complex<double> computeImpulseDiffraction(WholeRay *ray_line, QLineF local_region);
    complex<double> computeDiffractedEfield(ProductObservable *receiver, WholeRay *rayLine,bool properties);

    void chooseBeam(ProductObservable * receiver);
    void comput4FixedBeam(ProductObservable * receiver);
    void dontChoseBeam(ProductObservable * receiver);
    void freazeBeams();
    double computePrx(complex <double> totalEfield, complex<double> groundField, ProductObservable* receiver);
    double dBm(double power);
    double computeReflexionPer(double thetaI, double epsilonR) const;
    double computeReflexionPar(double thetaI, double epsilonR) const;

    vector<WholeRay *> getRays();
    void notifyObservables();

    /*!
     * \brief angularSpread
     * \param rx
     *
     * Computes the angular spred for rx.
     * The result is stored in m_chsData[rx].angularSpread
     */
    void angularSpread(ProductObservable *rx);

    void clearAll();

    /*
     * ProductObserver
     *
     *****************/

    //void update(const QPointF *productObservable, const float speed, const float direction) override{};
    void update(ProductObservable *receiver, QLineF const movement) override;
//    void updateCarPos(ProductObservable *productObservable) override;
    void drawRays(ProductObservable *productObservable, bool draw) override;
    void compute(ProductObservable *productObservable) override;
    double riceFactor(ProductObservable* receiver) override
    {
        return 10*log10(m_los_factor[receiver]/m_nlos_factor[receiver]);
    }

    double computePathLossPower(ProductObservable* copy_receiver) override;
    complex<double> computeInterference(ProductObservable *,QLineF local_region) override;

    using MathematicalProduct::attachObservable;
    void  attachObservable(ProductObservable *productObservable) override;

    Data * getChData(ProductObservable *rx) override;

    /*!
     * \fn MathematicalTransmitterProduct::pathLossPoints()
     * \brief Find points for computation of the path loss
     * \return path_points
     *
     * Compute points linearly in the coverage zone of the transmitter.
     * These points will be requested by MathRxProd to calculate
     * the power. See MathematicalReceiverProduct::notifyObserversPathLoss.
     * This function is an override of ProductObserver but shouldn't be.
     *
     */
    vector<QPointF> pathLossPoints() const override;

    //ModelObserver
    void attachObservable(ModelObservable *modelObserver) override;



    /*
     * TransmitterProduct
     *
     *****************/

    int getPosX() override {
        return x();
    }
    int getPosY() override {
        return y();
    }
    double getOrientation() override {
        return m_orientation;
    }
    char principalOrientation() override {
        return m_pr_orientation;
    }
    Kind getKind() override {
        return m_kind;
    }
    double getPower() override {
        return m_power;
    }
    int getRow() override {
        return m_row;
    }
    int getColumn() override {
        return m_column;
    }
    unsigned long getFrequency() override {
        return m_frequency;
    }
    unsigned long getBandwidth() override {
        return m_bandwidth;
    }
    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override {
        TransmitterProduct::m_orientation = orientation;
    }
    void setPrincipalOrientation(char orientation) override {
        m_pr_orientation = orientation;
    }
    void setPower(double power) override {
        m_power = power;
    }
    void setFrequency(unsigned long frequency) override {
        m_frequency = frequency;
    }
    void setBandwidth(unsigned long bandwidth) override {
        m_bandwidth = bandwidth;
    }
    void setRow(int row) override {
        m_row = row;
    }
    void setColumn(int column) override {
        m_column = column;
    }
    void setKind(Kind kind) override {
        m_kind = kind;
    }
    void newProperties(QPointF new_position, double orientation) override;

    // From MathematicalProduct
    void update(QGraphicsItem *graphic) override;
    void openDialog() override;
    void setScale(float scale) override;

    /*!
     * \fn void MathematicalTransmitterProduct::clearChData(ProductObservable *rx)
     * \brief Clears all estimated data for a channel
     * \param rx
     */
    void clearChData(ProductObservable *rx);

//    // From ProductObserver
//    void notify(const QPointF &pos) override;
//    void attachObservable(ProductObservable *productObservable) override;

//    // From ModelObserver
//    void attachObservable(ModelObservable* modelObserver) override;


//    QPointF sceneRectIntersection(const QRectF &rect, const QLineF &line)const;
//    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const;

    /*
     * AbstractAntenna
     *
     *****************/
    void notifyParent(ProductObservable *productObservable,
                      double speed,
                      const QPointF &point,
                      WholeRay *wholeRay) override;

    void notifyCarDetected() override;

    QPointF getPosition()const override;
    QPolygonF getIlluminationZone(const QRectF &rect)const override;
    QPolygonF getIlluminationZone()const override;
    void setIlluminatedZone(const QPolygonF &zone) override;
    QPolygonF getIlluminatedZone()const override;



private:
    double m_power                 { 2 };
    Kind m_kind               { dipole };
    int m_radius                 { 500 };
    bool m_beamsFrozen = false;

    map<ProductObservable *, bool> m_chosenBeams;

//    double m_powerAtReceiver;
    ModelObservable *m_model;
    vector<ProductObservable *> m_productObservable;
    //map<const QPointF*,vector<vector<MathematicalRayProduct*>*>> m_receiversRays;

    map<ProductObservable *,vector<WholeRay *>> m_receiversRays;
    map<ProductObservable *,complex<double>> m_receiversField;
    map<ProductObservable *,complex<double>> m_receiversGroundField;
    vector<MathematicalTreeProduct *> m_trees;

    // Rice facor
    map< ProductObservable *,double> m_los_factor;
    map<const ProductObservable *,double> m_nlos_factor;

    // Doppler spectrum
    map<WholeRay *,double /*speed*/> rays_speed;
    map<ProductObservable*, QLineF /*movement*/> receivers_speed;
//    QLineF m_ray_speed;

    //QPolygonF m_zone;
    complex<double> m_EMfieldAtReceiver;
//    vector<vector<MathematicalRayProduct *>*> m_wholeRays;
    vector<WholeRay *> m_wholeRays;

    complex<double> m_EMfield;

    // Data to share with receiver
    map<const ProductObservable *, Data> m_chsData;

public slots:
    void carMoved(MathematicalCarProduct *car, int, int, double) override;


};

#endif // MATHEMATICALTRANSMITTERPRODUCT_H
