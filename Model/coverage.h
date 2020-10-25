#ifndef COVERAGE_H
#define COVERAGE_H

#include "Model/algorithmInterface.h"
#include "Model/imagesmethod.h"
#include "Abstract_Factory/rayfactory.h"
#include "Abstract_Factory/scenefactory.h"
#include "Widget/infowidget.h"
#include "Product/heatmap.h"

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

    HeatMap *buildCoverageZone(const QRect &workingZone);
    void notifyTxs(QPointF *rx);

protected:
    SceneFactory* m_receiverFactory;
    float px_to_meter;
    vector <MathematicalProduct *> m_coverageRxs;
    //QPolygonF totalIlluminationZone;
    HeatMap m_heatMap;
    double m_dnsty{0.5};

signals:
    void computed(HeatMap *heatMap);

};

#endif // COVERAGE_H
