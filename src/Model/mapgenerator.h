#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

#include <QRectF>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

/* Project Specigic */

#include "Abstract_Factory/buildingfactory.h"
#include "Abstract_Factory/carfactory.h"
#include "Abstract_Factory/treefactory.h"

// For  tests
#include <QGraphicsScene>
#include "Abstract_Factory/transmitterfactory.h"

//--------------------------------------------------------------------------------------------
//
//          Defines
//
//--------------------------------------------------------------------------------------------

using namespace std;

//--------------------------------------------------------------------------------------------
//
//          Class Street
//
//--------------------------------------------------------------------------------------------

/*!
 * \class Street
 *
 * \brief It is a QLineF with width.
 */
class Street: public QLineF
{
public:

    /*!
     * \fn Street::Street()
     *
     * Constructs a null street.
     */
    Street();

    /*!
     * \fn Street::Street(double x1, double y1, double x2, double y2, const double w)
     *
     * Constructs a street object that represents the street between (x1, y1) and (x2, y2)
     * of width \a w.
     */
    Street(double x1, double y1, double x2, double y2, const double w);

    /*!
     * \fn Street::Street(const QPointF &p1, const QPointF &p2, const double w)
     *
     * Constructs a street object that represents the street between p1 and p2 and of
     * width \a w.
     */
    Street(const QPointF &p1, const QPointF &p2, const double w);

    /*!
     * \fn double Street::width() const
     *
     * Returns the width of the street.
     */
    double width() const;

    /*!
     * \fn void Street::setWidth(double w)
     *
     * Sets the width of the street.
     */
    void setWidth(double w);

private:
    double m_w{0};
};

//--------------------------------------------------------------------------------------------
//
//          Class MapGenerator
//
//--------------------------------------------------------------------------------------------

class MapGenerator
{
public:
    MapGenerator(QRectF mapBoundary);

    /* Generators */
//    void generateMap(unsigned h, unsigned w, unsigned carDnsty, unsigned strWidth, unsigned strGap, double px_to_meter);
    void generateMap(unsigned h, unsigned w,
                     unsigned min_cars, unsigned max_cars,
                     unsigned min_st_dist, unsigned max_st_dist,
                     unsigned min_st_w, unsigned max_st_w,
                     double px_to_m);
    void generateStreets(const unsigned &min_st_dist, const unsigned &max_st_dist,
                         const unsigned &min_st_w, const unsigned &max_st_w);
    void generateBuidlings();
    void addCars(unsigned min_cars, unsigned max_cars);
    void addTrees();
    void egBuilidings();

    /*!
     * \fn vector<float> carPlaces(const QLineF *str, float length)
     *
     * Generate a vector of all the possible positions of a car in a street \a str.
     */
    vector<float> carPlaces(const QLineF *str, float length, float followindDist);
    QPointF carPoistion(vector<float> *places, const QLineF *str);
    QPolygonF createPolyCar(const QPointF *pos, const QLineF *str);

    /* Dynamics */
    void startCars();
    bool getRunCars() const;
    static void moveCar(Car &car, MapGenerator &map, QLineF &street);
    static void moveCars(MapGenerator &mapGenerator);
    vector<Building *> getBuildings() const;
    vector<Car *> getCars() const;
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
    struct CarParams {float l=4; float w=1.8;} m_carParams;
    double px_to_meter;
    QRectF m_mapBoundary;
    vector<Street *> m_horizontalStreets;
    vector<Street *> m_verticalStreets;
    vector<Building *> m_buildings;
    vector<Car *> m_cars;
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
