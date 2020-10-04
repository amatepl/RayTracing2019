#ifndef COVERAGE_H
#define COVERAGE_H

#include "Model/algorithmInterface.h"
#include "Model/imagesmethod.h"
#include "Abstract_Factory/rayfactory.h"
#include "Abstract_Factory/scenefactory.h"
#include "Widget/infowidget.h"

class Coverage: public AlgorithmInterface, public ImagesMethod
{
public:
    Coverage(SceneFactory* receiverFactory,const float scale);
    void setAttributs(map<string, vector<MathematicalProduct *> > m_mathematicalComponents);

    void choseBeams();

    // AlgorithmInterface
//    MathematicalComponent* compute(vector<Tx*> transmitter, Rx* receiver,
//                                           vector<Building*> buildings) override;
    MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> mathematicalComponents, ReceiverFactory*) override;

    void clearWorkspace() override;

    vector<QRectF> buildCoverageZone();

protected:
    SceneFactory* m_receiverFactory;
    float px_to_meter;
    vector <MathematicalProduct *> m_coverageRxs;
    //QPolygonF totalIlluminationZone;
};

#endif // COVERAGE_H
