#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>

#include "Product/mathematicalproduct.h"
#include "Observer/productobservable.h"
#include "Observer/windowomodelbservable.h"
#include "Observer/modelobservable.h"
#include "Product/TransmitterProduct/tx.h"
#include "Product/ReceiverProduct/rx.h"
#include "Model/algorithmInterface.h"
#include "Abstract_Factory/abstractalgorithmfactory.h"
#include "Model/mapgenerator.h"
#include "Abstract_Factory/receiverfactory.h"

using namespace std;

class Model: public ModelObservable
{
public:
    Model(WindowModelObservable* windowModelObservable);
    ~Model();

    /*!
     * \fn void addMathematicalComponent(MathematicalProduct* mathematicalProduct)
     * \brief addMathematicalComponent
     * \param mathematicalProduct
     *
     * Stores mathematicalProduct in a map according to its type.
     */
    void addMathematicalComponent(MathematicalProduct* mathematicalProduct);
    void removeMathematicalComponent(MathematicalProduct* mathematicalProduct);
    void setObservableProducts();
    void setModelObservers();
    void launchAlgorithm(AlgorithmInterface* algorithm);
    void startCars();
    Tx* selectTransmitter();
    void notify(Tx* transmitter) override;

    void setScene(QGraphicsScene*scene, BuildingFactory *buildingFactory,
                  TreeFactory *treeFactory = nullptr, CarFactory *carFactory = nullptr,
                  ReceiverFactory* receiverfactory = nullptr);           // For tests only


    /*!
     * \brief clear
     *
     * Clears all the data.
     */
    void clear();

    /*!
     *
     * \brief clearWorkspace
     *
     * DEPRECATED !!
     */
    void clearWorkspace();

//    void generateMap(unsigned h, unsigned w, unsigned cars, unsigned wstrs, unsigned strsGap, double px_to_meter);
    void generateMap(unsigned h, unsigned w,
                     unsigned min_cars, unsigned max_cars,
                     unsigned min_st_dist, unsigned max_st_dist,
                     unsigned min_st_w, unsigned max_st_w,
                     double px_to_m);

private:
    map<string,vector<MathematicalProduct*>> m_mathematicalComponents;
    WindowModelObservable* m_windowModelObservable;
    AlgorithmInterface* m_algorithm;

    ReceiverFactory* m_receiverfactory;
    thread m_thread;
    MapGenerator *m_mapGenerator;

    QGraphicsScene* m_scene;            //For tests only
};

#endif // MODEL_H
