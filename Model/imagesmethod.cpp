#include "imagesmethod.h"

struct forImage{
    vector <Wall*> walls;
    const QPolygonF zone;
};

void ImagesMethod::createImages(){
    int recursionDepth = reflectionsNumber;

    //cout<<"In createImages"<<endl;

    foreach(MathematicalTransmitterProduct* transmitter,m_transmitters){
        m_receiver->attachObserver(transmitter);
        transmitter->attachObservable(m_receiver);
        forImage data = transmitterIllumination(transmitter);
        if(recursionDepth > 0){
                illuminatedWalls(data.walls,data.zone,recursionDepth -1 ,transmitter);
        }
    }
//    buildingsInIlluminationZone(Transmitter, recursionDepth);

}


//QPolygonF room::transmitterIllumination(){
forImage ImagesMethod::transmitterIllumination(MathematicalTransmitterProduct *transmitter){

    vector <MathematicalBuildingProduct*> illuminatedBuldings; // Buildings lying in the initial illumination zone.
//    QPolygonF illuminationZone = Transmitter->getIluminationZone(itemsBoundingRect());
    QPolygonF illuminationZone = transmitter->getIlluminationZone();
    vector <Wall*> nearestWalls;		// Vector containing the nearest walls to the transmitter of every building.

    foreach(MathematicalBuildingProduct *building, m_buildings){
        QPolygonF p_building(*building);

//        for(int i =0; i<p_building.size();i++){
//            cout<<p_building.at(i).x()<<", "<<p_building.at(i).y()<<endl;
//        }

        if(p_building.intersects(illuminationZone)){
            illuminatedBuldings.push_back(building);
            illuminationZone = illuminationZone.subtracted(building->shadow(transmitter->getPosition()));



//            for(int i =0; i<illuminationZone.size();i++){
//                cout<<illuminationZone.at(i).x()<<", "<<illuminationZone.at(i).y()<<endl;
//            }

            QPointF corner = building->closestPoint(transmitter->getPosition()); // Closest point of the building to the transmitter
            nearestWalls.push_back(building->nearestWalls(corner).at(0));   // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(1));
        }
    }
    transmitter->setIlluminatedZone(illuminationZone);

    forImage result{nearestWalls,illuminationZone};

    return result;
}


QPolygonF ImagesMethod::buildingsInIlluminationZone(AbstractAntena *ant, int nbReflections)
{
    int recursionDepth = nbReflections;


    QColor illumination;
    illumination.setBlue(255);
    illumination.setAlpha(100);
    QColor illumination2;
    illumination2.setRed(255);
    illumination2.setAlpha(50);


    QPolygonF illuminationZone = ant->getIlluminationZone();
    vector <Wall*> nearestWalls;

    foreach(MathematicalBuildingProduct *building, m_buildings){
        QPolygonF p_building(*building);

        if(p_building.intersects(illuminationZone) && building != ant->getBuilding()){

            //m_scene->addPolygon(illuminationZone,QPen(),illumination2);

            illuminationZone = illuminationZone.subtracted(building->shadow(ant->getPosition()));

            //m_scene->addPolygon(building->shadow(ant->getPosition()),QPen(),illumination2);

            QPointF corner = building->closestPoint(ant->getPosition()); // Closest point of the building to the transmitter
            nearestWalls.push_back(building->nearestWalls(corner).at(0));   // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(1));
        }
    }
    ant->setIlluminatedZone(illuminationZone);
    //m_scene->addPolygon(illuminationZone,QPen(),illumination2);

    if(recursionDepth > 0){
        illuminatedWalls(nearestWalls,illuminationZone, recursionDepth -1,ant);
    }
    return illuminationZone;
}

vector <Line> ImagesMethod::illuminatedWalls(vector <Wall*> walls, const QPolygonF zone, int nbReflections, AbstractAntena *parent){
    vector <Line> illuminatedWalls;
    vector <Wall*> usedWalls;

    //cout<<"Number of illuminated walls: "<< walls.size()<<endl;

    QColor illumination2;
    illumination2.setRed(255);
    illumination2.setAlpha(50);

    vector <TransmitterImage *> images; // vector for tests

    //m_scene->addPolygon(zone,QPen(),illumination2);
    for(int i=1; i <  zone.length()-1 ;i++){

        /*
         * Here we go thorough the sides of the illumination zone and check if they are a part of a wall
         * If yes, then the part is used to build the image of the transmitter.
         */

        int j =0;
        bool cont = true;
        //bool contDiffraction = true;
        while(j<walls.size() && cont){


            if(walls.at(j)->onLine(zone.at(i)) && walls.at(j)->onLine(zone.at(i+1))){
                illuminatedWalls.push_back(Line(zone.at(i),zone.at(i+1)));
                usedWalls.push_back(walls.at(j));

                //Creation of the trasmitter image
                TransmitterImage *image = new TransmitterImage(Line(zone.at(i),zone.at(i+1)),parent);
                image->setBuilding(walls.at(j)->getBuilding());
                image->setRayFactory(m_rayFactory);
                //m_scene->addEllipse(image->x(),image->y(),5,5);

                //image->setSceneBoundary(itemsBoundingRect());

                m_receiver->attachObserver(image);
                images.push_back(image);
                //cout<<"I did it again!"<< j<<endl;

                //QPolygonF imagesZone = zone.intersected(image->getIlluminationZone());

                QPolygonF imagesZone = buildingsInIlluminationZone(image,nbReflections);

        /*
         * Creation of diffracted points. Since it's done here it won't work for the case without
         * any reflections.
         */

                //usedWalls.push_back(walls.at(j));
                walls.erase(walls.begin()+j);
                cont = false;
            }
            j++;
        }

    }

        buildDiffractionPoints(zone,usedWalls,nbReflections,parent);

    return  illuminatedWalls;
}

void ImagesMethod::buildDiffractionPoints(const QPolygonF &zone, vector<Wall *> illuminatedWalls, int nbReflections, AbstractAntena *parent){

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

    for(int i = 0;i<zone.length()-1;i++){
        const QPointF *corner = nullptr;
        QPointF p2;
        QPointF p1;
        int j = 0;
        bool cond = true;
        while(j<illuminatedWalls.size() && cond){
            if(zone.at(i) == illuminatedWalls.at(j)->p1()||zone.at(i) == illuminatedWalls.at(j)->p2()){
                if(corner == nullptr){
                    corner = &zone.at(i);
                    if(illuminatedWalls.at(j)->onLine(zone.at(i+1))){
                        p1 = zone.at(i-1);
                    }else{p1 = zone.at(i+1);}

                    p2 = illuminatedWalls.at(j)->getBuilding()->forDiffraction(illuminatedWalls.at(j),zone.at(i));
                }
                else{
                    cond = false;
                }
            }

            j++;
        }

        if(cond){

            AntenaDiffraction *corner = new AntenaDiffraction(zone.at(i), p1,p2, parent,QRectF(0,0,5000,5000));
            corner->setRayFactory(m_rayFactory);
            m_receiver->attachObserver(corner);
            QPolygonF cornerZone = buildingsInIlluminationZone(corner,nbReflections);
            //addPolygon(cornerZone,QPen(),illumination1);
        }
    }
}
