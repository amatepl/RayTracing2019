#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <QRectF>
#include <vector>
#include <iostream>

#include "Abstract_Factory/buildingfactory.h"

#include <QGraphicsScene>   // For  tests

using namespace std;

class MapGenerator
{
public:
    MapGenerator(QRectF mapBoundary);
    void generateMap();
    vector<MathematicalBuildingProduct*> getBuildings()const;
    vector<MathematicalProduct*> getProducts()const;
    void setBuildingFactory(BuildingFactory* buildingFactory);

    void setScene(QGraphicsScene* scene){m_scene = scene;}      // For tests

protected:
    QRectF m_mapBoundary;
    vector<QLineF*> m_horizontalStreets;
    vector<QLineF*> m_verticalStreets;
    vector<MathematicalBuildingProduct*> m_buildings;
    BuildingFactory* m_buildingFactory;
    vector<MathematicalProduct*> m_products;

    QGraphicsScene* m_scene;        // For tests
};

#endif // MAPGENERATOR_H
