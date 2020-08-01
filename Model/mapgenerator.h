#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <QRectF>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "Abstract_Factory/buildingfactory.h"
#include "Abstract_Factory/carfactory.h"
#include "Abstract_Factory/treefactory.h"

// For  tests
#include <QGraphicsScene>
#include "Abstract_Factory/transmitterfactory.h"

using namespace std;

class MapGenerator
{
public:
    MapGenerator(QRectF mapBoundary);
    void generateMap();
    void addCars();
    void addTrees();
    static void moveCar(MathematicalCarProduct &car, QLineF &street);
    static void moveCars(MapGenerator &mapGenerator);
    vector<MathematicalBuildingProduct *> getBuildings() const;
    vector<MathematicalCarProduct *> getCars() const;
    vector<MathematicalProduct *> getProducts() const;
    void setBuildingFactory(BuildingFactory *buildingFactory);
    void setCarFactory(CarFactory *carFactory);
    void setTreeFactory(TreeFactory *treeFactory);

    void setScene(QGraphicsScene *scene){m_scene = scene;}      // For tests

protected:
    QRectF m_mapBoundary;
    vector<QLineF *> m_horizontalStreets;
    vector<QLineF *> m_verticalStreets;
    vector<MathematicalBuildingProduct *> m_buildings;
    vector<MathematicalCarProduct *> m_cars;
    vector<MathematicalTreeProduct *> m_trees;
    BuildingFactory *m_buildingFactory;
    CarFactory *m_carFactory;
    TreeFactory *m_treeFactory;
    vector<MathematicalProduct *> m_products;
    int m_distanceTree{ 50 };

    // FOR TESTS
    QGraphicsScene *m_scene;
    TransmitterFactory *m_transmitterFactory;
};

#endif // MAPGENERATOR_H
