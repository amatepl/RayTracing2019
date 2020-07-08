#include "imagesmethod.h"

struct forImage{
    vector <Wall*> walls;
    const QPolygonF zone;
};


void ImagesMethod::illuminationZones(){
    int recursionDepth = reflectionsNumber;

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

    foreach(MathematicalTransmitterProduct* transmitter,m_transmitters){
        for(int i=0;i<m_receivers.size();i++){
            m_receivers.at(i)->attachObserver(transmitter);
            transmitter->attachObservable(m_receivers.at(i));
        }
//        m_receiver->attachObserver(transmitter);
        transmitter->attachObservable(m_receiver);
        forImage data = transmitterIllumination(transmitter);

        m_totalIlluminationZone = m_totalIlluminationZone.united(data.zone.boundingRect());
//        m_scene->addPolygon(data.zone,QPen(),illumination1);

        setDiffraction(data.walls,data.zone,transmitter);       // Launches the methods to compute siple and double diffraction
        if(recursionDepth > 0){
                createImages(data.walls,data.zone,recursionDepth -1 ,transmitter);
        }
    }
//    buildingsInIlluminationZone(Transmitter, recursionDepth);



//    m_scene->addPolygon(m_totalIlluminationZone,QPen(),illumination1);


}


void ImagesMethod::setDiffraction(vector<Wall *> walls,const QPolygonF &zone, AbstractAntena *parent){
    /*
     * walls : walls illuminated by the antena
     * zone : antenas illumination zone
     * parent : contains walls and zone
     */

    vector <Line> illuminatedWalls;
    vector <Wall*> usedWalls;

    for(int i=1; i <  zone.length()-1 ;i++){

        /*
         * Here we go thorough the sides of the illumination zone and check if they are a part of a wall
         * If yes, then the part is used to build the diffraction image of the transmitter.
         */

        int j =0;
        bool cont = true;
        while(j<walls.size() && cont){
            if(walls.at(j)->onLine(zone.at(i)) && walls.at(j)->onLine(zone.at(i+1))){
                /*
                 * Two consecutives points of the coverage polygone are on the same wall.
                 */
                illuminatedWalls.push_back(Line(zone.at(i),zone.at(i+1)));
                usedWalls.push_back(walls.at(j));
                walls.erase(walls.begin()+j);
                cont = false;
            }
            j++;
        }
    }
    buildDiffractionPoints(zone,usedWalls,0,parent);
}

void ImagesMethod::buildDiffractionPoints(const QPolygonF &zone, vector<Wall *> illuminatedWalls, int nbReflections, AbstractAntena *parent){

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

    for(int i = 0;i<zone.length()-1;i++){
        const QPointF *cornerP = nullptr;
        QPointF p2;
        QPointF p1;
        int j = 0;
        bool cond = true;
        while(j<illuminatedWalls.size() && cond){
            if(zone.at(i) == illuminatedWalls.at(j)->p1()||zone.at(i) == illuminatedWalls.at(j)->p2()){
                /*
                 * The illumination zone corner is an extremity of one illuminated wall.
                 */
                if(cornerP == nullptr){
                    p2 = illuminatedWalls.at(j)->getBuilding()->forDiffraction(illuminatedWalls.at(j),zone.at(i)); //Perpendicular wall to the one illuminated
//                    m_scene->addEllipse(p2.x(),p2.y(),10,10,greenPen);

                    cond = false;
                    cornerP = &zone.at(i);
                    if(illuminatedWalls.at(j)->onLine(zone.at(i+1)) && zone.at(i-1) != p2){
                        /*
                         * Looking for the neighouring illuminatioin zone corner which doesn't lie on the same illuminated wall.
                         * It will be used to build the illumination zone of the diffraction point.
                         */
                        p1 = zone.at(i-1);
//                        m_scene->addEllipse(p1.x(),p1.y(),5,5,bluePen);
                    }else{
                        p1 = zone.at(i+1);
//                        m_scene->addEllipse(p1.x(),p1.y(),5,5,redPen);
                    }


                }
                else{
                    cond = false;
                }
            }
            j++;
        }

        //QPolygonF zoneCorn = buildIlluminationZone(zone.at(i));
        if(!cond){
            AntenaDiffraction *corner = new AntenaDiffraction(zone.at(i), p1,p2, parent);
            corner->setRayFactory(m_rayFactory);
            //m_scene->addPolygon(corner->getIlluminationZone(),QPen(),illumination1);
            if(p1==p2){
//                cout<< "Illumintion zone is a line!"<<endl;
            }

            QPolygonF cornerZone = buildingsInIlluminationZone(corner,nbReflections);

//            if(cornerZone.length()>0){
//                cout<<"Illumination zone at(0) = pos: "<< (cornerZone.at(0) == corner->getPosition()) <<endl;
//                cout<<"Positions: "<<cornerZone.at(0).x()<<", "<<cornerZone.at(0).y()<<" and "<<corner->getPosition().x()<<", "<<corner->getPosition().y()<<endl;
//            }

//            m_scene->addEllipse(zone.at(i).x(),zone.at(i).y(),5,5,redPen);                                  // RED for diffraction
            if(cornerZone.length() < 3){
                delete corner;
                continue;
            }
            else{
                for(int numberReceivers =0;numberReceivers<m_receivers.size();numberReceivers++){
                    m_receivers.at(numberReceivers)->attachObserver(corner);
                }
//                m_receiver->attachObserver(corner);
//                m_scene->addPolygon(cornerZone,QPen(),illumination1);         // Illumination zone for first diffraction
                //m_scene->addEllipse(cornerZone.at(0).x(),cornerZone.at(0).y(),10,10,redPen);

                //QLineF line(cornerZone.at(0),cornerZone.at(1));
                //m_scene->addLine(line,redPen);
            }

            for(int i=0; i<m_buildings.size();i++){
                QPolygonF build(*m_buildings.at(i));
                if(build.intersects(cornerZone)){


                    QLineF line;
                    int k =0;
                    bool foundCorner = false;
                    while(k<cornerZone.size() && !foundCorner){
                        foundCorner = (cornerZone.at(k)==*corner);
                        if(foundCorner){
                            QLineF lineDraw(cornerZone.at(k),cornerZone.at((k+1)%(cornerZone.size())));
                            line = lineDraw;
                            //m_scene->addLine(lineDraw, redPen);
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


                    Wall* wall = nullptr;
                    if(m_buildings.at(i)->adjacentWall(line, wall)){

                        //cout<<"Adjacent!"<<endl;
//                        m_scene->addLine(*wall,redPen);

                        /*
                         * A building has an adjacent wall to the illumination zone of the diffraction point.
                         */
                        QPointF pos(wall->farestExtrem(cornerZone.at(k-1)));

                        QPointF p2 = m_buildings.at(i)->forDiffraction(wall,pos);
//                        m_scene->addEllipse(p2.x(),p2.y(),10,10,redPen);                                  // RED for diffraction
//                        m_scene->addEllipse(pos.x(),pos.y(),10,10,bluePen);                               // BLUE farest extremity
//                        m_scene->addEllipse(cornerZone.at(1).x(),cornerZone.at(1).y(),10,10,greenPen);    // GREEN corner zone
                        AntenaDiffraction *corner2 = new AntenaDiffraction(pos, cornerZone.at(1),p2, corner);
                        corner2->setRayFactory(m_rayFactory);
//                        m_receiver->attachObserver(corner2);
                        for(int numberReceivers =0;numberReceivers<m_receivers.size();numberReceivers++){
                            m_receivers.at(numberReceivers)->attachObserver(corner2);
                        }

                        //m_scene->addPolygon(corner2->getIlluminationZone(),QPen(),illumination2);

                        QPolygonF cornerZone = buildingsInIlluminationZone(corner2,nbReflections);

                        //m_scene->addPolygon(cornerZone,QPen(),illumination2);       // Illumination zone for second diffraction
                    }
                }
            }
        }
    }
}

forImage ImagesMethod::transmitterIllumination(MathematicalTransmitterProduct *transmitter){

    // Painting tools
    QColor illumination;
    illumination.setBlue(255);
    illumination.setAlpha(100);


    vector <MathematicalBuildingProduct*> illuminatedBuldings; // Buildings lying in the initial illumination zone.
//    QPolygonF illuminationZone = Transmitter->getIluminationZone(itemsBoundingRect());
    QPolygonF illuminationZone = transmitter->getIlluminationZone();
    vector <Wall*> nearestWalls;		// Vector containing the nearest walls to the transmitter of every building.

    foreach(MathematicalBuildingProduct *building, m_buildings){
        QPolygonF p_building(*building);

        if(p_building.intersects(illuminationZone)){
            illuminatedBuldings.push_back(building);
            illuminationZone = illuminationZone.subtracted(building->shadow(transmitter->getPosition()));
            QPointF corner = building->closestPoint(transmitter->getPosition()); // Closest point of the building to the transmitter
            nearestWalls.push_back(building->nearestWalls(corner).at(0));   // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(1));

        }
    }
    transmitter->setIlluminatedZone(illuminationZone);
    //m_scene->addPolygon(illuminationZone,QPen(),illumination);

    forImage result{nearestWalls,illuminationZone};

    return result;
}

QPolygonF ImagesMethod::buildIlluminationZone(AbstractAntena *ant){

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

    foreach(MathematicalBuildingProduct *building, m_buildings){
        QPolygonF p_building(*building);

        if(p_building.intersects(illuminationZone) && building != ant->getBuilding()){
            //illuminatedBuldings.push_back(building);

            //addPolygon(building->shadow(ant->getPosition()),QPen(),illumination2);

            illuminationZone = illuminationZone.subtracted(building->shadow(ant->getPosition()));
            QPointF corner = building->closestPoint(ant->getPosition()); // Closest point of the building to the transmitter
            nearestWalls.push_back(building->nearestWalls(corner).at(0));   // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(1));
//            addPolygon(intitIlluminationZone,QPen(),illumination);
        }
    }
    return illuminationZone;
}


QPolygonF ImagesMethod::buildingsInIlluminationZone(AbstractAntena *ant, int nbReflections)
//vector <Building*> room::buildingsInIlluminationZone(int nbReflections)
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
//    QPolygonF illuminationZone = Transmitter->getIluminationZone(itemsBoundingRect());

    QPolygonF illuminationZone = ant->getIlluminationZone();


    //m_scene->addPolygon(illuminationZone,QPen(),illumination2);
    vector <Wall*> nearestWalls;

    foreach(MathematicalBuildingProduct *building, m_buildings){
        QPolygonF p_building(*building);

        if(p_building.intersects(illuminationZone) && building != ant->getBuilding()){
            //illuminatedBuldings.push_back(building);

            //addPolygon(building->shadow(ant->getPosition()),QPen(),illumination2);

            illuminationZone = illuminationZone.subtracted(building->shadow(ant->getPosition()));
            QPointF corner = building->closestPoint(ant->getPosition()); // Closest point of the building to the transmitter
            nearestWalls.push_back(building->nearestWalls(corner).at(0));   // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(1));
//            addPolygon(intitIlluminationZone,QPen(),illumination);
        }
    }
    //addPolygon(illuminationZone,QPen(),illumination);
    //ant->setIlluminatedZone(illuminationZone.intersected(Transmitter->getIlluminatedZone()));
    ant->setIlluminatedZone(illuminationZone);
    m_totalIlluminationZone = m_totalIlluminationZone.united(illuminationZone.boundingRect());

//    m_scene->addPolygon(illuminationZone,QPen(),illumination);

    if(recursionDepth > 0){
        createImages(nearestWalls,illuminationZone, recursionDepth -1,ant);
    }
    return illuminationZone;
}

vector <Line> ImagesMethod::createImages(vector<Wall *> walls, const QPolygonF zone, int nbReflections, AbstractAntena *parent) {
    vector <Line> illuminatedWalls;
    vector <Wall*> usedWalls;

    QPen redPen(Qt::red);
    redPen.setWidth(3);

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

    vector <TransmitterImage *> images; // vector for tests

    for(int i=1; i <  zone.length()-1 ;i++){

        /*
         * Here we go thorough the sides of the illumination zone and check if they are a part of a wall
         * If yes, then the part is used to build the image of the transmitter.
         */

        int j =0;
        bool cont = true;
        bool contDiffraction = true;
        while(j<walls.size() && cont){
            if(walls.at(j)->onLine(zone.at(i)) && walls.at(j)->onLine(zone.at(i+1))){
                illuminatedWalls.push_back(Line(zone.at(i),zone.at(i+1)));
                usedWalls.push_back(walls.at(j));

                //addLine(Line(zone.at(i),zone.at(i+1)),redPen);

                //Creation of the trasmitter image
                TransmitterImage *image = new TransmitterImage(Line(zone.at(i),zone.at(i+1)),parent);
                image->setBuilding(walls.at(j)->getBuilding());
                //image->setSceneBoundary(itemsBoundingRect());
                image->setRayFactory(m_rayFactory);
//                m_receiver->attachObserver(image);
                for(int numberReceivers =0;numberReceivers<m_receivers.size();numberReceivers++){
                    m_receivers.at(numberReceivers)->attachObserver(image);
                }
                images.push_back(image);

                //QPolygonF imagesZone = zone.intersected(image->getIlluminationZone());

                QPolygonF imagesZone = buildingsInIlluminationZone(image,nbReflections);

                //usedWalls.push_back(walls.at(j));
                walls.erase(walls.begin()+j);
                cont = false;
            }
                j++;
        }
    }
    //buildDiffractionPoints(zone,usedWalls,nbReflections,parent);  // Uncomment for diffraction + relfection
    return  illuminatedWalls;
}
