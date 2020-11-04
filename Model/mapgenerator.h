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

    /* Generators */
    void generateMap(unsigned h, unsigned w, unsigned carDnsty, unsigned strWidth, unsigned strGap, double px_to_meter);
    void generateStreets(const unsigned streetsDistance);
    void generateBuidlings(const unsigned streetsDistance, const unsigned streetWidth);
    void addCars();
    void addTrees();
    void egBuilidings();

    /* Dynamics */
    void startCars();
    bool getRunCars() const;
    static void moveCar(MathematicalCarProduct &car, MapGenerator &map, QLineF &street);
    static void moveCars(MapGenerator &mapGenerator);
    vector<Building *> getBuildings() const;
    vector<MathematicalCarProduct *> getCars() const;
    vector<MathematicalProduct *> getProducts() const;

    /* Modifiers */
    void setBuildingFactory(BuildingFactory *buildingFactory);
    void setCarFactory(CarFactory *carFactory);
    void setTreeFactory(TreeFactory *treeFactory);

    void setScene(QGraphicsScene *scene){m_scene = scene;}      // For tests
    void clear();

    template<class T>
    void deleteElmnts(vector<T *> vec)
    {
        for(T* t: vec){
            delete t;
        }
    }

protected:
    double px_to_meter;
    QRectF m_mapBoundary;
    vector<QLineF *> m_horizontalStreets;
    vector<QLineF *> m_verticalStreets;
    vector<Building *> m_buildings;
    vector<MathematicalCarProduct *> m_cars;
    vector<MathematicalTreeProduct *> m_trees;
    BuildingFactory *m_buildingFactory;
    CarFactory *m_carFactory;
    TreeFactory *m_treeFactory;
    vector<MathematicalProduct *> m_products;
    vector<thread *> m_threads;
    int m_distanceTree{ 50 };
    bool m_runCars{false};

    // FOR TESTS
    QGraphicsScene *m_scene;
    TransmitterFactory *m_transmitterFactory;
};

#endif // MAPGENERATOR_H
