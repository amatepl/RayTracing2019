#ifndef COVERAGE_H
#define COVERAGE_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

/* Project Specific */
#include "Model/algorithmInterface.h"
#include "Model/imagesmethod.h"
#include "Abstract_Factory/rayfactory.h"
#include "Abstract_Factory/scenefactory.h"
#include "Widget/infowidget.h"
#include "Product/heatmap.h"

//--------------------------------------------------------------------------------------------
//
//          Defines
//
//--------------------------------------------------------------------------------------------

enum HeatmapMode {complexE, sumAbsE, prx};

//--------------------------------------------------------------------------------------------
//
//          Class Coverage
//
//--------------------------------------------------------------------------------------------

class Coverage: public ImagesMethod, public AlgorithmInterface
{
   Q_OBJECT
public:
    Coverage(SceneFactory* receiverFactory,const float scale);
    void setAttributs(map<string, vector<MathematicalProduct *> > m_mathematicalComponents);

    void choseBeams();

    // AlgorithmInterface
//    MathematicalComponent* compute(vector<Tx*> transmitter, Rx* receiver,
//                                           vector<Building*> buildings) override;
    MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> mathematicalComponents, ReceiverFactory*) override;

    void clearWorkspace() override;

    void clear();

    HeatMap *buildCoverageZone(const QRect &workingZone);
    typedef complex<double>(Coverage::*fptr)(Tx *, QPointF *);
    typedef void(Coverage::*notifptr)(QPointF *, fptr) ;
    void notifyTxs(QPointF *rx, fptr f);
    void notifyTxsRms(QPointF *rx, fptr);
    void notifyTxsPrx(QPointF *rx, fptr);
    void setDnsty(const double dnsty);

    complex<double> complexE(Tx *tx, QPointF *rx);
    complex<double> normE(Tx *tx, QPointF *rx);
    complex<double> prx(Tx *tx, QPointF *rx);

    void setHeatmapMode(int mode);
    fptr selectFct();
    notifptr selectNotifier();
    void setScale(const double &px_to_m) override;

    HeatmapMode mode() const;

protected:

    SceneFactory* m_receiverFactory;
//    float px_to_meter;
    vector <MathematicalProduct *> m_coverageRxs;
    //QPolygonF totalIlluminationZone;
    HeatMap m_heatMap;
    double m_dnsty{0.5};
    HeatmapMode m_mode {HeatmapMode::complexE};

signals:
    void computed(HeatMap *heatMap, HeatmapMode mode);

};

#endif // COVERAGE_H
