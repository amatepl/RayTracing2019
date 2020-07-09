#ifndef IMAGESMETHOD_H
#define IMAGESMETHOD_H

#include <vector>
#include <QPolygonF>

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

#include <QGraphicsScene>

class AbstractRayFactory;

using namespace std;

struct forImage;

class ImagesMethod
{
public:
    void createImages();
    void setDiffraction(vector<Wall *> walls,const QPolygonF &zone, AbstractAntena *parent);
    forImage transmitterIllumination(MathematicalTransmitterProduct *transmitter);
    QPolygonF buildingsInIlluminationZone(AbstractAntena *ant, int nbReflections);
    vector <Line> illuminatedWalls(vector <Wall*> walls, const QPolygonF zone, int nbReflections, AbstractAntena *parent);
    void setRayFactory(AbstractRayFactory* rayFactory){m_rayFactory = rayFactory;};
    void buildDiffractionPoints(const QPolygonF &zone, vector<Wall *> illuminatedWalls, int nbReflections, AbstractAntena *parent);


    void illuminationZones();
    QPolygonF buildIlluminationZone(AbstractAntena *ant);
    vector <Line> createImages(vector<Wall *> walls, const QPolygonF zone, int nbReflections, AbstractAntena *parent);


    void setScene(QGraphicsScene* scene){m_scene=scene;};

protected:
    vector<MathematicalTransmitterProduct*> m_transmitters;
    vector<MathematicalBuildingProduct*> m_buildings;
    vector<MathematicalTreeProduct*> m_trees;

    MathematicalReceiverProduct* m_receiver;
    vector<MathematicalReceiverProduct*> m_receivers;
    int reflectionsNumber;
    AbstractRayFactory* m_rayFactory;


    QGraphicsScene* m_scene;

    QPolygonF m_currentTransmitterRange;
    QPolygonF m_totalIlluminationZone;            // For tests



};

#endif // IMAGESMETHOD_H
