#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "Model/imagesmethod.h"
#include "Product/TransmitterProduct/tx.h"
#include "Product/ReceiverProduct/rx.h"
#include "Abstract_Factory/rayfactory.h"
#include "Model/algorithmInterface.h"
#include "Model/imagesmethod.h"
#include "Abstract_Factory/receiverfactory.h"
#include "Widget/infowidget.h"

/*!
 * \class RayTracing
 * \brief The RayTracing class
 *
 * Manages ray tracing related tasks.
 */
class RayTracing: public AlgorithmInterface, public ImagesMethod
{
public:
    RayTracing(Tx* transmitter, Rx*, const float scale);
    RayTracing(const float scale);

    //AlgorithmInterface
//    MathematicalComponent* compute(vector<Tx *> transmitters, Rx* receiver,
//                                   vector<Building*> buildings) override;
    /*!
     * \fn compute
     * \brief compute
     * \param mathematicalComponents
     * \param receiverfactory
     * \return
     *
     * RETURN NULL PTR
     *
     * Launches ray tracing by notifying the transmitters about the receiver position.
     *
     * It also assign to everey rensmitter a ray factory that returns rays with a
     * grahics representation.
     */
    MathematicalComponent* compute(map<string,vector<MathematicalProduct*>> mathematicalComponents, ReceiverFactory* receiverfactory) override;

    /*!
     * \fn void clearWorkspace()
     * \brief Deletes the transmitters and the receivers.
     */
    void clearWorkspace() override;

    /*!
     * \fn void setAttributs(map<string,vector<MathematicalProduct*>> mathematicalComponents)
     * \brief setAttributs
     * \param mathematicalComponents
     *
     * Sets the mediator for every transmitter.
     *
     * Decodes map elements added by the user and attributes them to corresponding vectors.
     */
    void setAttributs(map<string,vector<MathematicalProduct*>> mathematicalComponents);

private:
    ReceiverFactory* m_receiverfactory;
//    Rx* copy_receiver;
    float px_to_meter;

};

#endif // RAYTRACING_H
