#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <QRectF>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "Abstract_Factory/buildingfactory.h"
#include "Abstract_Factory/carfactory.h"

#include <QGraphicsScene>   // For  tests

using namespace std;

class MapGenerator
{
public:
    MapGenerator(QRectF mapBoundary);
    void generateMap();
    void addCars();
    static void moveCar(MathematicalCarProduct &car, QLineF &street);
    static void moveCars(MapGenerator &mapGenerator);
    vector<MathematicalBuildingProduct*> getBuildings()const;
    vector<MathematicalCarProduct*> getCars()const;
    vector<MathematicalProduct*> getProducts()const;
    void setBuildingFactory(BuildingFactory* buildingFactory);
    void setCarFactory(CarFactory* carFactory);

    void setScene(QGraphicsScene* scene){m_scene = scene;}      // For tests

protected:
    QRectF m_mapBoundary;
    vector<QLineF*> m_horizontalStreets;
    vector<QLineF*> m_verticalStreets;
    vector<MathematicalBuildingProduct*> m_buildings;
    vector<MathematicalCarProduct*> m_cars;
    BuildingFactory* m_buildingFactory;
    CarFactory* m_carFactory;
    vector<MathematicalProduct*> m_products;

    QGraphicsScene* m_scene;        // For tests
};

#endif // MAPGENERATOR_H
