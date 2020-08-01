#ifndef IMAGESMETHOD_H
#define IMAGESMETHOD_H

#include <vector>
#include <QPolygonF>
#include <map>

#include "Share/line.h"
#include "Share/wall.h"
#include "Model/algorithmInterface.h"
#include "Product/abstractantena.h"
#include "Product/BuildingProduct/mathematicalbuildingproduct.h"
#include "Product/TreeProduct/mathematicaltreeproduct.h"
#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"
#include "Product/ReceiverProduct/mathematicalreceiverproduct.h"
#include "Product/TransmitterProduct/transmitterimage.h"
#include "Product/TransmitterProduct/antenadiffraction.h"
#include "Product/CarProduct/mathematicalcarproduct.h"
#include <QGraphicsScene>

class AbstractRayFactory;

using namespace std;

struct forImage;

class ImagesMethod: public QObject
{
public:
    void createImages();
    void setObservers();
    void connectToCars(AbstractAntena *ant);
    void disconnectCars(AbstractAntena * ant);
    void disconnectAllCars();
    void clearImages(MathematicalTransmitterProduct *tx);
    void clearAllImages();


    void setDiffraction(vector<Wall *> walls, const QPolygonF &zone, AbstractAntena *parent);
    forImage transmitterIllumination(MathematicalTransmitterProduct *transmitter);
    QPolygonF buildingsInIlluminationZone(AbstractAntena *ant, int nbReflections);
    vector <Line> illuminatedWalls(vector <Wall *> walls, const QPolygonF zone,
                                  int nbReflections, AbstractAntena *parent);
    void setRayFactory(AbstractRayFactory* rayFactory){m_rayFactory = rayFactory;};
    void buildDiffractionPoints(const QPolygonF &zone, vector<Wall *> illuminatedWalls,
                                int nbReflections, AbstractAntena *parent);


    void illuminationZones();
    void launchAlgorithm();
    QPolygonF buildIlluminationZone(AbstractAntena *ant);
    vector <Line> createImages(vector<Wall *> walls, const QPolygonF zone,
                              int nbReflections, AbstractAntena *parent);

    void connectTxsCars();

    void setScene(QGraphicsScene *scene) {m_scene = scene;};

protected:
    vector<MathematicalTransmitterProduct *> m_transmitters;
    vector<MathematicalBuildingProduct *> m_buildings;
    vector<MathematicalCarProduct *> m_cars;
    vector<MathematicalTreeProduct *> m_trees;

    MathematicalReceiverProduct *m_receiver;
    vector<MathematicalReceiverProduct *> m_receivers;
    int reflectionsNumber;
    MathematicalTransmitterProduct *m_currentTx;
    AbstractRayFactory *m_rayFactory;
    map<MathematicalTransmitterProduct *, vector<AbstractAntena *>> m_images;


    QGraphicsScene *m_scene;

    QPolygonF m_currentTransmitterRange;
    QPolygonF m_totalIlluminationZone;            // For tests


public slots:

    void recomputeImages(AbstractAntena *tx);

};

#endif // IMAGESMETHOD_H
