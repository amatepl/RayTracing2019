#include "mapgenerator.h"

MapGenerator::MapGenerator(QRectF mapBoundary):m_mapBoundary(mapBoundary)
{

}

void MapGenerator::generateMap()
{
    m_horizontalStreets.clear();
    m_verticalStreets.clear();

    int streetsDistance = 200;
    for (int i = 0; i < round(m_mapBoundary.height()/streetsDistance); i++) {
        int random1 = rand() % 100;
        int random2 = rand() % 100;
        QLineF *horizontalLine = new QLineF(0, i*streetsDistance + random1,
                                            m_mapBoundary.right(),
                                            i*streetsDistance + random2);

        int random3 = rand() % 100;
        int random4 = rand() % 100;
        QLineF *verticalLine = new QLineF(i*streetsDistance + random3,
                                          m_mapBoundary.top(),
                                          i*streetsDistance + random4,
                                          m_mapBoundary.bottom());

//        m_scene->addLine(*horizontalLine);
//        m_scene->addLine(*verticalLine);

        m_horizontalStreets.push_back(horizontalLine);
        m_verticalStreets.push_back(verticalLine);

    }

    int streetWidth = 30;
    /*
    for (int i = 0; i < round(m_mapBoundary.height()/streetsDistance) - 1; i++) {
        for (int j = 0; j < round(m_mapBoundary.width()/streetsDistance) - 1; j++) {
            QPointF intersectionPoint1;
            m_horizontalStreets.at(j)->intersect(*m_verticalStreets.at(i), &intersectionPoint1);

            QPointF intersectionPoint2;
            m_horizontalStreets.at(j + 1)->intersect(*m_verticalStreets.at(i), &intersectionPoint2);

            QPointF intersectionPoint3;
            m_horizontalStreets.at(j)->intersect(*m_verticalStreets.at(i + 1), &intersectionPoint3);

            QPointF intersectionPoint4;
            m_horizontalStreets.at(j + 1)->intersect(*m_verticalStreets.at(i + 1), &intersectionPoint4);



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

            MathematicalProduct *building = m_buildingFactory->createMathematicalProduct(buildingForm);

            m_products.push_back(building);


//            m_scene->addPolygon(buildingForm);

        }

    }*/
    addCars();
    //addTrees();
}

void MapGenerator::addCars()
{
    QPointF carPosition;

    int numberOfCars = 0;       // For test

    for (unsigned i = 0; i < m_horizontalStreets.size(); i++) {
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

//        cout <<"First point: "<< normal.p2().x()<< ", "<< normal.p2().y() <<endl;

        normal.translate(normal.p1() - normal.p2());

        carContour << normal.p1();

//        cout <<"2 point: "<< normal.p1().x()<< ", "<< normal.p1().y() <<endl;

        normal.translate(tmpLine.p2() - tmpLine.p1());

        carContour << normal.p1();

//        cout <<"3 point: "<< normal.p1().x()<< ", "<< normal.p1().y() <<endl;

        normal.translate(normal.p2() - normal.p1());

        carContour << normal.p2();

//        cout <<"4t: "<< normal.p2().x()<< ", "<< normal.p2().y() <<endl;

        carContour<< carContour.at(0);

//        cout <<"4: "<< normal.p2().x()<< ", "<< normal.p2().y() <<endl;

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
        m_cars.push_back((MathematicalCarProduct *)car);
        ((MathematicalCarProduct *)car)->setRoad(line);

        thread *thread_obj = new thread (&MapGenerator::moveCar,
                                        ref(*(MathematicalCarProduct*)car),
                                        ref(*m_horizontalStreets.at(i)));

        numberOfCars+=1;

    }

    for (unsigned j = 0; j < m_verticalStreets.size(); j++) {
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

//        MathematicalProduct *car = m_carFactory->createMathematicalProduct(carPosition.x(),
//                                                                           carPosition.y());

        MathematicalProduct *car = m_carFactory->createMathematicalProduct(carPosition.x(),
                                                                           carPosition.y(),
                                                                           carContour,
                                                                           true);

        dynamic_cast<MathematicalCarProduct *>(car)->setMovement(tmpLine);

        m_products.push_back(car);
        m_cars.push_back((MathematicalCarProduct *) car);
        ((MathematicalCarProduct *) car)->setRoad(line);

        thread *thread_obj = new thread (&MapGenerator::moveCar,
                                        ref(*(MathematicalCarProduct*)car),
                                        ref(*m_verticalStreets.at(j)));
        numberOfCars+=1;
//        thread_obj->join();
//        thread_obj->detach();

    }
    cout<< "Number of horizontal and vertical streets: "<< (m_horizontalStreets.size() + m_verticalStreets.size() )<<endl;
    cout<<"Number of cars: " << numberOfCars << endl;
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


void MapGenerator::moveCar(MathematicalCarProduct &car, QLineF &street)
{
    bool run = true;
    QLineF normal = street.unitVector();

    while (run) {
        if (car.getPosX()>100 && car.getPosX()<4900
            && car.getPosY()>100 && car.getPosY()<4900){

            normal.translate(QPointF(car.getPosX(), car.getPosY()) - normal.p1());
            normal.setLength(10);
            car.setPosX(normal.p2().x());
            car.setPosY(normal.p2().y());
//            car.setPosX(car.getPosX() + 2 * street.dx()/street.length());
//            car.setPosY(car.getPosY() + 2 *street.dy()/street.length());
//            car.newProperties();
        } else {
            run = false;
        }


//        cout<<"Car pos: "<<car.getPosX()<<", "<<car.getPosY()<<endl;

        this_thread::sleep_for(std::chrono::milliseconds(100));
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
