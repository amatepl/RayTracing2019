#ifndef COVERAGE_H
#define COVERAGE_H

#include "Model/algorithmInterface.h"
#include "Model/imagesmethod.h"
#include "Abstract_Factory/rayfactory.h"
#include "Abstract_Factory/scenefactory.h"

class Coverage: public AlgorithmInterface, public ImagesMethod
{
public:
    Coverage(SceneFactory* receiverFactory);
    void setAttributs(map<string, vector<MathematicalProduct *> > m_mathematicalComponents);

    // AlgorithmInterface
    MathematicalComponent* compute(vector<MathematicalTransmitterProduct*> transmitter, MathematicalReceiverProduct* receiver,
                                           vector<MathematicalBuildingProduct*> buildings) override;
    MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> mathematicalComponents) override;

    void sendData(MathematicalProduct *transmitter, MathematicalProduct *receiver) override;
    vector<QRectF> buildCoverageZone();

protected:
    SceneFactory* m_receiverFactory;
    //QPolygonF totalIlluminationZone;
};

#endif // COVERAGE_H
