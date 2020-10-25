#ifndef TX_H
#define TX_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

#include <math.h>
#include <complex>
#include <iostream>
#include <QPointF>
#include <QPolygonF>
#include <vector>
#include <ratio>
#include <gsl/pointers>

/* Project Specific includes */

#include "txinterface.h"
#include "dialogtx.h"
#include "Product/mathematicalproduct.h"
#include "Abstract_Factory/abstractrayfactory.h"

#include "Observer/productobserver.h"
#include "Observer/productobservable.h"
#include "Observer/modelobserver.h"
#include "Observer/modelobservable.h"

#include "Product/RayProduct/ray.h"
#include "Product/TreeProduct/mathematicaltreeproduct.h"
#include <Product/abstractantena.h>
#include "Product/CarProduct/mathematicalcarproduct.h"

#include "Share/physics.h"
#include "Share/chdata.h"

//--------------------------------------------------------------------------------------------
//
//          Global Variables
//
//--------------------------------------------------------------------------------------------

#define NDEBUG

using namespace std;
using namespace gsl;
using u = double;
using amp_u = double;
//using WholeRay = vector<Ray *>;

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
//          Class Tx
//
//--------------------------------------------------------------------------------------------
/*!
 * \class Tx
 * \brief The Tx class
 *
 * Represent the transmitter mathematical object
 * Contains the parameters of the transmitter
 *
 * Create rays
 * Computes the power and the electric field
 * Computes channel characteristics
 */
class Tx : public QPointF,
                                       public ProductObserver, public ModelObserver,
                                       public AbstractAntena, public TxInterface,
                                       public MathematicalProduct
{


public:
    Tx(int posX, int posY);
    ~Tx() override;

    void appendTree(MathematicalTreeProduct *tree);

    void drawRays();
    QPolygonF buildCoverage() const;

    //virtual void setModel(Model model) override;
    complex<double> computeImpulseGroundReflection(QPointF *copy_receiver, double direction, QLineF local_region);
    complex <double> computeEfieldGround(const QPointF *receiver, const double direction,
                                         const bool properties);


    /*!
     * \fn Tx::computeR(WholeRay *wholeRay)
     * \brief Computes the R factor
     * \param wholeRay
     * \return R
     */
    double computeR(WholeRay *wholeRay) const;

    /*!
     * \fn Tx::estimateCh(QPointF *rx)
     * \brief Estimates channel characteristics for a given receiver
     * \param rx
     */
    void estimateCh(QPointF *rx);

    /*!
     * \brief Tx::vecSpeed
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

    double distance(const QPointF *receiver);
    complex<double> computeImpulseDiffraction(WholeRay *ray_line, QLineF local_region);
    complex<double> computeDiffractedEfield(QPointF *receiver, WholeRay *rayLine,bool properties);

    void chooseBeam(QPointF * receiver);
    void comput4FixedBeam(QPointF * receiver);
    void dontChoseBeam(QPointF * receiver);
    void freazeBeams();
    double computePrx(complex <double> totalEfield, complex<double> groundField, QPointF* receiver);
    double dBm(double power);
    double computeReflexionPer(double thetaI, double epsilonR) const;
    double computeReflexionPar(double thetaI, double epsilonR) const;

    vector<WholeRay *> getRays();
    void notifyObservables();
    void notifyObservers(QPointF *rx, const QLineF mvmnt);

    /*!
     * \brief angularSpread
     * \param rx
     *
     * Computes the angular spred for rx.
     * The result is stored in m_chsData[rx].angularSpread
     */
    void angularSpread(QPointF *rx);

    void clearAll();

    void addTxImg(ProductObserver *txImg);

    /*!
     * \fn void detectAndLink()
     * \brief detectAndLink
     *
     * Verify if there is a line of sight between the receiver and the transmitter.
     * If yes adds the corresponding ray to the list of rays.
     */
    void detectAndLink(const QPointF &p);

    /*!
     * \fn bool detect(QPointF *p)
     * \brief Veryfies if there is a line of sight between tx and the point.
     * \param p
     * \return
     *
     * Veryfies if there is a line of sight between tx and the point.
     */
    bool detect(const QPointF &p);

    /*!
     * \fn void link(QPointF *p)
     * \brief link
     * \param p
     *
     * Links tx to the point by adding the line of sight ray to the rays' list.
     */
    void link(const QPointF &p, WholeRay *wholeRay);

    complex<double> computeEField(QPointF *rx);

    /*
     * ProductObserver
     *
     *****************/

    //void update(const QPointF *productObservable, const float speed, const float direction) override{};
    Data *update(QPointF *receiver, QLineF const movement) override;
//    void updateCarPos(QPointF *productObservable) override;
    void drawRays(QPointF *productObservable, bool draw) override;
    void compute(QPointF *productObservable);
    double riceFactor(QPointF* receiver)
    {
        return 10*log10(m_los_factor[receiver]/m_nlos_factor[receiver]);
    }

    double computePathLossPower(QPointF* copy_receiver);
    complex<double> computeInterference(QPointF *,QLineF local_region);

    using MathematicalProduct::attachObservable;
    void  attachObservable(QPointF *productObservable) override;

    Data * getChData(QPointF *rx);

    /*!
     * \fn Tx::pathLossPoints()
     * \brief Find points for computation of the path loss
     * \return path_points
     *
     * Compute points linearly in the coverage zone of the transmitter.
     * These points will be requested by MathRxProd to calculate
     * the power. See Rx::notifyObserversPathLoss.
     * This function is an override of ProductObserver but shouldn't be.
     *
     */
    vector<QPointF> pathLossPoints() const;

    //ModelObserver
    void attachObservable(ModelObservable *modelObserver) override;



    /*
     * TxInterface
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

    /*!
     * \fn void clearPathLoss()
     * \brief clearPathLoss
     *
     * Clears all the Path Loss related data.
     */
    void clearPathLoss();

    /*!
     * \brief powerPathLoss
     * \return
     */
    vector<double> powerPathLoss() override {return Prx;};
    /*!
     * \brief distancePathLoss
     * \return
     */
    vector<double> distancePathLoss() override {return D;};
    /*!
     * \brief linearPathLoss
     * \return
     */
    vector<double> linearPathLoss() override {return path_loss;};

    vector<double> friisLoss() override {return friis_loss;};
    double pathLossExponent() override {return m/10;};
    double fadingVariability() override {return fading_variability;};
    double minPower() override {return min_prx;};

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override {
        TxInterface::m_orientation = orientation;
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
    void openDialog(QWidget *) override;
    void setScale(float scale) override;

    /*!
     * \fn void Tx::clearChData(QPointF *rx)
     * \brief Clears all estimated data for a channel
     * \param rx
     */
    void clearChData(QPointF *rx);

    void deleteRays(QPointF *rx);

//    // From ProductObserver
//    void notify(const QPointF &pos) override;
//    void attachObservable(QPointF *productObservable) override;

//    // From ModelObserver
//    void attachObservable(ModelObservable* modelObserver) override;


//    QPointF sceneRectIntersection(const QRectF &rect, const QLineF &line)const;
//    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const;

    /*
     * AbstractAntenna
     *
     *****************/
    void notifyParent(QPointF *productObservable,
                      double speed,
                      const QPointF &point,
                      WholeRay *wholeRay) override;

    void notifyCarDetected() override;

    QPointF getPosition()const override;
    QPolygonF getIlluminationZone(const QRectF &rect)const override;
    QPolygonF getIlluminationZone()const override;
    void setIlluminatedZone(const QPolygonF &zone) override;
    QPolygonF getIlluminatedZone()const override;

    // 1. Path Loss Computation:
    void linearRegressionPathLoss();
    void computePathLossFading();
    double standardDeviation();

     /*!
     * \fn notifyObserversPathLoss(ProductObserver* transmitter)
     * \brief Fill the map m_pathloss to compute the path loss.
     * \param transmitter
     *
     * This function calls two other functions that are only used
     * in MathTxProduct but are virtualized in ProductObserver (bad choice).
     * The first one is MathTxProduct::pointsPathLoss which gives
     * the points where the power should be calculated.
     * The second one is MathTxProduct::computePathLossPower which
     * calculates the power from the receiver copied to the point.
     * The m_pathloss map is then filled with the Euclidean distance
     * from the point and the power in dBm at this point.
     * An average is computed if the same distance is calculated.
     *
     */
   void notifyObserversPathLoss() override;
    double inputNoise();
    void computeMinPrx();

    // 2. Shadowing Computation:
    void clearShadowing();

     /*!
     * \brief notifyObservervesShadowing
     * \param tx
     * \return Coresponding angle with power receiver as a map
     *
     * The shadowing is computed at the same distance as transmitter
     * but around 360°. The shadowing represent the variability around
     * the transmitter.
     *
     */
    map<double, double> notifyObserversShadowing() override;

     /*!
     * \brief circlePoints
     * \param center
     * \param radius
     * \param rpd: Range per degree (number of samples per degree)
     * \return Vector of QPointF in the perimeter of a circle
     */
   vector<QPointF> circlePoints(QPointF center, double radius, int rpd);

    // 3. Cell Range
    void clearCellRange();
    vector<double> probabilityConnection() override;
    vector<double> cellRangeConnection() override;

    /*!
     * \fn averageOnMap(std::map<double,double> values,
                                                     std::map<double,int> counter);
     * \brief Average value inside a map by the number of keyword iteration
     * \param values
     * \param counter
     *
     * The keyword is the same. The value of the counter is the iteration
     * number of the same value. The value of values is the sum of all
     * value that the map found for the same key.
     *
     */
    map<double, double> averageOnMap(map<double, double> values, map<double, int> counter) const;
    void cellRange() override;

private:
    double m_power                 { 2 };
    Kind m_kind               { dipole };
    int m_radius                 { 500 };
    bool m_beamsFrozen = false;

    vector<ProductObserver *> m_txImgs;     // Would be nice if converted to unique_ptr

    map<QPointF *, bool> m_chosenBeams;

//    double m_powerAtReceiver;
    ModelObservable *m_model;
    vector<QPointF *> m_productObservable;
    //map<const QPointF*,vector<vector<Ray*>*>> m_receiversRays;

    map<const QPointF *,vector<WholeRay *>> m_receiversRays;
    map<QPointF *,complex<double>> m_receiversField;
    map<QPointF *,complex<double>> m_receiversGroundField;
    vector<MathematicalTreeProduct *> m_trees;

    // Rice facor
    map< QPointF *,double> m_los_factor;
    map<const QPointF *,double> m_nlos_factor;

    // Doppler spectrum
    map<WholeRay *,double /*speed*/> rays_speed;
    map<const QPointF*, QLineF /*movement*/> receivers_speed;
//    QLineF m_ray_speed;

    //QPolygonF m_zone;
    complex<double> m_EMfieldAtReceiver;
//    vector<vector<Ray *>*> m_wholeRays;
    vector<WholeRay *> m_wholeRays;

    complex<double> m_EMfield;

    // Data to share with receiver
    map<const QPointF *, Data> m_chsData;

    // 3. For Path Loss Computation
    std::map<double /*distance*/, double /*power*/> m_pathloss;
    vector<double> logD, fading;
    vector<double> Prx, path_loss, friis_loss, D;
    double m,b,r,fading_variability, min_prx; //Path loss slope and intercept and regression coefficient

    // 3. Cell Range
    vector<double> cell_range, probability;
    int m_target_snr        {8};
    int m_noise_figure      {10};
    int m_interferencemargin{6};

public slots:
    void carMoved(MathematicalCarProduct *car, int, int, double) override;


};

#endif // TX_H
