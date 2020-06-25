#include "imagesmethod.h"


//void ImagesMethod::createImages(){
//    int recursionDepth = reflectionsNumber;

//    foreach(antena* transmitter,m_transmitters){
//        m_receiver->addAntenaImage(transmitter);
//        transmitter->setReceiver(m_receiver);
//        forImage data = transmitterIllumination(transmitter);
//        if(recursionDepth > 0){
//                illuminatedWalls(data.walls,data.zone,recursionDepth -1 ,transmitter);
//        }
//    }
////    buildingsInIlluminationZone(Transmitter, recursionDepth);

//}

//struct forImage{
//    vector <Wall*> walls;
//    const QPolygonF zone;
//};

////QPolygonF room::transmitterIllumination(){
//forImage ImagesMethod::transmitterIllumination(antena *transmitter){

//    // Painting tools
//    QColor illumination;
//    illumination.setBlue(255);
//    illumination.setAlpha(100);


//    vector <Building*> illuminatedBuldings; // Buildings lying in the initial illumination zone.
////    QPolygonF illuminationZone = Transmitter->getIluminationZone(itemsBoundingRect());
//    QPolygonF illuminationZone = transmitter->getIlluminationZone();
//    vector <Wall*> nearestWalls;		// Vector containing the nearest walls to the transmitter of every building.

//    foreach(MathematicalBuildingProduct *building, m_buildings){
//        QPolygonF p_building(*building);

//        if(p_building.intersects(illuminationZone)){
//            illuminatedBuldings.push_back(building);
//            illuminationZone = illuminationZone.subtracted(building->shadow(transmitter->getPosition()));
//            QPointF corner = building->closestPoint(transmitter->getPosition()); // Closest point of the building to the transmitter
//            nearestWalls.push_back(building->nearestWalls(corner).at(0));   // Add the 2 walls that are at the corner.
//            nearestWalls.push_back(building->nearestWalls(corner).at(1));

//        }
//    }
//    transmitter->setIlluminatedZone(illuminationZone);

//    forImage result{nearestWalls,illuminationZone};

//    return result;
//}


//QPolygonF ImagesMethod::buildingsInIlluminationZone(AbstractAntena *ant, int nbReflections)
////vector <Building*> room::buildingsInIlluminationZone(int nbReflections)
//{
//    int recursionDepth = nbReflections;

//    //vector <Building*> illuminatedBuldings; // Buildings lying in the initial illumination zone.
////    QPolygonF illuminationZone = Transmitter->getIluminationZone(itemsBoundingRect());
//    QPolygonF illuminationZone = ant->getIlluminationZone();
//    vector <Wall*> nearestWalls;

//    foreach(Building *building, m_buildings){
//        QPolygonF p_building(*building);

//        if(p_building.intersects(illuminationZone) && building != ant->getBuilding()){
//            //illuminatedBuldings.push_back(building);

//            illuminationZone = illuminationZone.subtracted(building->shadow(ant->getPosition()));
//            QPointF corner = building->closestPoint(ant->getPosition()); // Closest point of the building to the transmitter
//            nearestWalls.push_back(building->nearestWalls(corner).at(0));   // Add the 2 walls that are at the corner.
//            nearestWalls.push_back(building->nearestWalls(corner).at(1));
//        }
//    }
//    //ant->setIlluminatedZone(illuminationZone.intersected(Transmitter->getIlluminatedZone()));
//    ant->setIlluminatedZone(illuminationZone);

//    if(recursionDepth > 0){
//        illuminatedWalls(nearestWalls,illuminationZone, recursionDepth -1,ant);
//    }
//    return illuminationZone;
//}

//vector <Line> ImagesMethod::illuminatedWalls(vector <Wall*> walls, const QPolygonF zone, int nbReflections, AbstractAntena *parent){
//    vector <Line> illuminatedWalls;
//    vector <Wall*> usedWalls;


//    vector <AntenaImage *> images; // vector for tests

//    for(int i=1; i <  zone.length()-1 ;i++){

//        /*
//         * Here we go thorough the sides of the illumination zone and check if they are a part of a wall
//         * If yes, then the part is used to build the image of the transmitter.
//         */

//        int j =0;
//        bool cont = true;
//        bool contDiffraction = true;
//        while(j<walls.size() && cont){
//            if(walls.at(j)->onLine(zone.at(i)) && walls.at(j)->onLine(zone.at(i+1))){
//                illuminatedWalls.push_back(Line(zone.at(i),zone.at(i+1)));
//                usedWalls.push_back(walls.at(j));

//                //Creation of the trasmitter image
//                AntenaImage *image = new AntenaImage(Line(zone.at(i),zone.at(i+1)),parent);
//                image->setBuilding(walls.at(j)->getBuilding());
//                image->setSceneBoundary(itemsBoundingRect());
//                m_receiver->addAntenaImage(image);
//                images.push_back(image);

//                //QPolygonF imagesZone = zone.intersected(image->getIlluminationZone());

//                QPolygonF imagesZone = buildingsInIlluminationZone(image,nbReflections);

//        /*
//         * Creation of diffracted points. Since it's done here it won't work for the case without
//         * any reflections.
//         */

//                //usedWalls.push_back(walls.at(j));
//                walls.erase(walls.begin()+j);
//                cont = false;
//            }
//                j++;
//            }

//        }

//        buildDiffractionPoints(zone,usedWalls,nbReflections,parent);




//    return  illuminatedWalls;
//}
