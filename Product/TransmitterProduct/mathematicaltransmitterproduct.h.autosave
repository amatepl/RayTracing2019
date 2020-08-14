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

using namespace std;

//--------------------------------------------------------------------------------------------
//
//          Class MathematicalTransmitterProduct
//
//--------------------------------------------------------------------------------------------

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
    QPolygonF buildCoverage();

    //virtual void setModel(Model model) override;
    complex<double> computeImpulseGroundReflection(ProductObservable *copy_receiver, double direction, QLineF local_region);
    complex <double> computeEfieldGround(ProductObservable *receiver, double direction,
                                         bool properties);

    complex<double> computeEMfield(vector<MathematicalRayProduct*> *rayLine,
                                   ProductObservable* receiver,bool properties);

    complex<double>computeImpulseReflection(vector<MathematicalRayProduct *> *ray_line, QLineF local_region);

    double distance(ProductObservable *receiver);
    complex<double> computeImpulseDiffraction(vector<MathematicalRayProduct *> *ray_line, QLineF local_region);
    complex<double> computeDiffractedEfield(ProductObservable *receiver, vector<MathematicalRayProduct *> *rayLine,bool properties);
    complex<double> computeDiffractedTreeEfield(vector<QLineF>rayLine);
    vector<vector<QLineF>> buildTreeRays(QPointF *Rx,MathematicalTreeProduct *tree);
    void computeRayThroughTree(QPointF *Rx,MathematicalTreeProduct *tree);

    void chooseBeam(ProductObservable * receiver);
    void comput4FixedBeam(ProductObservable * receiver);
    void dontChoseBeam(ProductObservable * receiver);
    void freazeBeams();
    double computePrx(complex <double> totalEfield);
    double dBm(double power);
    double computeReflexionPer(double thetaI, double epsilonR);
    double computeReflexionPar(double thetaI, double epsilonR);

    double computeElevationScaterringAngle(float heightRx, float heightTx,
                                           float heightConopy, float distanceRxTree);

    map<string,double> computeIncidenceDepartureAngles(float angleIncidenceConopy,
                                                        float angleAzimuth,
                                                        float angleElevation);


    vector<vector<MathematicalRayProduct *> *> getRays();
    void notifyObservables();
    QPointF sceneRectIntersection(const QRectF &rect, const QLineF &line) const;

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

    std::vector<QPointF> pointsForPathLoss(ProductObservable *true_receiver) override;
    double computePathLossPower(ProductObservable* copy_receiver) override;
    std::complex<double> computeInterference(ProductObservable *,QLineF local_region) override;

    using MathematicalProduct::attachObservable;
    void  attachObservable(ProductObservable *productObservable) override;

    Data * getChData(ProductObservable *rx) override;

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
                      QLineF const movement,
                      const QPointF &point,
                      vector<MathematicalRayProduct *> *wholeRay) override;

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

    map<ProductObservable *,vector<vector<MathematicalRayProduct *>*>> m_receiversRays;
    map<ProductObservable *,complex<double>> m_receiversField;
    vector<MathematicalTreeProduct *> m_trees;

    // Rice facor
    map<ProductObservable *,double> m_los_factor;
    map<ProductObservable *,double> m_nlos_factor;

    // Doppler spectrum
    map<vector<MathematicalRayProduct *> *,QLineF> ray_speeds;
    QLineF m_receiver_speed;
    QLineF m_ray_speed;

    //QPolygonF m_zone;
    complex<double> m_EMfieldAtReceiver;
    vector<vector<MathematicalRayProduct *>*> m_wholeRays;

    complex<double> m_EMfield;

    // Data to share with receiver
    map<ProductObservable *, Data> m_chsData;

public slots:
    void carMoved(MathematicalCarProduct *car, int, int, double) override;


};

#endif // MATHEMATICALTRANSMITTERPRODUCT_H
