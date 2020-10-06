#include "imagesmethod.h"

struct forImage{
    vector <Wall *> walls;
    const QPolygonF zone;
};


void ImagesMethod::illuminationZones()
{
    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

    setObservers();

    launchAlgorithm();
}


void ImagesMethod::launchAlgorithm()
{

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

    int recursionDepth = reflectionsNumber;

//    for (unsigned i = 0; i < m_receivers.size(); i++) {
//        m_receivers.at(i)->eraseObservers();
//    }

    foreach (Tx *transmitter, m_transmitters) {

        m_currentTx = transmitter;

//        m_currentTransmitterRange = transmitter->getIlluminationZone();
        m_currentTransmitterRange = transmitter->buildCoverage();

//        m_scene->addPolygon(m_currentTransmitterRange, QPen(), illumination1);

        forImage data = transmitterIllumination(transmitter);

//        m_scene->addPolygon(data.zone, QPen(), illumination1);

        m_totalIlluminationZone = m_totalIlluminationZone.united(data.zone.boundingRect());

        // Launches the methods to compute siple and double diffraction

        setDiffraction(data.walls, data.zone, transmitter);
        if (recursionDepth > 0) {
            createImages(data.walls, data.zone, recursionDepth - 1, transmitter);
        }
    }
}

void ImagesMethod::recomputeImages(AbstractAntena */*tx*/)
{
//    clearImages(tx);

    disconnectAllCars();

    clearAllImages();

    launchAlgorithm();

    for (unsigned i = 0; i < m_receivers.size(); i++) {
        m_receivers.at(i)->notifyObservers();
    }
}

void ImagesMethod::setObservers()
{
    foreach (Tx *transmitter, m_transmitters) {
        for (unsigned i = 0; i < m_receivers.size(); i++) {
            m_receivers.at(i)->attachTransmitter(transmitter);
            transmitter->attachObservable(m_receivers.at(i));
        }

        connectToCars(transmitter);

        connect(transmitter, &AbstractAntena::detectsCar,
                this, &ImagesMethod::recomputeImages,
                Qt::QueuedConnection);
    }
}


void ImagesMethod::connectToCars(AbstractAntena *ant)
{
    for (unsigned i = 0; i < m_cars.size(); i++) {
        connect(m_cars.at(i), &MathematicalCarProduct::positionChanged,
                ant, &AbstractAntena::carMoved, Qt::QueuedConnection);
    }
}


void ImagesMethod::disconnectCars(AbstractAntena *ant)
{
    for (unsigned i = 0; i < m_cars.size(); i++) {
        disconnect(m_cars.at(i), &MathematicalCarProduct::positionChanged,
                   ant, &AbstractAntena::carMoved);
    }
}


void ImagesMethod::disconnectAllCars()
{
    for (unsigned i = 0; i < m_transmitters.size(); i++) {
        for (unsigned j = 0; j < m_images[m_transmitters.at(i)].size(); j++) {
            disconnectCars(m_images[m_transmitters.at(i)].at(j));
        }
    }
}


void ImagesMethod::clearImages(Tx *tx)
{
    for (unsigned i = 0; i< m_images[tx].size(); i++) {
        delete m_images[tx].at(i);
    }
}


void ImagesMethod::clearAllImages()
{
//    unsigned s = m_transmitters.size();

    for (unsigned i = 0; i < m_transmitters.size(); i++) {

//        unsigned s2 = m_images[m_transmitters.at(i)].size();

        for (unsigned j = 0; j < m_images[m_transmitters.at(i)].size(); j++){

            delete m_images[m_transmitters.at(i)].at(j);

        }
        m_images[m_transmitters.at(i)].clear();
//        m_images[m_transmitters.at(i)].erase(m_images[m_transmitters.at(i)].begin(),
//                                             m_images[m_transmitters.at(i)].end());
//        m_images[m_transmitters.at(i)].shrink_to_fit();
    }

    for (unsigned i = 0; i < m_receivers.size(); i++) {
        m_receiver->clearObeservers();
    }
}


void ImagesMethod::setDiffraction(vector<Wall *> walls, const QPolygonF &zone, AbstractAntena *parent)
{
    //     walls : walls illuminated by the antena
    //     zone : antenas illumination zone
    //     parent : contains walls and zone

    vector <Line> illuminatedWalls;
    vector <Wall *> usedWalls;

    for (int i = 1; i < zone.length() - 1 ; i++) {

        //      Here we go thorough the sides of the illumination zone and check if they are a part of a wall
        //      If yes, then the part is used to build the diffraction image of the transmitter.

        unsigned j = 0;
        bool cont = true;
        while (j < walls.size() && cont) {
            if (walls.at(j)->onLine(zone.at(i)) && walls.at(j)->onLine(zone.at(i+1))) {
                /*
                 * Two consecutives points of the coverage polygone are on the same wall.
                 */
                illuminatedWalls.push_back(Line(zone.at(i), zone.at(i+1)));
                usedWalls.push_back(walls.at(j));
                walls.erase(walls.begin() + j);
                cont = false;
            }
            j++;
        }
    }
    buildDiffractionPoints(zone, usedWalls, 0, parent);
}


void ImagesMethod::buildDiffractionPoints(const QPolygonF &zone, vector<Wall *> illuminatedWalls,
                                          int nbReflections, AbstractAntena *parent)
{

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

    QColor illumination2;
    illumination2.setGreen(100);
    illumination2.setBlue(100);
    illumination2.setAlpha(100);

    QPen redPen(Qt::red);
    redPen.setWidth(3);
    QPen bluePen(Qt::blue);
    bluePen.setWidth(3);
    QPen greenPen(Qt::green);
    greenPen.setWidth(3);

//    m_scene->addEllipse(zone.at(0).x(),zone.at(0).y(),5,5,redPen);
//    m_scene->addPolygon(zone,illumination2);

    Building *cornersBuilding = nullptr;

    for(int i = 0; i < zone.length() - 1; i++){
        const QPointF *cornerP = nullptr;
        QPointF p2;
        QPointF p1;
        unsigned j = 0;
        bool cond = true;
        while (j < illuminatedWalls.size() && cond) {
            if (zone.at(i) == illuminatedWalls.at(j)->p1()
                || zone.at(i) == illuminatedWalls.at(j)->p2()) {

                //
                //  The illumination zone corner is an extremity of one illuminated wall.
                //

                //               -------
                //              |       |
                //              |       |
                //              |       |
                //               ---p1--        Rx

                //              c ----- p2
                //              |       |
                //      Tx      |       |
                //              |       |
                //               -------


                if (cornerP == nullptr) {

                    //Perpendicular wall to the one illuminated
                    p2 = illuminatedWalls.at(j)->getBuilding()->forDiffraction(illuminatedWalls.at(j), zone.at(i));

                    cornersBuilding = illuminatedWalls.at(j)->getBuilding();
//                    m_scene->addEllipse(p2.x(), p2.y(), 10, 10, greenPen);

                    cond = false;
                    cornerP = &zone.at(i);
                    if (illuminatedWalls.at(j)->onLine(zone.at(i+1)) && zone.at(i-1) != p2) {

                        //  Looking for the neighouring illuminatioin zone corner which doesn't lie
                        //  on the same illuminated wall.
                        //  It will be used to build the illumination zone of the diffraction point.

                        p1 = zone.at(i-1);

                    } else {
                        p1 = zone.at(i+1);
                    }

                } else {
                    cond = false;
                }
            }
            j++;
        }

        //QPolygonF zoneCorn = buildIlluminationZone(zone.at(i));
        if (!cond) {

            AntenaDiffraction *corner = new AntenaDiffraction(zone.at(i), p1, p2, parent);
            corner->setBuilding(cornersBuilding);
            corner->setRayFactory(m_rayFactory);

//            m_scene->addPolygon(corner->getIlluminationZone(),QPen(),illumination1);
            if (p1 == p2) {
//                cout<< "Illumintion zone is a line!"<<endl;
            }

//            m_scene->addPolygon(corner->getIlluminationZone(), QPen(), illumination1);

            QPolygonF cornerZone = buildingsInIlluminationZone(corner, nbReflections);

//            m_scene->addPolygon(corner->getIlluminationZone(), QPen(), illumination2);

//            m_scene->addEllipse(zone.at(i).x(),zone.at(i).y(),5,5,redPen);              // RED for diffraction
            if (cornerZone.length() < 3) {
                delete corner;
                continue;
            } else {
//                for (unsigned int numberReceivers = 0; numberReceivers < m_receivers.size(); numberReceivers++) {
//                    m_receivers.at(numberReceivers)->attachObserver(corner);
////                    m_scene->addPolygon(corner->getIlluminationZone(), QPen(), illumination1);
//                }

                connectToCars(corner);
                m_images[m_currentTx].push_back(corner);
                m_currentTx->addTxImg(corner);

            }

            for (unsigned int i = 0; i < m_buildings.size(); i++) {
                QPolygonF build(*m_buildings.at(i));
                if (build.intersects(cornerZone)) {
                    QLineF line;
                    int k =0;
                    bool foundCorner = false;
                    while (k < cornerZone.size() && !foundCorner) {
                        foundCorner = (cornerZone.at(k) == *corner);
                        if (foundCorner) {
                            QLineF lineDraw(cornerZone.at(k), cornerZone.at((k+1) % (cornerZone.size())));
                            line = lineDraw;
                        }
                        k++;
                    }

//                    QLineF line(cornerZone.at(0),cornerZone.at(1));         // There si an error here

//                    cout<<"Illumination zone at(0) = pos: "<< (cornerZone.at(0) == corner->getPosition()) <<endl;

//                    if(cornerZone.at(0) == corner->getPosition()){
//                        QLineF lineDraw(cornerZone.at(0),cornerZone.at(1));
//                        m_scene->addLine(lineDraw,redPen);
//                    }
//                    else{
//                        QLineF lineDraw(cornerZone.at(0),cornerZone.at(cornerZone.size()-1));
//                        m_scene->addLine(lineDraw,redPen);
//                    }

                    //QLineF lineDraw(cornerZone.at(0),cornerZone.at(1));         // for drawing

                    //m_scene->addLine(line,redPen);


//                    Wall* wall = nullptr;
//                    if(m_buildings.at(i)->adjacentWall(line, wall)){

//                        //cout<<"Adjacent!"<<endl;
////                        m_scene->addLine(*wall,redPen);

//                        /*
//                         * A building has an adjacent wall to the illumination zone of the diffraction point.
//                         */
//                        QPointF pos(wall->farestExtrem(cornerZone.at(k-1)));

//                        QPointF p2 = m_buildings.at(i)->forDiffraction(wall,pos);
////                        m_scene->addEllipse(p2.x(),p2.y(),10,10,redPen);                                  // RED for diffraction
////                        m_scene->addEllipse(pos.x(),pos.y(),10,10,bluePen);                               // BLUE farest extremity
////                        m_scene->addEllipse(cornerZone.at(1).x(),cornerZone.at(1).y(),10,10,greenPen);    // GREEN corner zone
//                        AntenaDiffraction *corner2 = new AntenaDiffraction(pos, cornerZone.at(1),p2, corner);
//                        corner2->setRayFactory(m_rayFactory);
////                        m_receiver->attachObserver(corner2);
//                        for(int numberReceivers =0;numberReceivers<m_receivers.size();numberReceivers++){
//                            m_receivers.at(numberReceivers)->attachObserver(corner2);
//                        }

//                        //m_scene->addPolygon(corner2->getIlluminationZone(),QPen(),illumination2);

//                        QPolygonF cornerZone = buildingsInIlluminationZone(corner2,nbReflections);

//                        //m_scene->addPolygon(cornerZone,QPen(),illumination2);       // Illumination zone for second diffraction
//                    }
                }
            }
        }
    }
}


forImage ImagesMethod::transmitterIllumination(Tx *transmitter)
{

    // Painting tools
    QColor illumination;
    illumination.setBlue(255);
    illumination.setAlpha(100);

    QColor illumination2;
    illumination2.setRed(255);
    illumination2.setAlpha(50);

    QPolygonF illuminationZone = transmitter->buildCoverage();
    vector <Wall *> nearestWalls;		// Vector containing the nearest walls to the transmitter of every building.

    foreach (Building *building, m_buildings) {
        QPolygonF p_building(*building);

        if (p_building.intersects(illuminationZone)) {
//            illuminatedBuldings.push_back(building);
            illuminationZone = illuminationZone.subtracted(building->shadow(transmitter->getPosition()));

//            m_scene->addPolygon(building->shadow(transmitter->getPosition()),QPen(),illumination2);

            // Closest point of the building to the transmitter
            QPointF corner = building->closestPoint(transmitter->getPosition());

            // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(0));
            nearestWalls.push_back(building->nearestWalls(corner).at(1));
        }
    }

    transmitter->setIlluminatedZone(illuminationZone);
    //m_scene->addPolygon(illuminationZone,QPen(),illumination);

    forImage result{nearestWalls, illuminationZone};

    return result;
}

QPolygonF ImagesMethod::buildIlluminationZone(AbstractAntena *ant)
{
    // Painting tools
    QColor illumination;
    illumination.setBlue(255);
    illumination.setAlpha(100);
    QColor illumination2;
    illumination2.setRed(255);
    illumination2.setAlpha(50);

    //vector <Building*> illuminatedBuldings; // Buildings lying in the initial illumination zone.
//    QPolygonF illuminationZone = Transmitter->getIluminationZone(itemsBoundingRect());
    QPolygonF illuminationZone = ant->getIlluminationZone();
    //addPolygon(illuminationZone,QPen(),illumination2);
    vector <Wall*> nearestWalls;

    foreach (Building *building, m_buildings){
        QPolygonF p_building(*building);

        if (p_building.intersects(illuminationZone) && building != ant->getBuilding()) {
            //illuminatedBuldings.push_back(building);

            //addPolygon(building->shadow(ant->getPosition()),QPen(),illumination2);

            illuminationZone = illuminationZone.subtracted(building->shadow(ant->getPosition()));

            // Closest point of the building to the transmitter
            QPointF corner = building->closestPoint(ant->getPosition());

            // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(0));
            nearestWalls.push_back(building->nearestWalls(corner).at(1));
//            addPolygon(intitIlluminationZone,QPen(),illumination);
        }
    }

    return illuminationZone;
}


QPolygonF ImagesMethod::buildingsInIlluminationZone(AbstractAntena *ant, int nbReflections)
{
    // Painting tools
    QColor illumination;
    illumination.setBlue(255);
    illumination.setAlpha(100);
    QColor illumination2;
    illumination2.setRed(255);
    illumination2.setAlpha(50);

    int recursionDepth = nbReflections;

    //vector <Building*> illuminatedBuldings; // Buildings lying in the initial illumination zone.

    QPolygonF illuminationZone = ant->getIlluminationZone();


//    m_scene->addPolygon(illuminationZone,QPen(),illumination2);
    vector <Wall *> nearestWalls;

    foreach (Building *building, m_buildings) {
        QPolygonF p_building(*building);

        if (p_building.intersects(illuminationZone) && building != ant->getBuilding()) {
            //illuminatedBuldings.push_back(building);

//            m_scene->addPolygon(building->shadow(ant->getPosition()),QPen(),illumination2);

            illuminationZone = illuminationZone.subtracted(building->shadow(ant->getPosition()));

            // Closest point of the building to the transmitter
            QPointF corner = building->closestPoint(ant->getPosition());

            // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(0));
            nearestWalls.push_back(building->nearestWalls(corner).at(1));

        }
    }

    //ant->setIlluminatedZone(illuminationZone.intersected(Transmitter->getIlluminatedZone()));
    illuminationZone = illuminationZone.intersected(m_currentTransmitterRange);
    ant->setIlluminatedZone(illuminationZone);
    m_totalIlluminationZone = m_totalIlluminationZone.united(illuminationZone.boundingRect());

//    m_scene->addPolygon(illuminationZone,QPen(),illumination);

    if (recursionDepth > 0) {
        createImages(nearestWalls, illuminationZone, recursionDepth - 1, ant);
    }
    return illuminationZone;
}


vector <Line> ImagesMethod::createImages(vector<Wall *> walls, const QPolygonF zone,
                                        int nbReflections, AbstractAntena *parent)
{
    vector <Line> illuminatedWalls;
    vector <Wall*> usedWalls;

    QPen redPen(Qt::red);
    redPen.setWidth(3);

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

    vector <TxImg *> images; // vector for tests

    for (int i = 1; i < zone.length() - 1; i++) {

        //
        //      Here we go thorough the sides of the illumination zone and check if
        //      they are a part of a wall
        //      If yes, then the part is used to build the image of the transmitter.
        //

        unsigned int j = 0;
        bool cont = true;
//        bool contDiffraction = true;
        while (j < walls.size() && cont) {
            if (walls.at(j)->onLine(zone.at(i)) && walls.at(j)->onLine(zone.at(i+1))) {
                illuminatedWalls.push_back(Line(zone.at(i), zone.at(i+1)));
                usedWalls.push_back(walls.at(j));

                //addLine(Line(zone.at(i),zone.at(i+1)),redPen);

                //Creation of the trasmitter image
                TxImg *image = new TxImg(Line(zone.at(i), zone.at(i+1)),
                                                               parent,
                                                               walls.at(j)->getEpsilon());

                m_images[m_currentTx].push_back(image);
                m_currentTx->addTxImg(image);

//                m_scene->addEllipse(image->getPosition().x(), image->getPosition().y(), 5, 5, redPen);

                connectToCars(image);

                image->setBuilding(walls.at(j)->getBuilding());

                if (walls.at(j)->getWallType() != Wall::wall) {
                    image->setWallType(walls.at(j)->getWallType());
                    image->setMovement(walls.at(j)->movement());
                }

                image->setRayFactory(m_rayFactory);
//                m_receiver->attachObserver(image);
//                for (unsigned int numberReceivers = 0;
//                     numberReceivers < m_receivers.size();
//                     numberReceivers++) {

//                    m_receivers.at(numberReceivers)->attachObserver(image);
//                }

                images.push_back(image);

                //QPolygonF imagesZone = zone.intersected(image->getIlluminationZone());

                QPolygonF imagesZone = buildingsInIlluminationZone(image, nbReflections);

                //usedWalls.push_back(walls.at(j));
                walls.erase(walls.begin() + j);
                cont = false;
            }
                j++;
        }
    }
    //buildDiffractionPoints(zone,usedWalls,nbReflections,parent);  // Uncomment for diffraction + relfection
    return  illuminatedWalls;
}


void ImagesMethod::connectTxsCars()
{
//    for (unsigned i = 0; i < images) {

//    }
}
