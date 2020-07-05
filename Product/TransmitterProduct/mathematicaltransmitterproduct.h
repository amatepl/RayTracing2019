#ifndef MATHEMATICALTRANSMITTERPRODUCT_H
#define MATHEMATICALTRANSMITTERPRODUCT_H

#include "math.h"
#include "complex.h"
#include <iostream>
#include <QPointF>
#include <QPolygonF>
#include <vector>

#include "transmitterproduct.h"
#include "dialogtransmitterproduct.h"
#include "Product/mathematicalproduct.h"
#include "Abstract_Factory/abstractrayfactory.h"

#include "Observer/productobserver.h"
#include "Observer/productobservable.h"
#include "Observer/modelobserver.h"
#include "Observer/modelobservable.h"

#include <Product/RayProduct/mathematicalrayproduct.h>
#include <Product/abstractantena.h>


using namespace std;

class MathematicalTransmitterProduct : public QPointF, public MathematicalProduct, public ProductObserver, public ModelObserver,
        public AbstractAntena, public TransmitterProduct
{
public:
    MathematicalTransmitterProduct(int posX, int posY);
    ~MathematicalTransmitterProduct() override;

    void drawRays();
    QPolygonF buildCoverage();

    //virtual void setModel(Model model) override;

    complex <double> computeEfieldGround(ProductObservable *receiver);
    complex<double> computeEMfield(vector<MathematicalRayProduct*> *rayLine,ProductObservable* receiver);
    double distance(ProductObservable *receiver);
    complex<double> computeDiffractedEfield(vector<MathematicalRayProduct*> *rayLine);
    double computePrx(complex <double> totalEfield);
    double dBm(double power);

    double computeReflexionPer(double thetaI, double epsilonR);
    double computeReflexionPar(double thetaI, double epsilonR);
    vector<vector<MathematicalRayProduct *> *> getRays();
    void notifyObservables();
    QPointF sceneRectIntersection(const QRectF &rect, const QLineF &line)const;
    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const;
    void setSceneBoundary(const QRectF &rect);


    // ProductObserver
    //void update(const QPointF *productObservable, const float speed, const float direction) override{};
    void update(ProductObservable *receiver, const float speed, const float direction) override;
    void drawRays(ProductObservable* productObservable, bool draw) override;

    //ModelObserver
    void attachObservable(ModelObservable* modelObserver) override;
    void attachObservable(ProductObservable *productObservable) override;

    // Vector to receive all the physical informations to share
    std::vector <double> attenuation(ProductObservable *receiver) {return m_attenuation[receiver];}
    std::vector <double> rayLength(ProductObservable* receiver) {return m_raylength[receiver];}
//==============
    // From TransmitterProduct
    int getPosX() override {return x();}
    int getPosY() override {return y();}
    double getOrientation() override {return m_orientation;}
    Kind getKind() override {return m_kind;}
    double getPower() override {return m_power;}
    int getRow() override {return m_row;}
    int getColumn() override {return m_column;}
    unsigned long getFrequency() override {return m_frequency;}

    void setPosX(int posX) override {setX(posX);}
    void setPosY(int posY) override {setY(posY);}
    void setOrientation(double orientation) override {m_orientation = orientation;}
    void setPower(double power) override {m_power = power;}
    void setFrequency(unsigned long frequency) override {m_frequency = frequency;}
    void setRow(int row) override {m_row = row;}
    void setColumn(int column) override {m_column = column;}
    void setKind(Kind kind) override {m_kind = kind;}
    void newProperties() override;

    // From MathematicalProduct
    void update(QGraphicsItem *graphic) override;
//>>>>>>> d1ec8e004ad1b2afa2d74871dff3deaf7bbc3b77
    void openDialog() override;

//    // From ProductObserver
//    void notify(const QPointF &pos) override;
//    void attachObservable(ProductObservable *productObservable) override;

//    // From ModelObserver
//    void attachObservable(ModelObservable* modelObserver) override;


//    QPointF sceneRectIntersection(const QRectF &rect, const QLineF &line)const;
//    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const;

    //AbstractAntenna
    void notifyParent(ProductObservable *productObservable,const float speed, const float direction, const QPointF &point, vector<MathematicalRayProduct *> *wholeRay) override;

    QPointF getPosition()const override;
    QPolygonF getIlluminationZone(const QRectF &rect)const override;
    QPolygonF getIlluminationZone()const override;
    void setIlluminatedZone(const QPolygonF &zone) override;
    QPolygonF getIlluminatedZone()const override;



private:
    float m_orientation;
    double m_power;
    Kind m_kind;

    double m_powerAtReceiver;
    ModelObservable* m_model;
    vector<ProductObservable*> m_productObservable;
    //map<const QPointF*,vector<vector<MathematicalRayProduct*>*>> m_receiversRays;

    map<ProductObservable*,vector<vector<MathematicalRayProduct*>*>> m_receiversRays;
    map<ProductObservable*,complex<double>> m_receiversField;
    map<ProductObservable*,vector<double>> m_receiversPowers;
    map<ProductObservable*,vector<double>> m_attenuation;
    map<ProductObservable*,vector<double>> m_raylength;

    int m_radius;

    QRectF m_sceneBoundary;


    //QPolygonF m_zone;
    complex<double> m_EMfieldAtReceiver;
    vector<vector<MathematicalRayProduct*>*> m_wholeRays;

    complex<double> m_EMfield;
};

#endif // MATHEMATICALTRANSMITTERPRODUCT_H
