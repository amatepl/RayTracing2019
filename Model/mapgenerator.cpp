#include "mapgenerator.h"

MapGenerator::MapGenerator(QRectF mapBoundary): m_mapBoundary(mapBoundary)
{

}

void MapGenerator::generateMap()
{
    m_horizontalStreets.clear();
    m_verticalStreets.clear();

//    QPolygonF buildingForm;
//    buildingForm << QPointF(2000,2000)
//                 << QPointF(2100,2000)
//                 << QPointF(2100,2100)
//                 << QPointF(2000,2100)
//                 << QPointF(2000,2000);



//    MathematicalProduct *building = m_buildingFactory
//                                        ->createMathematicalProduct(buildingForm);

//    m_products.push_back(building);

//    QPolygonF buildingForm2;
//    buildingForm2 << QPointF(2200,2200)
//                  << QPointF(2300,2200)
//                  << QPointF(2300,2300)
//                  << QPointF(2200,2300)
//                  << QPointF(2200,2200);

//    MathematicalProduct *building2 = m_buildingFactory
//                                        ->createMathematicalProduct(buildingForm2);

//    m_products.push_back(building2);




    int streetsDistance = 200;
    for (int i = 0; i < round(m_mapBoundary.height()/streetsDistance); i++) {
        int random1 = 0;//= rand() % 100;
        int random2 = 0;//= rand() % 100;
        QLineF *horizontalLine = new QLineF(0, i*streetsDistance + random1,
                                            m_mapBoundary.right(),
                                            i*streetsDistance + random2);

        int random3 = 0;//rand() % 100;
        int random4 = 0;//rand() % 100;
        QLineF *verticalLine = new QLineF(i*streetsDistance + random3,
                                          m_mapBoundary.top(),
                                          i*streetsDistance + random4,
                                          m_mapBoundary.bottom());


        m_horizontalStreets.push_back(horizontalLine);
        m_verticalStreets.push_back(verticalLine);

    }

    int streetWidth = 30;

    for (int i = 0; i < round(m_mapBoundary.height()/streetsDistance) - 1; i++) {
        for (int j = 0; j < round(m_mapBoundary.width()/streetsDistance) - 1; j++) {
            QPointF intersectionPoint1;
            m_horizontalStreets.at(j)->intersect(*m_verticalStreets.at(i),
                                                 &intersectionPoint1);

            QPointF intersectionPoint2;
            m_horizontalStreets.at(j + 1)->intersect(*m_verticalStreets.at(i),
                                                     &intersectionPoint2);

            QPointF intersectionPoint3;
            m_horizontalStreets.at(j)->intersect(*m_verticalStreets.at(i + 1),
                                                 &intersectionPoint3);

            QPointF intersectionPoint4;
            m_horizontalStreets.at(j + 1)->intersect(*m_verticalStreets.at(i + 1),
                                                     &intersectionPoint4);



            intersectionPoint1.setX(round(intersectionPoint1.x() + streetWidth));
            intersectionPoint1.setY(round(intersectionPoint1.y() + streetWidth));

            intersectionPoint2.setX(round(intersectionPoint2.x() + streetWidth));
            intersectionPoint2.setY(round(intersectionPoint2.y() - streetWidth));

            intersectionPoint3.setX(round(intersectionPoint3.x() - streetWidth));
            intersectionPoint3.setY(round(intersectionPoint3.y() + streetWidth));

            intersectionPoint4.setX(round(intersectionPoint4.x() - streetWidth));
            intersectionPoint4.setY(round(intersectionPoint4.y() - streetWidth));

//            intersectionPoint1.setX(intersectionPoint1.x() + streetWidth);
//            intersectionPoint1.setY(intersectionPoint1.y() + streetWidth);

//            intersectionPoint2.setX(intersectionPoint2.x() + streetWidth);
//            intersectionPoint2.setY(intersectionPoint2.y() - streetWidth);

//            intersectionPoint3.setX(intersectionPoint3.x() - streetWidth);
//            intersectionPoint3.setY(intersectionPoint3.y() + streetWidth);

//            intersectionPoint4.setX(intersectionPoint4.x() - streetWidth);
//            intersectionPoint4.setY(intersectionPoint4.y() - streetWidth);

            QPolygonF buildingForm;
            buildingForm << intersectionPoint1
                         << intersectionPoint2
                         << intersectionPoint4
                         << intersectionPoint3
                         << intersectionPoint1;

            MathematicalProduct *building = m_buildingFactory
                                                ->createMathematicalProduct(buildingForm);

            m_products.push_back(building);

        }
    }

    addCars();
    addCars();

    //addTrees();
}

void MapGenerator::addCars()
{
    QPointF carPosition;

    for (unsigned i = 1; i < m_horizontalStreets.size()-1; i++) {
        int random = rand() % (int) m_horizontalStreets.at(i)->length();
        QLineF line = *m_horizontalStreets.at(i);

        line.setLength(random);


        carPosition = line.p2();
        QLineF tmpLine(line);
        tmpLine.setLength(tmpLine.length() - 11);
        QPointF tmpPoint = tmpLine.p2();
        tmpLine.setLength(tmpLine.length() + 22);
        tmpLine.setP1(tmpPoint);

        QLineF normal = tmpLine.normalVector();
        normal.setLength(11);

        QPolygonF carContour;

        carContour << normal.p2();

        normal.translate(normal.p1() - normal.p2());
        carContour << normal.p1();

        normal.translate(tmpLine.p2() - tmpLine.p1());
        carContour << normal.p1();

        normal.translate(normal.p2() - normal.p1());
        carContour << normal.p2();

        carContour<< carContour.at(0);


        QRectF carRect(line.p2().x(), line.p2().x(), 22, 22);

        //          1 --- 4
        //          |     |
        //          |     |
        //          2 --- 3

        MathematicalProduct *car = m_carFactory->createMathematicalProduct(carPosition.x(),
                                                                           carPosition.y(),
                                                                           carContour,
                                                                           true);

        dynamic_cast<MathematicalCarProduct *>(car)->setMovement(tmpLine);

        m_products.push_back(car);
        m_cars.push_back(static_cast<MathematicalCarProduct *>(car));
        ((MathematicalCarProduct *)car)->setRoad(m_horizontalStreets.at(i));

//        thread *thread_obj = new thread (&MapGenerator::moveCar,
//                                        ref(*(MathematicalCarProduct*)car),
//                                        ref(*this),
//                                        ref(*m_horizontalStreets.at(i)));


    }

    for (unsigned j = 1; j < m_verticalStreets.size() - 1; j++) {
        int random = rand() % (int) m_verticalStreets.at(j)->length();
        QLineF line = *m_verticalStreets.at(j);
        line.setLength(random);
        carPosition = line.p2();

        QLineF tmpLine(line);
        tmpLine.setLength(tmpLine.length() - 11);
        QPointF tmpPoint = tmpLine.p2();
        tmpLine.setLength(tmpLine.length() + 22);
        tmpLine.setP1(tmpPoint);

        QLineF normal = tmpLine.normalVector();
        normal.setLength(11);

        QPolygonF carContour;

        carContour << normal.p2();

        normal.translate(normal.p1() - normal.p2());

        carContour << normal.p1();

        normal.translate(tmpLine.p2() - tmpLine.p1());

        carContour << normal.p1();

        normal.translate(normal.p2() - normal.p1());

        carContour << normal.p2();

        carContour<< carContour.at(0);

        MathematicalProduct *car = m_carFactory->createMathematicalProduct(carPosition.x(),
                                                                           carPosition.y(),
                                                                           carContour,
                                                                           true);

        dynamic_cast<MathematicalCarProduct *>(car)->setMovement(tmpLine);

        m_products.push_back(car);
        m_cars.push_back((MathematicalCarProduct *) car);
        ((MathematicalCarProduct *) car)->setRoad(m_verticalStreets.at(j));

//        thread *thread_obj = new thread (&MapGenerator::moveCar,
//                                        ref(*(MathematicalCarProduct*)car),
//                                        ref(*m_verticalStreets.at(j)));


    }

}


void MapGenerator::addTrees()
{
    QPointF treePosition;

    for (unsigned i = 0; i < m_horizontalStreets.size(); i++) {
        for (unsigned j = 0; j < m_horizontalStreets.at(i)->length(); j += m_distanceTree) {
            QLineF line = *m_horizontalStreets.at(i);
            line.setLength(j);
            treePosition = line.p2();
            MathematicalProduct *tree = m_treeFactory->createMathematicalProduct(treePosition.x(),
                                                                                 treePosition.y(),
                                                                                 true);
            m_products.push_back(tree);
            m_trees.push_back((MathematicalTreeProduct *)tree);
        }
    }

    for (unsigned i = 0; i < m_verticalStreets.size(); i++) {
        for (unsigned j = 0; j < m_horizontalStreets.at(i)->length(); j += m_distanceTree) {
            QLineF line = *m_verticalStreets.at(i);
            line.setLength(j);
            treePosition = line.p2();
            MathematicalProduct *tree = m_treeFactory->createMathematicalProduct(treePosition.x(),
                                                                                 treePosition.y(),
                                                                                 true);
            m_products.push_back(tree);
            m_trees.push_back((MathematicalTreeProduct *)tree);
        }
    }
}


void MapGenerator::startCars()
{
    m_runCars = !m_runCars;

    if (m_runCars) {

        for (unsigned i = 0; i < m_cars.size(); i++) {
            thread *thread_obj = new thread (&MapGenerator::moveCar,
                                            ref(*m_cars[i]),
                                            ref(*this),
                                            ref(*m_cars[i]->getRoad()));
            m_threads.push_back(thread_obj);
        }

    } else {
        for (unsigned i = 0; i < m_threads.size(); i++) {
            m_threads[i]->join();
        }
        m_threads.clear();
    }
}

bool MapGenerator::getRunCars() const
{
    return m_runCars;
}

void MapGenerator::moveCar(MathematicalCarProduct &car, MapGenerator &map, QLineF &street)
{

    QLineF normal; //= street.unitVector();
    QLineF str = street;
    bool run = map.getRunCars();

    while (run) {

        normal = str;

        normal.setP2(car.getPos());

        normal.setLength(normal.length() + 5);

        if (QLineF(street.p1(), normal.p2()).length() > street.length()) {

            normal.setLength(10);
            car.setPos(normal.p2());

        } else {

            car.setPos(normal.p2());

        }

        run = map.getRunCars();
        this_thread::sleep_for(std::chrono::milliseconds(200));

    }
}

void MapGenerator::moveCars(MapGenerator &mapGenerator)
{
    vector<MathematicalCarProduct *> cars = mapGenerator.getCars();

    while (true) {
        for (unsigned i = 0; i < cars.size(); i++) {
            cars.at(i)->moveCar();
        }
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

vector<MathematicalBuildingProduct *> MapGenerator::getBuildings() const
{
    return m_buildings;
}

vector<MathematicalCarProduct *> MapGenerator::getCars() const
{
    return m_cars;
}

vector<MathematicalProduct *> MapGenerator::getProducts() const
{
    return m_products;
}

void MapGenerator::setBuildingFactory(BuildingFactory *buildingFactory)
{
    m_buildingFactory = buildingFactory;
}

void MapGenerator::setCarFactory(CarFactory *carFactory)
{
    m_carFactory = carFactory;
}

void MapGenerator::setTreeFactory(TreeFactory *treeFactory)
{
    m_treeFactory = treeFactory;
}
