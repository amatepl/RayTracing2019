#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "Model/imagesmethod.h"
#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"
#include "Abstract_Factory/rayfactory.h"
#include "Model/algorithmInterface.h"
#include "Model/imagesmethod.h"
#include "Abstract_Factory/receiverfactory.h"
#include "Widget/infowidget.h"

class RayTracing: public AlgorithmInterface, public ImagesMethod
{
public:
    RayTracing(MathematicalTransmitterProduct* transmitter, MathematicalReceiverProduct*, const float scale);
    RayTracing(const float scale);

    //AlgorithmInterface
//    MathematicalComponent* compute(vector<MathematicalTransmitterProduct *> transmitters, MathematicalReceiverProduct* receiver,
//                                   vector<MathematicalBuildingProduct*> buildings) override;
    MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> mathematicalComponents, ReceiverFactory* receiverfactory) override;

    void clearWorkspace() override;
    void setAttributs(map<string,vector<MathematicalProduct*>> mathematicalComponents);

private:
    ReceiverFactory* m_receiverfactory;
//    MathematicalReceiverProduct* copy_receiver;
    float px_to_meter;

};

#endif // RAYTRACING_H
