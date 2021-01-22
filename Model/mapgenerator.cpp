#include "mapgenerator.h"

MapGenerator::MapGenerator(QRectF mapBoundary): m_mapBoundary(mapBoundary)
{

}

//void MapGenerator::generateMap(unsigned h, unsigned w, unsigned carDnsty, unsigned strWidth, unsigned strGap, double px_to_meter)
void MapGenerator::generateMap(unsigned h, unsigned w,
                     unsigned min_cars, unsigned max_cars,
                     unsigned min_st_dist, unsigned max_st_dist,
                     unsigned min_st_w, unsigned max_st_w,
                     double px_to_m)
{
    m_horizontalStreets.clear();
    m_verticalStreets.clear();
    m_mapBoundary.setHeight(h);
    m_mapBoundary.setWidth(w);

    this->px_to_meter = px_to_m;
//    unsigned streetsDistance = 100;

    generateStreets(min_st_dist, max_st_dist,(unsigned) min_st_w/2, (unsigned) max_st_w/2);

    generateBuidlings(min_st_dist, max_st_dist, (unsigned) min_st_w/2, (unsigned) max_st_w/2);

//    egBuilidings();

//    for (unsigned i = 0; i < carDnsty; i++) {
    addCars(min_cars);
//    }
//    addCars();

    //addTrees();
}

void MapGenerator::generateStreets(const unsigned &min_st_dist, const unsigned &max_st_dist,
                                   const unsigned &min_st_w, const unsigned &max_st_w)
{
    for (int i = 0; i < round(m_mapBoundary.height()/(max_st_dist + 2 * max_st_w)); i++) {
        int random1 = 0;
        if (min_st_dist < max_st_dist) {
            random1 = rand() % (max_st_dist - min_st_dist);
        }

        int random2 = 0;
        if (min_st_dist < max_st_dist) {
            random2 = rand() % (max_st_dist - min_st_dist);
        }

        QLineF *horizontalLine = new QLineF(0, round(i*min_st_dist / px_to_meter + random1/ px_to_meter),
                                            round(m_mapBoundary.right() / px_to_meter),
                                            round(i*min_st_dist / px_to_meter + random2/ px_to_meter));

        int random3 = 0;
        if (min_st_dist < max_st_dist) {
            random3 = rand() % (max_st_dist - min_st_dist);
        }

        int random4 = 0;
        if (min_st_dist < max_st_dist) {
            random4 = rand() % (max_st_dist - min_st_dist);
        }

        QLineF *verticalLine = new QLineF(round(i*min_st_dist / px_to_meter + random3/ px_to_meter),
                                          round(m_mapBoundary.top() / px_to_meter),
                                          round(i*min_st_dist / px_to_meter + random4/ px_to_meter),
                                          round(m_mapBoundary.bottom() / px_to_meter));

        m_horizontalStreets.push_back(horizontalLine);
        m_verticalStreets.push_back(verticalLine);

    }
}

void MapGenerator::generateBuidlings(const unsigned &min_st_dist, const unsigned &max_st_dist,
                                     const unsigned &min_st_w, const unsigned &max_st_w)
{
    int random1 = 0;
    int random2 = 0;
    int random3 = 0;
    int random4 = 0;

    m_products.clear();
    for (int i = 0; i < round(m_mapBoundary.height()/(max_st_dist + 2*max_st_w)) - 1; i++) {

        if (min_st_w < max_st_w) {
            random2 = rand() % (max_st_w - min_st_w);
        }

        for (int j = 0; j < round(m_mapBoundary.width()/(max_st_dist + 2*max_st_w)) - 1; j++) {

            if (min_st_w < max_st_w) {
                random4 = rand() % (max_st_w - min_st_w);
            }

            QPointF intersectionPoint1;
            m_horizontalStreets.at(j)->intersects(*m_verticalStreets.at(i),
                                                  &intersectionPoint1);

            QPointF intersectionPoint2;
            m_horizontalStreets.at(j + 1)->intersects(*m_verticalStreets.at(i),
                                                      &intersectionPoint2);

            QPointF intersectionPoint3;
            m_horizontalStreets.at(j)->intersects(*m_verticalStreets.at(i + 1),
                                                  &intersectionPoint3);

            QPointF intersectionPoint4;
            m_horizontalStreets.at(j + 1)->intersects(*m_verticalStreets.at(i + 1),
                                                      &intersectionPoint4);

            intersectionPoint1.setX(round(intersectionPoint1.x() + (min_st_w + random3) / px_to_meter));
            intersectionPoint1.setY(round(intersectionPoint1.y() + (min_st_w + random1) / px_to_meter));

            intersectionPoint2.setX(round(intersectionPoint2.x() + (min_st_w + random3) / px_to_meter));
            intersectionPoint2.setY(round(intersectionPoint2.y() - (min_st_w + random2) / px_to_meter));

            intersectionPoint3.setX(round(intersectionPoint3.x() - (min_st_w + random4) / px_to_meter));
            intersectionPoint3.setY(round(intersectionPoint3.y() + (min_st_w + random1) / px_to_meter));

            intersectionPoint4.setX(round(intersectionPoint4.x() - (min_st_w + random4) / px_to_meter));
            intersectionPoint4.setY(round(intersectionPoint4.y() - (min_st_w + random2) / px_to_meter));

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

            random3 = random4;

        }

        random1 = random2;
    }
//<<<<<<< Updated upstream

//                QPolygonF buildingForm;
//                buildingForm << QPointF(0,0)
//                             << QPointF(600,0)
//                             << QPointF(600,200)
//                             << QPointF(0,200)
//                             << QPointF(0,0);

//                MathematicalProduct *building = m_buildingFactory
//                                                    ->createMathematicalProduct(buildingForm);

//                m_products.push_back(building);

//                QPolygonF buildingForm2;
//                buildingForm2 << QPointF(0,260)
//                             << QPointF(600,260)
//                             << QPointF(600,410)
//                             << QPointF(0,410)
//                             << QPointF(0,260);

//                MathematicalProduct *building2 = m_buildingFactory
//                                                    ->createMathematicalProduct(buildingForm2);

//                m_products.push_back(building2);

//    addCars(car);
//    addCars();

    //addTrees();

}

void MapGenerator::addCars(unsigned carDnsty)
{
    QPointF carPos;

    for (unsigned i = 1; i < m_horizontalStreets.size()-1; i++) {

        vector<float> freePlaces = carPlaces(m_horizontalStreets.at(i), m_carParams.l / px_to_meter, 1 / px_to_meter);

        unsigned nbCars = 0;
        while (nbCars < carDnsty && freePlaces.size()) {
            carPos = carPoistion(&freePlaces, m_horizontalStreets.at(i));

            QPolygonF carContour = createPolyCar(&carPos, m_horizontalStreets.at(i));

            MathematicalProduct *car = m_carFactory->createMathematicalProduct(carPos.x(),
                                                                               carPos.y(),
                                                                               carContour,
                                                                               true);
            QLineF tmpLine = *m_horizontalStreets.at(i);
            tmpLine.setLength(m_carParams.l);
            tmpLine.translate(carPos - tmpLine.p1());
            dynamic_cast<Car *>(car)->setMovement(tmpLine);

            m_products.push_back(car);
            m_cars.push_back(static_cast<Car *>(car));
            ((Car *)car)->setRoad(m_horizontalStreets.at(i));

            QPolygonF carPoly = *dynamic_cast<QPolygonF *>(car);



            //        thread *thread_obj = new thread (&MapGenerator::moveCar,
            //                                        ref(*(Car*)car),
            //                                        ref(*this),
            //                                        ref(*m_horizontalStreets.at(i)));

            nbCars++;
        }
    }

    for (unsigned j = 1; j < m_verticalStreets.size() - 1; j++) {
        vector<float> freePlaces = carPlaces(m_verticalStreets.at(j), m_carParams.l / px_to_meter, 1 / px_to_meter);

        unsigned nbCars = 0;
        while (nbCars < carDnsty && freePlaces.size()) {
            carPos = carPoistion(&freePlaces, m_verticalStreets.at(j));

            QPolygonF carContour = createPolyCar(&carPos, m_verticalStreets.at(j));

            MathematicalProduct *car = m_carFactory->createMathematicalProduct(carPos.x(),
                                                                               carPos.y(),
                                                                               carContour,
                                                                               true);
            QLineF tmpLine = *m_verticalStreets.at(j);
            tmpLine.setLength(m_carParams.l);
            tmpLine.translate(carPos - tmpLine.p1());
            dynamic_cast<Car *>(car)->setMovement(tmpLine);

            m_products.push_back(car);
            m_cars.push_back(static_cast<Car *>(car));
            ((Car *)car)->setRoad(m_verticalStreets.at(j));

            QPolygonF carPoly = *dynamic_cast<QPolygonF *>(car);

            //        thread *thread_obj = new thread (&MapGenerator::moveCar,
            //                                        ref(*(Car*)car),
            //                                        ref(*this),
            //                                        ref(*m_verticalStreets.at(i)));
            nbCars++;
        }

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


void MapGenerator::egBuilidings()
{
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

//    QPolygonF buildingForm;
//    buildingForm << QPointF(0,0)
//                 << QPointF(2000,0)
//                 << QPointF(2000,200)
//                 << QPointF(0,200)
//                 << QPointF(0,0);

//    MathematicalProduct *building = m_buildingFactory
//                                        ->createMathematicalProduct(buildingForm);

//    m_products.push_back(building);

//    QPolygonF buildingForm2;
//    buildingForm2 << QPointF(0,260)
//                 << QPointF(2000,260)
//                 << QPointF(2000,410)
//                 << QPointF(0,410)
//                 << QPointF(0,260);

//    MathematicalProduct *building2 = m_buildingFactory
//                                        ->createMathematicalProduct(buildingForm2);

//    m_products.push_back(building2);

    QPolygonF buildingForm;
    buildingForm << QPointF(0,0)
                 << QPointF(50,0)
                 << QPointF(50,300)
                 << QPointF(0,300)
                 << QPointF(0,0);

    MathematicalProduct *building = m_buildingFactory
                                        ->createMathematicalProduct(buildingForm);

    m_products.push_back(building);

    QPolygonF buildingForm2;
    buildingForm2 << QPointF(50,300)
                 << QPointF(450,300)
                 << QPointF(450,500)
                 << QPointF(50,500)
                 << QPointF(50,300);

    MathematicalProduct *building2 = m_buildingFactory
                                        ->createMathematicalProduct(buildingForm2);

    m_products.push_back(building2);

    QPolygonF buildingForm3;
    buildingForm3 << QPointF(62,0)
                 << QPointF(450,0)
                 << QPointF(450,288)
                 << QPointF(62,288)
                 << QPointF(62,0);

    MathematicalProduct *building3 = m_buildingFactory
                                        ->createMathematicalProduct(buildingForm3);

    m_products.push_back(building3);

//        QPolygonF buildingForm;
//        buildingForm << QPointF(0,0)
//                     << QPointF(100,0)
//                     << QPointF(100,100)
//                     << QPointF(0,100)
//                     << QPointF(0,0);

//        MathematicalProduct *building = m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm);

//        m_products.push_back(building);

//        QPolygonF buildingForm2;
//        buildingForm2 << QPointF(160,0)
//                     << QPointF(260,0)
//                     << QPointF(260,100)
//                     << QPointF(160,100)
//                     << QPointF(160,0);

//        MathematicalProduct *building2 = m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm2);

//        m_products.push_back(building2);

//        QPolygonF buildingForm3;
//        buildingForm3 << QPointF(320,0)
//                     << QPointF(420,0)
//                     << QPointF(420,100)
//                     << QPointF(320,100)
//                     << QPointF(320,0);

//        MathematicalProduct *building3 = m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm3);

//        m_products.push_back(building3);

//        QPolygonF buildingForm4;
//        buildingForm4 << QPointF(0,160)
//                     << QPointF(100,160)
//                     << QPointF(100,260)
//                     << QPointF(0,260)
//                     << QPointF(0,160);

//        MathematicalProduct *building4= m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm4);

//        m_products.push_back(building4);

//        QPolygonF buildingForm5;
//        buildingForm5 << QPointF(160,160)
//                     << QPointF(260,160)
//                     << QPointF(260,260)
//                     << QPointF(160,260)
//                     << QPointF(160,160);

//        MathematicalProduct *building5 = m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm5);

//        m_products.push_back(building5);

//        QPolygonF buildingForm6;
//        buildingForm6 << QPointF(320,160)
//                     << QPointF(420,160)
//                     << QPointF(420,260)
//                     << QPointF(320,260)
//                     << QPointF(320,160);

//        MathematicalProduct *building6 = m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm6);

//        m_products.push_back(building6);

//        QPolygonF buildingForm7;
//        buildingForm7 << QPointF(0,320)
//                     << QPointF(100,320)
//                     << QPointF(100,420)
//                     << QPointF(0,420)
//                     << QPointF(0,320);

//        MathematicalProduct *building7= m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm7);

//        m_products.push_back(building7);

//        QPolygonF buildingForm8;
//        buildingForm8 << QPointF(160,320)
//                     << QPointF(260,320)
//                     << QPointF(260,420)
//                     << QPointF(160,420)
//                     << QPointF(160,320);

//        MathematicalProduct *building8 = m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm8);

//        m_products.push_back(building8);

//        QPolygonF buildingForm9;
//        buildingForm9 << QPointF(320,320)
//                     << QPointF(420,320)
//                     << QPointF(420,420)
//                     << QPointF(320,420)
//                     << QPointF(320,320);

//        MathematicalProduct *building9 = m_buildingFactory
//                                            ->createMathematicalProduct(buildingForm9);

//        m_products.push_back(building9);


}

// Create an vector of possible positions
// use radom to select a position and pop it out from the vector
vector<float> MapGenerator::carPlaces(const QLineF *str, float length, float followindDist)
{
    vector<float> res;
    int nbSegments = (int) str->length() / (length + followindDist);
    for (int i = 0; i < nbSegments; i++) {
        res.push_back(i * (length + followindDist));
    }
    return res;
}

QPointF MapGenerator::carPoistion(vector<float> *places, const QLineF *str)
{
    int nbFreePlaces = places->size();
    int segmentIdx = rand() % nbFreePlaces;
    float segment = places->at(segmentIdx);
    places->erase(places->begin() + segmentIdx);
    QLineF l = *str;
    l.setLength(segment);
    return l.p2();
}

QPolygonF MapGenerator::createPolyCar(const QPointF *pos, const QLineF *str)
{
    //          1 --- 4
    //          |     |
    //          |     |
    //          2 --- 3

    QLineF line = *str;
    line.setP2(*pos);
    QLineF tmpLine(line);
    tmpLine.setLength(tmpLine.length() - (m_carParams.l/2)/px_to_meter);
    QPointF tmpPoint = tmpLine.p2();
    tmpLine.setLength(tmpLine.length() + m_carParams.l/px_to_meter);
    tmpLine.setP1(tmpPoint);

    QLineF normal = tmpLine.normalVector();
    normal.setLength((m_carParams.w/2)/px_to_meter);

    QPolygonF carContour;

    carContour << normal.p2();

    normal.translate(normal.p1() - normal.p2());
    carContour << normal.p1();

    normal.translate(tmpLine.p2() - tmpLine.p1());
    carContour << normal.p1();

    normal.translate(normal.p2() - normal.p1());
    carContour << normal.p2();

    carContour<< carContour.at(0);

    return carContour;
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

void MapGenerator::moveCar(Car &car, MapGenerator &map, QLineF &street)
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
    vector<Car *> cars = mapGenerator.getCars();

    while (true) {
        for (unsigned i = 0; i < cars.size(); i++) {
            cars.at(i)->moveCar();
        }
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

vector<Building *> MapGenerator::getBuildings() const
{
    return m_buildings;
}

vector<Car *> MapGenerator::getCars() const
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

void MapGenerator::clear()
{
    deleteElmnts<QLineF>(m_horizontalStreets);
    m_horizontalStreets.clear();

    deleteElmnts<QLineF>(m_verticalStreets);
    m_verticalStreets.clear();

    deleteElmnts<thread>(m_threads);
    m_threads.clear();

    m_buildings.clear();
    m_cars.clear();
    m_trees.clear();
    m_products.clear();
}
