#ifndef IMAGESMETHOD_H
#define IMAGESMETHOD_H

#include <vector>
#include <QPolygonF>
#include <map>

#include "Share/line.h"
#include "Share/wall.h"
#include "Model/algorithmInterface.h"
#include "Product/abstractantena.h"
#include "Product/BuildingProduct/building.h"
#include "Product/TreeProduct/mathematicaltreeproduct.h"
#include "Product/TransmitterProduct/tx.h"
#include "Product/ReceiverProduct/rx.h"
#include "Product/TransmitterProduct/tximg.h"
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
    void clearImages(Tx *tx);
    void clearAllImages();


    void setDiffraction(vector<Wall *> walls, const QPolygonF &zone, AbstractAntena *parent);
    forImage transmitterIllumination(Tx *transmitter);
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

    void setReflectionsNbr(unsigned reflectionsNbr);

    void clear();

protected:
    vector<Tx *> m_transmitters;
    vector<Building *> m_buildings;
    vector<MathematicalCarProduct *> m_cars;
    vector<MathematicalTreeProduct *> m_trees;

    Rx *m_receiver;
    vector<Rx *> m_receivers;
    int reflectionsNumber;
    Tx *m_currentTx;
    AbstractRayFactory *m_rayFactory;
    map<Tx *, vector<AbstractAntena *>> m_images;


    QGraphicsScene *m_scene;

    QPolygonF m_currentTransmitterRange;
    QPolygonF m_totalIlluminationZone;            // For tests


public slots:

    void recomputeImages(AbstractAntena *);

};

#endif // IMAGESMETHOD_H
