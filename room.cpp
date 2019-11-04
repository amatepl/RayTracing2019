
#include "room.h"
//#include "plots.h"


using namespace std;

room::room(QObject *parente) :
    QGraphicsScene()
  //, QImage(1000,1000, QImage::Format_RGB32)
{   //myParent = parente;
    setSceneRect(0,0,950,500);

    readSettingsFile();

    antenaType = 2; // 0 for transmitter 1 for receiver 2 for nothing
    Transmitter = NULL;
    m_Receiver = NULL;

    m_mode = MoveItem;


    // Absolute electric permittivity
    //eps = epsilonAir*epsilonWallRel;

    // impedance of the wall
    //Zwall = sqrt((muAir/eps));

    // Propagation constants for small-loss hypothesis
    // alpha = 2*M_PI*freq*sqrt((muAir*eps)/2)*sqrt((sqrt(1 + pow((wallSigma/(2*M_PI*freq*eps)), 2)) -1 ));
    // beta = 2*M_PI*freq*sqrt((muAir*eps)/2)*sqrt((sqrt(1 + pow((wallSigma/(2*M_PI*freq*eps)), 2)) + 1 ));

    // gamma = alpha + i*beta;

    // Let us define the walls and draw the view


    Building *building1 = new Building(1,1,1,200,200,200,200,1,this);
    Building *building2 = new Building(250, 1,250, 200,450, 200,450, 1,this);
    Building *building3 = new Building(500, 1, 500, 200,700, 200, 700, 1,this);
    Building *building4 = new Building(750, 1, 750, 200,950, 200, 950, 1,this);
    Building *building5 = new Building(1, 300, 1, 500,200, 500, 200, 300,this);
    Building *building6 = new Building(250, 300, 250, 500,600, 500, 600, 300,this);
    Building *building7 = new Building(650, 300, 650, 500,950, 500, 950, 300,this);

    m_buildings.push_back(building1);
    m_buildings.push_back(building2);
    m_buildings.push_back(building3);
    m_buildings.push_back(building4);
    m_buildings.push_back(building5);
    m_buildings.push_back(building6);
    m_buildings.push_back(building7);

    //Building 1
    walls[0] = new Wall(200,1,200,200, 0.0, 0.0, 0.0, 0);
    walls[18] = new Wall(200,1,1,1, 0.0, 0.0, 0.0, 18);
    walls[1] = new Wall(200,200,1,200, 0.0, 0.0, 0.0, 1);
    walls[19] = new Wall(1,200,1,1, 0.0, 0.0, 0.0, 19);

    //Building 2
    walls[2] = new Wall(250, 1, 250, 200, 0.0, 0.0, 0.0, 2);
    walls[3] = new Wall(250, 200, 450, 200, 0.0, 0.0, 0.0, 3);
    walls[4] = new Wall(450, 200, 450, 1, 0.0, 0.0, 0.0, 4);
    walls[20] = new Wall(450, 1, 250, 1, 0.0, 0.0, 0.0,20);

    //Building 3
    walls[5] = new Wall(500, 1, 500, 200, 0.0, 0.0, 0.0, 5);
    walls[6] = new Wall(500, 200, 700, 200, 0.0, 0.0, 0.0, 6);
    walls[7] = new Wall(700, 200, 700, 1, 0.0, 0.0, 0.0, 7);
    walls[21] = new Wall(700, 1, 500, 1, 0.0, 0.0, 0.0, 21);

    //Building 4
    walls[8] = new Wall(750, 1, 750, 200, 0.0, 0.0, 0.0, 8);
    walls[9] = new Wall(750, 200, 950, 200, 0.0, 0.0, 0.0, 9);
    walls[10] = new Wall(950, 200, 950, 1, 0.0, 0.0, 0.0, 10);
    walls[22] = new Wall(950, 1, 750, 1, 0.0, 0.0, 0.0, 22);

    //Building 5
    walls[11] = new Wall(200, 300, 200, 500, 0.0, 0.0, 0.0, 11);
    walls[23] = new Wall(200, 500, 1, 500, 0.0, 0.0, 0.0, 23);
    walls[24] = new Wall(1, 500, 1, 300, 0.0, 0.0, 0.0, 24);
    walls[12] = new Wall(1, 300, 200, 300, 0.0, 0.0, 0.0, 12);

    //Building 6
    walls[13] = new Wall(250, 300, 250, 500, 0.0, 0.0, 0.0, 13);
    walls[25] = new Wall(250, 500, 600, 500, 0.0, 0.0, 0.0, 25);
    walls[14] = new Wall(600, 500, 600, 300, 0.0, 0.0, 0.0, 14);
    walls[15] = new Wall(600, 300, 250, 300, 0.0, 0.0, 0.0, 15);

    //Building 7
    walls[16] = new Wall(650, 300, 650, 500, 0.0, 0.0, 0.0, 16);
    walls[26] = new Wall(650, 500, 950, 500, 0.0, 0.0, 0.0, 26);
    walls[27] = new Wall(950, 500, 950, 300, 0.0, 0.0, 0.0, 27);
    walls[17] = new Wall(950, 300, 650, 300, 0.0, 0.0, 0.0, 17);

    drawWalls();

    streetsPenDep["commerceUp"] = 0;
    streetsPenDep["commerceDown"] = 0;
    streetsPenDep["spa"] = 0;
    streetsPenDep["indu"] = 0;
    streetsPenDep["deuxEg"] = 0;
    findDiffractionPoints();

}
room::~room(void){}

void room::setUpStreets(){

    struct streets{
        int laLoi[4]= {1,200,950,300};
        int commerceUp[4] = {200,1,250,200};
        int commerceDown[4] = {200,300,250,500};
        int deuxEg[4] = {450,1,500,200};
        int spa[4] = {700,1,750,200};
        int indu[4] = {600,300,650,500};
    };




    //lis = {1,200,950,300};
    struct rect{
      int size[4];
    };
    map <unsigned int,rect*> st;
    rect* str = new rect;
    str->size[0] = 1;
//    st = ('La_Loi', str);
    st['Rue_de_la_Loi']= str;
//    //{'Rue_du_Commerce_Up', {200,1,250,200}};
}

void room::penetrationDepth(){
    int Ry = m_Receiver->getPosY();
    float depth;

    if(onStreet(st->commerceUp)){
        depth = (st->commerceUp[3] - Ry)*0.1;
        //if(depth > streetsPenDep["commerceUp"]){
        if(depth > stDepth[0]){
        streetsPenDep["commerceUp"] = depth;
            stDepth[0] = depth;
        }
    }
    else if(onStreet(st->deuxEg)){
        depth = (st->deuxEg[3] - Ry)*0.1;
        //if(depth > streetsPenDep["deuxEg"]){
        if(depth > stDepth[1]){
            streetsPenDep["deuxEg"] = depth;
            stDepth[1] = depth;
        }
    }
    else if(onStreet(st->spa)){
        depth = (st->spa[3] - Ry)*0.1;
        //if(depth > streetsPenDep["spa"]){
        if(depth > stDepth[2]){
            streetsPenDep["spa"] = depth;
            stDepth[2] = depth;
        }
    }
    else if(onStreet(st->commerceDown)){
        cout<<"OK!"<<endl;
        depth = (Ry - st->commerceDown[1])*0.1;
        //if(depth > streetsPenDep["commerceDown"]){
        if(depth > stDepth[3]){
            streetsPenDep["commerceDown"] = depth;
            stDepth[3] = depth;
        }
    }
    else if(onStreet(st->indu)){
        depth = (Ry - st->indu[1])*0.1;
        //if(depth > streetsPenDep["indu"]){
        if(depth > stDepth[4]){
            streetsPenDep["indu"] = depth;
            stDepth[4] = depth;
        }
    }
}

bool room::onStreet(int street[4]){
    int Rx = m_Receiver->getPosX();
    int Ry = m_Receiver->getPosY();

    return Rx>street[0] && Rx<street[2] && Ry>street[1] && Ry<street[3];
}


bool room::workingZone(int Rx, int Ry){
    bool result;

    bool building1 = Rx>=1 && Rx<=200 && Ry>=1 && Ry<=200;
    bool building2 = Rx>=250 && Rx<=450 && Ry>=1 && Ry<=200;
    bool building3 = Rx>=500 && Rx<=700 && Ry>=1 && Ry<=200;
    bool building4 = Rx>=750 && Rx<=950 && Ry>=1 && Ry<=200;
    bool building5 = Rx>=1 && Rx<=200 && Ry>=300 && Ry<=500;
    bool building6 = Rx>=250 && Rx<=600 && Ry>=300 && Ry<=500;
    bool building7 = Rx>=650 && Rx<=950 && Ry>=300 && Ry<=500;



    result = building1 || building2 || building3 || building4 || building5 || building6 || building7;
    return result ;
}

void room::findDiffractionPoints(){

    /*
     * This fonction adds the diffraction points (corners) to the list of diffraction points.
    */

    //QPointF* diffractionPoint = new QPointF(0,0);
    QPointF diffractionPoint(0,0);
    for(unsigned int i = 0;i<amount_walls;i++){
        for(unsigned int j = 0;j<amount_walls;j++){
//            if(walls[i]->getIndWall() != walls[j]->getIndWall()){
//                if(pointOnLine(walls[j],walls[i]->x1(),walls[i]->y1())){
//                    bool check = true;
//                    unsigned int c = 0;
//                    while(c<diffractionPoints.size()&& check){
//                        check = (diffractionPoints[c][0] != walls[i]->x1() || diffractionPoints[c][1] != walls[i]->y1());
//                        c++;
//                        //cout<<(double)950/500<<endl;
//                    }

//                    if(check){diffractionPoints.push_back({walls[i]->x1(),walls[i]->y1()});}
//                }
//                else if(pointOnLine(walls[j],walls[i]->x2(),walls[i]->y2())){
//                    bool check = true;
//                    unsigned int c = 0;
//                    while(c<diffractionPoints.size()&& check){
//                        check = (diffractionPoints[c][0] != walls[i]->x2() || diffractionPoints[c][1] !=walls[i]->y2());
//                        c++;
//                    }

//                    if(check){diffractionPoints.push_back({walls[i]->x2(),walls[i]->y2()});}
//                }
//            }
            if(walls[i]!= walls[j]){
                if(walls[i]->intersect(*walls[j],&diffractionPoint)==1){
                    bool check = true;
                    unsigned int c = 0;
                    while(c<diffractionPoints.size()&& check){
                        check = (diffractionPoints[c][0] !=  (&diffractionPoint)->x()||diffractionPoints[c][1] !=   (&diffractionPoint)->y() );
                        c++;
                        //cout<<(double)950/500<<endl;
                    }

                    if(check&& !(&diffractionPoint)->isNull()){diffractionPoints.push_back({(&diffractionPoint)->x(),(&diffractionPoint)->y()});}
                }
            }
        }
    }
}


void room::drawWalls(){
    QPen outlinePen(QColor(0, 0, 0, 255));
    outlinePen.setWidth(2);
    for(unsigned int i = 0;i<amount_all_walls;i++){
        this->addLine(walls[i]->x1(),walls[i]->y1(),walls[i]->x2(),walls[i]->y2(),outlinePen);
    }
}


void room::setAntenaType(int type){antenaType = type;}

void room::launch_algo(bool drawR){

    /*
     * This function is called upon when the user pushes the launch_algo button
     * The clearAll() method empties the previous calculation to assure that the previous experiment is deleted in the memory
     *
     * Methods (math and geometry) : void recursion(), void calculateDiffractedRays();
     * Methods (drawing and ray creation) : void drawRay();
     * Methods (electric properties) : double dBm(), double calculatePower(vector < vector <rays*>>);
     *
     * Parameters : double powerReceived, double resultsBinaryDebit;
     */

    clearAll();     // Resets the power, binary debit and ray vector --> 0
    computePhysicalResponse = drawR;

    // TEST -----------------------


    createImages();
    m_receiver->notifyObservers();
    //buildingsInIlluminationZone();
//    QColor illumination;
//    illumination.setBlue(255);
//    illumination.setAlpha(100);
//    addPolygon(Transmitter->getIluminationZone(itemsBoundingRect()),QPen(),illumination);

    // END TEST--------------------

//    if(!workingZone(m_Receiver->getPosX(), m_Receiver->getPosY())){
//        // Calculate power -- Reflexion and transmission

//        current_ray = new Line(m_Receiver->getPosX(),m_Receiver->getPosY(),Transmitter->getPosX(),Transmitter->getPosY());
//        bool reflection = true;
//        unsigned int i = 0;
//        while(i<amount_walls && reflection){
//            reflection = !intersectionCheck(current_ray,walls[i]);
//            i++;
//        }
//        delete(current_ray);

//        if(drawR){
//            if(reflection){recursion(Transmitter->getPosX(), Transmitter->getPosY(),m_Receiver->getPosX(),m_Receiver->getPosY(),reflectionsNumber,drawRay);}
//            else{
//                drawDiffraction(this);}
//        }
//        else{
//            if(reflection){recursion(Transmitter->getPosX(), Transmitter->getPosY(),m_Receiver->getPosX(),m_Receiver->getPosY(),reflectionsNumber, buildRay);}
//            else{buildDiffraction((this));}
//        }
//        //cout<<diffractedPower<<endl;
//        //if(diffractedPower !=0){power = power + dBmRev(diffractedPower);}

//        //if(diffractedPower !=0){powerRef = powerRef + dBmRev(diffractedPower);}
//        if(reflection){
//            powerRef = computePrx(totalEfield);
//            powerReceived = dBm(powerRef);
//        }
//        if(powerReceived){
//            resultsBinaryDebit = binaryDebit(powerReceived);
//        }
//    }
}


// ------------------------------ Image method ------------------------------------------------


void room::recursion(double transmitterPosX, double transmitterPosY, double receiverPosX, double receiverPosY, int numberOfReflections,void (*draw)(double, double, double, double,room*)){

    /*
     * The recursion method generalize the image method for any amount of reflections. Keeps track of the depth of the recursive algorithm.
     * Calls drawRay and stores the rays as they are being created.
     */

    transmitterSerie[recursionState][0] = transmitterPosX;
    transmitterSerie[recursionState][1] = transmitterPosY;

    Line* current_wall = wallRecursiveNumber[recursionState];

    int NumberOfReflections = numberOfReflections;

    // ---- Drawing of the ray on the screen && saving ----
    (*draw)(transmitterPosX,transmitterPosY,receiverPosX,receiverPosY,this);



    // --- Re-loop starts -------------
    if(NumberOfReflections > 0 ){
        recursionState += 1;

        //Direct ray beteween the transmitter and the receiver
        for(unsigned int i = 0;i < amount_walls;i++){

           current_wall = walls[i];

            if(current_wall != wallRecursiveNumber[recursionState -1]){
                wallRecursiveNumber[recursionState] = walls[i];

                angle_wall = current_wall->getAngleRad();

                //------------TRANSMITTER IMAGE CONSTRUCTION--------------------------

                //auto start = high_resolution_clock::now();

//                int ray_vector_length = sqrt(pow(transmitterPosY - current_wall->y2(),2) + pow(transmitterPosX - current_wall->x2(),2));
//                float virtual_slope;

//                if (transmitterPosY - current_wall->y2() < 0 && transmitterPosX - current_wall->x2()){
//                    virtual_slope = -acos((transmitterPosX - current_wall->x2())/ray_vector_length);
//                }

//                else{
//                    virtual_slope = acos((transmitterPosX - current_wall->x2())/ray_vector_length);
//                }

//                float ray_slope = angle_wall + (angle_wall - virtual_slope);
//                float ray_vector[2] ={cos(ray_slope) , sin(ray_slope)};
//                float x2 = ray_vector_length * ray_vector[0];
//                float y2 = ray_vector_length * ray_vector[1];
//                double transmitterImagePosX = current_wall->x2() + x2;
//                double transmitterImagePosY = current_wall->y2() + y2;




                QPointF transmitterImagePos = current_wall->symetricalPoint(transmitterPosX,transmitterPosY);
//                auto stop = high_resolution_clock::now();

//                auto duration = duration_cast<nanoseconds>(stop - start);

//                cout << duration.count() << endl;

                //---------END OF TRANSMITTER IMAGE CONSTRUCTION--------------------------

                //current_ray = new Line(transmitterImagePosX, transmitterImagePosY,receiverPosX,receiverPosY);
                //imCoordinates[0] = intersection(current_ray,current_wall)[0];
                //imCoordinates[1] = intersection(current_ray,current_wall)[1];
                //delete(current_ray);
                //if(pointOnLine(current_wall,imCoordinates[0],imCoordinates[1]) && pointOnLine(current_ray,imCoordinates[0],imCoordinates[1])){
                    //recursion(transmitterImagePosX, transmitterImagePosY,receiverPosX,receiverPosY,NumberOfReflections - 1,draw);
                    recursion(transmitterImagePos.x(), transmitterImagePos.y(),receiverPosX,receiverPosY,NumberOfReflections - 1,draw);
                //}

            }

        if(i == amount_walls - 1){recursionState -=1;}
        }
    }
}

struct forImage{
    vector <Wall*> walls;
    const QPolygonF zone;
};


void room::createImages(){
    int recursionDepth = reflectionsNumber;
//    int recursionDepth = 0;
//    QPolygonF illuminatedZone =  transmitterIllumination();
    forImage data = transmitterIllumination();
    illuminatedWalls(data.walls,data.zone,recursionDepth -1 ,Transmitter);
//    buildingsInIlluminationZone(Transmitter, recursionDepth);

}


//QPolygonF room::transmitterIllumination(){
forImage room::transmitterIllumination(){

    // Painting tools
    QColor illumination;
    illumination.setBlue(255);
    illumination.setAlpha(100);


    vector <Building*> illuminatedBuldings; // Buildings lying in the initial illumination zone.
//    QPolygonF illuminationZone = Transmitter->getIluminationZone(itemsBoundingRect());
    QPolygonF illuminationZone = Transmitter->getIlluminationZone();
    vector <Wall*> nearestWalls;

    foreach(Building *building, m_buildings){
        QPolygonF p_building(*building);

        if(p_building.intersects(illuminationZone)){
            illuminatedBuldings.push_back(building);
            illuminationZone = illuminationZone.subtracted(building->shadow(Transmitter->getPosition()));
            QPointF corner = building->closestPoint(Transmitter->getPosition()); // Closest point of the building to the transmitter
            nearestWalls.push_back(building->nearestWalls(corner).at(0));   // Add the 2 walls that are at the corner.
            nearestWalls.push_back(building->nearestWalls(corner).at(1));

        }
    }
    Transmitter->setIlluminatedZone(illuminationZone);
    //addPolygon(illuminationZone,QPen(),illumination);

    forImage result{nearestWalls,illuminationZone};

    return result;
}


QPolygonF room::buildingsInIlluminationZone(AbstractAntena *ant, int nbReflections)
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
    //addPolygon(illuminationZone,QPen(),illumination2);
    vector <Wall*> nearestWalls;

    foreach(Building *building, m_buildings){
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
    //addPolygon(illuminationZone.intersected(Transmitter->getIlluminatedZone()),QPen(),illumination);

    if(recursionDepth > 0){
        illuminatedWalls(nearestWalls,illuminationZone, recursionDepth -1,ant);
    }
    return illuminationZone;
}

vector <Line> room::illuminatedWalls(vector <Wall*> walls, const QPolygonF zone, int nbReflections, AbstractAntena *parent){
    vector <Line> illuminatedWalls;

    QPen redPen(Qt::red);
    redPen.setWidth(3);

    QColor illumination1;
    illumination1.setGreen(255);
    illumination1.setAlpha(100);

    vector <AntenaImage *> images; // vector for tests

    for(int i=1; i <  zone.length()-2 ;i++){

        /*
         * Here we go thorough the sides of the illumination zone and check if they are a part of a wall
         * If yes, then the part is used to build the image of the transmitter.
         */

        int j =0;
        bool cont = true;
        while(j<walls.size() && cont){
            if(walls.at(j)->onLine(zone.at(i)) && walls.at(j)->onLine(zone.at(i+1))){
                illuminatedWalls.push_back(Line(zone.at(i),zone.at(i+1)));

                addLine(Line(zone.at(i),zone.at(i+1)),redPen);

                //Creation of the trasmitter image
                AntenaImage *image = new AntenaImage(Line(zone.at(i),zone.at(i+1)),parent);
                image->setBuilding(walls.at(j)->getBuilding());
                image->setSceneBoundary(itemsBoundingRect());
                m_receiver->addAntenaImage(image);
                images.push_back(image);
                walls.erase(walls.begin()+j);
                //QPolygonF imagesZone = zone.intersected(image->getIlluminationZone());

                QPolygonF imagesZone = buildingsInIlluminationZone(image,nbReflections);

                cont = false;
            }
            j++;
        }
    }


    return  illuminatedWalls;
}

void room::drawRay(double transmitterPosX,double transmitterPosY,double originX,double originY,room* scene){

    /*
     * Called back from the recursion method, draws the rays when necessary, then removes the excess
     */

    auto start = high_resolution_clock::now();
    // Freeing memory
    vector <ray*> completeRay;
    completeRay.clear();
    Line *current_ray;
    ray* receiver_ray;

    // Setting up drawing tool
    QPen outlinePen(QColor(0, 0, 255, 255));
    outlinePen.setWidth(1);

    unsigned char j = 0;
    while(j<=(*scene).recursionState){

        /*
         * We need to check if our rays reflects on the right walls. For that purpouse we check the
         * intersection of the last ray component with the wall that was used to build the transmitter image.
        */

        Wall* walle = (*scene).wallRecursiveNumber[(*scene).recursionState -j];
        transmitterPosX = (*scene).transmitterSerie[(*scene).recursionState-j][0];
        transmitterPosY = (*scene).transmitterSerie[(*scene).recursionState-j][1];
        current_ray= new Line(transmitterPosX,transmitterPosY,originX,originY);

        // To get rid of this if the original transmitter has to be added to the transmitterSrerie
        if(j != (*scene).recursionState){

            //double imageCoordinates[2] = {(*scene).intersection(current_ray,walle)[0],(*scene).intersection(current_ray,walle)[1]};
            QPointF imageCoordinates;


            //if((*scene).pointOnLine(walle,imageCoordinates[0],imageCoordinates[1]) && (*scene).pointOnLine(current_ray,imageCoordinates[0],imageCoordinates[1])){
            if(current_ray->intersect(*walle,&imageCoordinates)==1){


                receiver_ray = new ray(imageCoordinates.x(),imageCoordinates.y(),originX,originY,current_ray->angleTo(*walle),walle->getIndWall());

                completeRay.push_back(receiver_ray);
                originX = imageCoordinates.x();
                originY = imageCoordinates.y();
                delete(current_ray);

            }
            else{
                /*
                 * Here we know that the ray doesn't reflect on any real wall so we've got to destroy it and also its past.
                */

                completeRay.clear();
                delete(current_ray);
                j = (*scene).recursionState+1; // Setting j to this value stops the while loop
            }
        }
        else if(j == (*scene).recursionState){

            //Ray from transmitter
            receiver_ray = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),originX,originY,0,0);
            completeRay.push_back(receiver_ray);
        }
        j++;
    }

    unsigned int i = 0;
    bool dontStop = true;
    while(i<completeRay.size() && dontStop){
        for (unsigned int j = 0;j<(*scene).amount_walls;j++){
            /*
             This loop checks if there is any intersection of the ray with the walls. If this is the case we destroy the ray since
             there is no transmission.
            */

            receiver_ray = completeRay[i];
            current_ray = new Line(receiver_ray->x1(),receiver_ray->y1(),receiver_ray->x2(),receiver_ray->y2());

//            if((*scene).intersectionCheck(current_ray,(*scene).walls[j])&& !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->getX2(), completeRay[i]->getY2()) && !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->getX1(), completeRay[i]->getY1())){

            // Check if there is intersection between current ray and any wall and if this intersection is not the reflexion point.
            bool inter =(*scene).intersectionCheck(current_ray,(*scene).walls[j])&& !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->x2(), completeRay[i]->y2()) && !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->x1(), completeRay[i]->y1());
            //Check if we don't reflect on a corner.
            bool extremity1 = (completeRay[i]->x1() != (*scene).walls[j]->x1() && completeRay[i]->y1() != (*scene).walls[j]->y1()) || (completeRay[i]->x2() != (*scene).walls[j]->x2() && completeRay[i]->y2() != (*scene).walls[j]->y2());
            bool extremity2 = (completeRay[i]->x1() != (*scene).walls[j]->x2() && completeRay[i]->y1() != (*scene).walls[j]->y2()) || (completeRay[i]->x2() != (*scene).walls[j]->x1() && completeRay[i]->y2() != (*scene).walls[j]->y1());
            if(inter && (!extremity1 || !extremity2)){
                delete(current_ray);
                completeRay.clear();
                completeRay.shrink_to_fit();
                dontStop = false;
                break;
            }
        }
        i++;
    }

    if(!completeRay.empty()){
        unsigned int i = 0;
        while(i<completeRay.size()){
            outlinePen.setColor(QColor(0,255 -  (255/(*scene).reflectionsNumber)*(i),255,255));
            //receiver_ray->setPen(outlinePen);
            scene->addLine(completeRay[i]->x1(),completeRay[i]->y1(),completeRay[i]->x2(),completeRay[i]->y2(),outlinePen);

//            cout<<"x1 and y1: ";
//            cout<<completeRay[i]->x1();
//            cout<<", ";
//            cout<<completeRay[i]->y1()<<endl;

//            cout<<"x2 and y2: ";
//            cout<<completeRay[i]->x2();
//            cout<<", ";
//            cout<<completeRay[i]->y2()<<endl;
//            cout<<"--------------------------"<<endl;
            i++;
        }
        (*scene).totalEfield += scene->computeEfield(completeRay);

        delete(receiver_ray);
        completeRay.clear();
        completeRay.shrink_to_fit();
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << duration.count() << endl;

}

///////////////////////////////build///////////////////////////////

void room::buildRay(double transmitterPosX,double transmitterPosY,double originX,double originY,room* scene){

    /*
     * Called back from the recursion method, draws the rays when necessary, then removes the excess
     */

    // Freeing memory
    vector <ray*> completeRay;
    completeRay.clear();
    Line *current_ray;
    ray* receiver_ray;

    unsigned char j = 0;
    while(j<=(*scene).recursionState){

        /*
         * We need to check if our rays reflects on the right walls. For that purpouse we check the
         * intersection of the last ray component with the wall that was used to build the transmitter image.
        */

        Wall* walle = (*scene).wallRecursiveNumber[(*scene).recursionState -j];
        transmitterPosX = (*scene).transmitterSerie[(*scene).recursionState-j][0];
        transmitterPosY = (*scene).transmitterSerie[(*scene).recursionState-j][1];
        current_ray= new Line(transmitterPosX,transmitterPosY,originX,originY);

        // To get rid of this if the original transmitter has to be added to the transmitterSrerie
        if(j != (*scene).recursionState){

            //double imageCoordinates[2] = {(*scene).intersection(current_ray,walle)[0],(*scene).intersection(current_ray,walle)[1]};
            QPointF imageCoordinates;


            //if((*scene).pointOnLine(walle,imageCoordinates[0],imageCoordinates[1]) && (*scene).pointOnLine(current_ray,imageCoordinates[0],imageCoordinates[1])){
            if(current_ray->intersect(*walle,&imageCoordinates) == 1){

                receiver_ray = new ray(imageCoordinates.x(),imageCoordinates.y(),originX,originY,current_ray->angleTo(*walle),walle->getIndWall());
                delete(current_ray);
                completeRay.push_back(receiver_ray);
                originX = imageCoordinates.x();
                originY = imageCoordinates.y();

            }
            else{
                /*
                 * Here we know that the ray doesn't reflect on any real wall so we've got to destroy it and also its past.
                */
                delete(current_ray);
                completeRay.clear();
                completeRay.shrink_to_fit();
                j = (*scene).recursionState+1; // Setting j to this value stops the while loop
            }
        }
        else if(j == (*scene).recursionState){

            //Ray from transmitter
            receiver_ray = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),originX,originY,0,0);
            completeRay.push_back(receiver_ray);
        }
        j++;
    }

    unsigned int i = 0;
    bool dontStop = true;
    while(i<completeRay.size() && dontStop){
        for (unsigned int j = 0;j<(*scene).amount_walls;j++){
            /*
             This loop checks if there is any intersection of the ray with the walls. If this is the case we destroy the ray since
             there is no transmission.
            */

            receiver_ray = completeRay[i];
            current_ray = new Line(receiver_ray->x1(),receiver_ray->y1(),receiver_ray->x2(),receiver_ray->y2());
            //if((*scene).intersectionCheck(current_ray,(*scene).walls[j])&& !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->getX2(), completeRay[i]->getY2()) && !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->getX1(), completeRay[i]->getY1())){

            // Check if there is intersection between current ray and any wall and if this intersection is not the reflexion point.
            bool inter =(*scene).intersectionCheck(current_ray,(*scene).walls[j])&& !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->x2(), completeRay[i]->y2()) && !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->x1(), completeRay[i]->x1());
            //Check if we don't reflect on a corner.
            bool extremity1 = (completeRay[i]->x1() != (*scene).walls[j]->x1() && completeRay[i]->y1() != (*scene).walls[j]->y1() && completeRay[i]->x2() != (*scene).walls[j]->x2() && completeRay[i]->y2() != (*scene).walls[j]->y2());
            bool extremity2 = (completeRay[i]->x1() != (*scene).walls[j]->x2() && completeRay[i]->y1() != (*scene).walls[j]->y2() && completeRay[i]->x2() != (*scene).walls[j]->x1() && completeRay[i]->y2() != (*scene).walls[j]->y1());
            if(inter && extremity1 && extremity2){
                delete(current_ray);
                completeRay.clear();
                dontStop = false;
                break;
            }
        }
        i++;
    }

    if(!completeRay.empty()){
        //(*scene).power +=1/(8*(*scene).Ra)*(*scene).calculateRay(completeRay);
        (*scene).totalEfield += scene->computeEfield(completeRay);
        delete(receiver_ray);
        completeRay.clear();
        completeRay.shrink_to_fit();
    }
}




// ----------------------------------------------- Diffraction -----------------------------------------------------


void room::drawDiffraction(room* scene){

    /* This function draws the diffracted ray and asks to calculate its power.
     * Only one diffraction is allowed for a given position of the transmitter and the receiver.
     */

    // Setting-up the drawing tool.
    QPen outlinePen(QColor(255, 0, 0, 220));
    outlinePen.setWidth(1);

    // Those will check the intersections with the walls.
    Line* pathTester;

    //Actual rays that we chould obtein when the diffracation happens.
    ray* rayReceiver;
    ray* rayTransmitter;


    //(*scene).diffractionPoints.clear();
    vector<std::array <double,2>> usedDiffPoints;


//    for(unsigned int i =0;i< (*scene).diffractionPoints.size();i++){
//        if((*scene).diffractionPoints[i][0]>(*scene).Receiver->getPosX() && (*scene).diffractionPoints[i][0]<(*scene).Transmitter->getPosX() && (*scene).diffractionPoints[i][1]>(*scene).Receiver->getPosY() && (*scene).diffractionPoints[i][1]<(*scene).Transmitter->getPosY()){
//            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
//        }
//        else if((*scene).diffractionPoints[i][0]<(*scene).Receiver->getPosX() && (*scene).diffractionPoints[i][0]>(*scene).Transmitter->getPosX() && (*scene).diffractionPoints[i][1]<(*scene).Receiver->getPosY() && (*scene).diffractionPoints[i][1]>(*scene).Transmitter->getPosY()){
//            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
//        }
//        else if((*scene).diffractionPoints[i][0]<(*scene).Receiver->getPosX() && (*scene).diffractionPoints[i][0]>(*scene).Transmitter->getPosX() && (*scene).diffractionPoints[i][1]>(*scene).Receiver->getPosY() && (*scene).diffractionPoints[i][1]<(*scene).Transmitter->getPosY()){
//            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
//        }
//        else if((*scene).diffractionPoints[i][0]>(*scene).Receiver->getPosX() && (*scene).diffractionPoints[i][0]<(*scene).Transmitter->getPosX() && (*scene).diffractionPoints[i][1]<(*scene).Receiver->getPosY() && (*scene).diffractionPoints[i][1]>(*scene).Transmitter->getPosY()){
//            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
//        }
//    }

    for(unsigned int i =0;i< (*scene).diffractionPoints.size();i++){
        if((*scene).diffractionPoints[i][0] >(*scene).m_Receiver->x() && (*scene).diffractionPoints[i][0]<(*scene).Transmitter->x() && (*scene).diffractionPoints[i][1]>(*scene).m_Receiver->y() && (*scene).diffractionPoints[i][1]<(*scene).Transmitter->y()){
            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
        }
        else if((*scene).diffractionPoints[i][0]<(*scene).m_Receiver->x() && (*scene).diffractionPoints[i][0]>(*scene).Transmitter->x() && (*scene).diffractionPoints[i][1]<(*scene).m_Receiver->y() && (*scene).diffractionPoints[i][1]>(*scene).Transmitter->y()){
            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
        }
        else if((*scene).diffractionPoints[i][0]<(*scene).m_Receiver->x() && (*scene).diffractionPoints[i][0]>(*scene).Transmitter->x() && (*scene).diffractionPoints[i][1]>(*scene).m_Receiver->y() && (*scene).diffractionPoints[i][1]<(*scene).Transmitter->y()){
            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
        }
        else if((*scene).diffractionPoints[i][0]>(*scene).m_Receiver->x() && (*scene).diffractionPoints[i][0]<(*scene).Transmitter->x() && (*scene).diffractionPoints[i][1]<(*scene).m_Receiver->y() && (*scene).diffractionPoints[i][1]>(*scene).Transmitter->y()){
            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
        }
    }

    bool notDiffracted = true;
    unsigned int i =0;
    while(i<usedDiffPoints.size() && notDiffracted){
        pathTester = new Line(usedDiffPoints[i][0],usedDiffPoints[i][1],(*scene).m_Receiver->getPosX(), (*scene).m_Receiver->getPosY());
        bool noTrans = true;

        unsigned int j = 0;
        while(j<(*scene).amount_all_walls){
            //vector<double> inters = (*scene).intersection(pathTester,(*scene).walls[j]);
            QPointF inters;
            if(pathTester->intersect(*(*scene).walls[j],&inters)==1 && inters.x() != usedDiffPoints[i][0] && inters.y() != usedDiffPoints[i][1]){
            //if((*scene).pointOnLine(pathTester,inters[0],inters[1]) && (*scene).pointOnLine((*scene).walls[j],inters[0],inters[1]) && inters[0] != usedDiffPoints[i][0] && inters[1] != usedDiffPoints[i][1]){
                noTrans = false;
            }
            j++;
        }

        if(noTrans){
            scene->addLine((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),usedDiffPoints[i][0],usedDiffPoints[i][1],outlinePen);
            scene->addLine((*scene).m_Receiver->getPosX(),(*scene).m_Receiver->getPosY(),usedDiffPoints[i][0],usedDiffPoints[i][1],outlinePen);
            rayReceiver = new ray((*scene).m_Receiver->getPosX(),(*scene).m_Receiver->getPosY(),usedDiffPoints[i][0],usedDiffPoints[i][1],0,0);
            rayTransmitter = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),usedDiffPoints[i][0],usedDiffPoints[i][1],0,0);
            double diffractPower = (*scene).diffractedRayPower(rayReceiver,rayTransmitter);
            (*scene).powerRef = diffractPower;
            (*scene).powerReceived = (*scene).dBm(diffractPower);
            delete(rayReceiver);
            delete(rayTransmitter);
            //(*scene).diffractedPower+= diffractPower;
            notDiffracted =false;
        }
    delete(pathTester);
    i++;
    }
    usedDiffPoints.clear();
    usedDiffPoints.shrink_to_fit();

}


void room::buildDiffraction(room* scene){
    /* This function builds the diffracted ray and asks to calculate its power.
     * Only one diffraction is allowed for a given position of the transmitter and the receiver.
     */

    // Those will check the intersections with the walls.
    Line* pathTester;

    //Actual rays that we chould obtein when the diffracation happens.
    ray* rayReceiver;
    ray* rayTransmitter;


    vector<std::array <double,2>> usedDiffPoints;


    for(unsigned int i =0;i< (*scene).diffractionPoints.size();i++){

        /*
         * This for loop choses omly the possible diffraction points i.e. the diffraction point lying in the rectanglw which two opposite
         * corners are the positions of the transmitter and the receiver.
         */

        if((*scene).diffractionPoints[i][0]>(*scene).m_Receiver->getPosX() && (*scene).diffractionPoints[i][0]<(*scene).Transmitter->getPosX() && (*scene).diffractionPoints[i][1]>(*scene).m_Receiver->getPosY() && (*scene).diffractionPoints[i][1]<(*scene).Transmitter->getPosY()){
            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
        }
        else if((*scene).diffractionPoints[i][0]<(*scene).m_Receiver->getPosX() && (*scene).diffractionPoints[i][0]>(*scene).Transmitter->getPosX() && (*scene).diffractionPoints[i][1]<(*scene).m_Receiver->getPosY() && (*scene).diffractionPoints[i][1]>(*scene).Transmitter->getPosY()){
            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
        }
        else if((*scene).diffractionPoints[i][0]<(*scene).m_Receiver->getPosX() && (*scene).diffractionPoints[i][0]>(*scene).Transmitter->getPosX() && (*scene).diffractionPoints[i][1]>(*scene).m_Receiver->getPosY() && (*scene).diffractionPoints[i][1]<(*scene).Transmitter->getPosY()){
            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
        }
        else if((*scene).diffractionPoints[i][0]>(*scene).m_Receiver->getPosX() && (*scene).diffractionPoints[i][0]<(*scene).Transmitter->getPosX() && (*scene).diffractionPoints[i][1]<(*scene).m_Receiver->getPosY() && (*scene).diffractionPoints[i][1]>(*scene).Transmitter->getPosY()){
            usedDiffPoints.push_back((*scene).diffractionPoints[i]);
        }
    }

    bool notDiffracted = true;
    unsigned int i =0;
    while(i<usedDiffPoints.size() && notDiffracted){
        pathTester = new Line(usedDiffPoints[i][0],usedDiffPoints[i][1],(*scene).m_Receiver->getPosX(), (*scene).m_Receiver->getPosY());
        bool noTrans = true;
        unsigned int j = 0;

        while(j<(*scene).amount_all_walls){

            /*
             * Here we check if the path tester intersect any wall. If yes the diffraction is canceled.
             */

            //vector<double> inters = (*scene).intersection(pathTester,(*scene).walls[j]);
            QPointF inters;
            //if((*scene).pointOnLine(pathTester,inters[0],inters[1]) && (*scene).pointOnLine((*scene).walls[j],inters[0],inters[1]) && inters[0] != usedDiffPoints[i][0] && inters[1] != usedDiffPoints[i][1]){
            if(pathTester->intersect(*(*scene).walls[j],&inters)==1 && inters.x() != usedDiffPoints[i][0] && inters.y() != usedDiffPoints[i][1]){
                noTrans = false;
            }
            j++;
        }

        if(noTrans){
            rayReceiver = new ray((*scene).m_Receiver->getPosX(),(*scene).m_Receiver->getPosY(),usedDiffPoints[i][0],usedDiffPoints[i][1],0,0);
            rayTransmitter = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),usedDiffPoints[i][0],usedDiffPoints[i][1],0,0);
            double diffractPower = (*scene).diffractedRayPower(rayReceiver,rayTransmitter);
            (*scene).powerRef = diffractPower;
            (*scene).powerReceived = (*scene).dBm(diffractPower);
            if((*scene).powerReceived > -70){
                (*scene).penetrationDepth();
            }
            delete(rayTransmitter);
            delete(rayReceiver);
            //(*scene).diffractedPower+= diffractPower;
            notDiffracted =false;
        }
    delete(pathTester);
    i++;
    }
    usedDiffPoints.clear();
    usedDiffPoints.shrink_to_fit();

}


// --> Numerical computing --------------------------------------------------------------------------------------------------------------



// --> geometric tools ------------------------------------------------------------------------------------------------------------------


bool room::commonToAnyWall(double posX, double posY, int indwall){

    /*
     * To know whether or not an extremety of a wall is an edge, it is requered to check if the point is shared with another wall of the list
     */

    bool ans = true;

    for (unsigned int i = 0; i < amount_walls; i ++){

            if(pointOnLine(walls[i], posX, posY)  && i != indwall /*&& walls[i]->line().intersect(walls[indwall]->line(), NULL) == 0*/){
                ans = false;
            }
    }
    return ans;
}



//bool room::pointOnLine(lineo* line1, double x, double y){
bool room::pointOnLine(Line* line1,const double xp,const double yp){
    /*
     * As the intersection is computed by lines equations, it is required to check whether or not the intersection is placed on the the wall line, an line
     * equation being define from [-INF, +INF]
     */

    int x1 = (int)line1->x1();
    int y1 = (int)line1->y1();
    int x2 = (int)line1->x2();
    int y2 = (int)line1->y2();

    bool answer = false;

    int x = xp;
    int y = yp;

    if(x1 == x2){   // Cas du mur vertical
        answer = ((y<=y2 && y>=y1) || ( y>=y2 && y<=y1)) && x == x1;
    }
    else if (y1 == y2){   // Cas du mur horizental
        answer = ((x>=x2 && x<=x1) || (x<=x2 && x>=x1)) && y == y1;
    }
    else {
       answer = ((x1<=x && y1<=y && x2>=x && y2 >=y) ||(x1>=x && y1>=y && x2<=x && y2 <=y)||(x>=x2 && y<=y2 && x<=x1 && y>=y1) || (x<=x2 && y>=y2 && x>=x1 && y<=y1));
    }
    return answer;

}



bool room::intersectionCheck(Line* line1, Line* line2){
    /*
     * Two-equations line system, determines the intersection point if it exists
     *    y = ax + b
     *    y = cx + d
     */

//    double xpos;
//    double ypos;

//    long double a = line1->getSlope();
//    double b = line1->getYorigin();
//    long double c = line2->getSlope();
//    double d = line2->getYorigin();

//    if(a == INFINITY){
//        xpos = line1->getX1();
//        ypos = c * xpos + d;
//    }

//    else if(c == INFINITY){
//        xpos = line2->getX1();
//        ypos = a * xpos + b;
//    }
//    else{
//    xpos = (d - b)/(a - c);
//    ypos = (a * xpos) + b;
//    }
//    xpos = round(xpos);
//    ypos = round(ypos);

//    return (pointOnLine(line1,xpos,ypos) && pointOnLine(line2,xpos,ypos));

    bool res;
    QPointF point;
    if(line1->intersect(*line2,&point)==1){
        res = 1;
    }
    else
        res = 0;
    return res;


}




bool room::checkTransmission(Line* line1, Line* line2, int x1, int y1,int x2,int y2){
    bool isNotTransmitted = false;
    if(intersectionCheck(line1,line2)){
        if(!pointOnLine(line1,x1,y1)){
            if(!pointOnLine(line1,x2,y2)){
                isNotTransmitted = true;
            }

        }
    }
    return isNotTransmitted;
}

// double room::distInWall(double tetai){

// /*
//  * It is requiered to know the distance travelled in the wall, we will use Snell's rule to determine the angle in the transmitted ray inside the wall, then
//  * knowing the thickness determine the length in the wall by simple trigonometry.
//  */
//     double tetaTrans = asin((sqrt(epsilonAir)*sin(tetai))/(sqrt(epsilonWallRel*epsilonAir)));    // Snell's rule

//     return wallThickness*pow(10, -2)/cos(tetaTrans);    // L/cos(\teta_Transmitted) cosine projection, the 1/2 factor for the pixel to Cm conversion
// }

// --> Electrical power calculation --------------------------------------------------------------------------------------------------------------------

double room::computeReflexionPer(double thetaI, double epsilonR){
    //double R = (cos(thetaI) - sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)))/(cos(thetaI) + sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)));
    /*
     * Now in the code thatai is the angle between the ray and the wall and not between the ray and the normal to the wall.
     * Basicly thetai = pi/2 - thetai.
     * Because of that cos and sin are inverted and we take their absolute value because of the angles given by Qt.
     */

    double R = (abs(sin(thetaI)) - sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(cos(thetaI),2)))/(abs(sin(thetaI)) + sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(cos(thetaI),2)));
    return R;
}

double room::computeReflexionPar(double thetaI, double epsilonR){
    double R = (cos(thetaI) - (1/sqrt(epsilonR))*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)))/(cos(thetaI) + (1/sqrt(epsilonR))*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)));
    return R;
}

void room::computeEMField(vector<ray> *rays){
    totalEfield += computeEfield(rays);
    powerRef = computePrx(totalEfield);
    powerReceived = dBm(powerRef);
}

void room::clearEMFIeld(){
    totalEfield = 0;
}

complex <double> room::computeEfield(vector<ray> *rayLine){
    /* One vector<ray*> is one multi-path componant, the size of the vector determine the n-level we are in, for each ray only the power in the last ray is transmitted to
     * the receptor. As seen in the power formula, n rays -> n-1 additions to the power.
     *
     * This function gives the electrical field, generated by one MPC, at the receiver. The electric field is // to the dipole antenna since we only consider relections
     * off the buildings. The electric field is not // for the reflexion with the ground though. This is taken into account in the function computePrx.
     */

    complex <double> i(0.0, 1.0);
    int amountSegment = rayLine->size();
    double completeLength = 0.0;
    double theta = 0.0;
    double R = 1;
    complex <double> Efield = 0.0;
    ray currentRay;
    for (int i=0; i<amountSegment; i++){
        currentRay = rayLine->at(i);
        theta = currentRay.getTheta();
        if((i != amountSegment-1)){   // The last segment, the one that reach the receptor does not have a rebound
            double thetaI = abs(currentRay.getTetai());
            R *= computeReflexionPer(thetaI,epsilonWallRel);
        }
        completeLength += currentRay.getMeterLength(); // Get each length of each ray segment after the meter conversion (1px == 1dm)
    }
    double Ia = sqrt(2.0*powerEmettor/Ra); // Ia could be changed for Beamforming application (add exp)
    double a = R * ((Zvoid*Ia)/(2.0*M_PI))/completeLength;
    Efield = i * a * exp(-i*(2.0*M_PI/lambda)*completeLength);

    if(amountSegment==1){
        this->minLength = completeLength; // for delay spread computation
        this->LOS = pow(a,2);
    } else{
        this->NLOS += pow(a,2);
    }
    if(completeLength > this->maxLength){
        this->maxLength = completeLength; // for delay spread computation
    }
    // Store ray parameter for Physical impulse response
//    if(computePhysicalResponse){
//        // Store attenuation a and distance completeLength
//        channelData[rayNumber] = R/completeLength;
//        channelData[rayNumber+20] = completeLength;
//        double degangle = round((theta+direction)*180/M_PI);
//        double radangle = degangle*M_PI/180;
//        spectrumField[specNumber] = Efield;
//        spectrumAngle[specNumber] = (2.0*M_PI/lambda)*speedReal*cos(radangle);
//        int save = specNumber;
//        for (int j = 0; j < save; j++){
//            if (spectrumAngle[j] == spectrumAngle[save]){
//                spectrumField[j] += Efield;
//                specNumber -= 1;
//            }
//        }
//        specNumber += 1;
//        rayNumber += 1;
//    }
    return Efield;
}


complex <double> room::computeEfield(vector<ray*> rayLine){
    /* One vector<ray*> is one multi-path componant, the size of the vector determine the n-level we are in, for each ray only the power in the last ray is transmitted to
     * the receptor. As seen in the power formula, n rays -> n-1 additions to the power.
     *
     * This function gives the electrical field, generated by one MPC, at the receiver. The electric field is // to the dipole antenna since we only consider relections
     * off the buildings. The electric field is not // for the reflexion with the ground though. This is taken into account in the function computePrx.
     */

    complex <double> i(0.0, 1.0);
    int amountSegment = rayLine.size();
    double completeLength = 0.0;
    double theta = 0.0;
    double R = 1;
    complex <double> Efield = 0.0;
    ray *currentRay;
    for (int i=0; i<amountSegment; i++){
        currentRay = rayLine.at(i);
        theta = currentRay->getTheta();
        if((i != amountSegment-1)){   // The last segment, the one that reach the receptor does not have a rebound
            double thetaI = abs(currentRay->getTetai());
            R *= computeReflexionPer(thetaI,epsilonWallRel);
        }
        completeLength += currentRay->getMeterLength(); // Get each length of each ray segment after the meter conversion (1px == 1dm)
    }
    double Ia = sqrt(2.0*powerEmettor/Ra); // Ia could be changed for Beamforming application (add exp)
    double a = R * ((Zvoid*Ia)/(2.0*M_PI))/completeLength;
    Efield = i * a * exp(-i*(2.0*M_PI/lambda)*completeLength);

    if(amountSegment==1){
        this->minLength = completeLength; // for delay spread computation
        this->LOS = pow(a,2);
    } else{
        this->NLOS += pow(a,2); 
    }
    if(completeLength > this->maxLength){
        this->maxLength = completeLength; // for delay spread computation
    } 
    // Store ray parameter for Physical impulse response
    if(computePhysicalResponse){
        // Store attenuation a and distance completeLength 
        channelData[rayNumber] = R/completeLength;
        channelData[rayNumber+20] = completeLength;
        double degangle = round((theta+direction)*180/M_PI);
        double radangle = degangle*M_PI/180;
        spectrumField[specNumber] = Efield;
        spectrumAngle[specNumber] = (2.0*M_PI/lambda)*speedReal*cos(radangle);
        int save = specNumber;
        for (int j = 0; j < save; j++){
            if (spectrumAngle[j] == spectrumAngle[save]){
                spectrumField[j] += Efield;
                specNumber -= 1;
            }
        }
        specNumber += 1;
        rayNumber += 1;
    }
    return Efield;
}

complex <double> room::computeEfieldGround(){
    // Compute the electrical field, at the receiver, induced by the ray reflected off the ground.
    // To Do: check if there is a wall between the TX and RX
    double distance = this->distance(); // conversion (1px == 2cm)
    double thetaG = atan((distance/2)/antennaHeight);
    double thetaI = M_PI - thetaG;
    double R = computeReflexionPar(thetaG,epsilonWallRel);
    double completeLength = distance/sin(thetaG);
    if(completeLength > this->maxLength) this->maxLength = completeLength; // for delay spread computation
    complex <double> i(0.0, 1.0);
    double Ia = sqrt(2*powerEmettor/Ra); // Ia could be changed for Beamforming application
    double a = R * ((Zvoid*Ia)/(2*M_PI)) * (cos(M_PI/2*cos(thetaI))/sin(thetaI))/completeLength;
    complex <double> Efield = i * a * exp(-i*(2.0*M_PI/lambda)*completeLength);
    this->NLOS += pow(a,2);

    // Store ray parameter for Physical impulse response
//    if(computePhysicalResponse){
//        // Store attenuation a and distance completeLength
//        channelData[rayNumber] = R/completeLength;
//        channelData[rayNumber+20] = completeLength;
//        rayNumber += 1;
//    }

    return Efield;
}

double room::computePrx(complex <double> totalEfield){
    // Compute the power at the receive antenna with the total electric field induced by all MPC
    complex <double> groundEfield = this->computeEfieldGround(); // Compute the electrical field from the ray reflected off the ground
    double distance = this->distance();
    double thetaI = atan(antennaHeight/(distance/2))+M_PI/2;
    complex <double> Voc = (lambda/M_PI)*(totalEfield + groundEfield*(cos(M_PI/2*cos(thetaI))/sin(thetaI)));
    double Prx = 1/(8*Ra)*norm(Voc);
    return Prx;
}

double room::computeSNR(double Prx){
    /*
        Compute the SNR [dB] with Prx given in dBm.
    */
    double SNR = (Prx-30) - noiseFigure - inputNoise;
    return SNR;
}

double room::diffractedRayPower(ray* rayReceiver, ray* rayTransmitter){

    // Direct distance between the receiver and the transmitter
    double direct_dist = sqrt(pow(Transmitter->getPosX()-m_Receiver->getPosX(),2) + pow(Transmitter->getPosY()-m_Receiver->getPosY(),2)); //convertir px to cm?
    cout << "direct distance: " << direct_dist << endl;
    // The vactor that will contain the direct ray.
    //vector<ray*> rayLine;
    //rayLine.clear();

    complex<double> Efield =0.0;

    // The length defference between the path going through the tip of the obstacle, and the direct path.

    double delta_r = (rayReceiver->length()+rayTransmitter->length() - direct_dist)*pow(10, -1.0);
    cout << "length rx: " << rayReceiver->length() << endl;
    cout << "length tx: " << rayTransmitter->length() << endl;
    cout << "delta_r: " << delta_r << endl;

    double nu = sqrt(2*2*M_PI/lambda*delta_r/M_PI);
    cout << "nu: " << nu << endl;
    // The ITU's approximation for |F(nu)|^2
    double FresnelPowerdB = -6.9 - 20*log10(sqrt(pow(nu-0.1,2)+1)+nu-0.1);
    cout << "dB Fresnel: " << FresnelPowerdB << endl;
//    double FresnelPowerdB = 6.9 + 20*log10(sqrt(pow(nu-0.1,2)+1)+nu-0.1);
    double FresnelPower = pow(10,FresnelPowerdB/20);
    cout << "Fresnel: " << FresnelPower << endl;
//    double fresnelPowerW = pow(10,FresnelPower/20);
    //double fresnelNorm = sqrt(-6.9 - 20*log10(sqrt(pow(nu-0.1,2)+1)+nu-0.1));
//    double fresnelNorm = sqrt(fresnelPowerW);
//    double fresnelArg = -(M_PI/4)-(M_PI/2)*pow(nu,2);
//    double fresnelArg = -(1/4)-(1/2)*pow(nu,2);
//    complex <double> fresnelCoef = fresnelNorm*exp(fresnelArg);
//    complex <double> fresnelCoef = (fresnelNorm*cos(M_PI*fresnelArg),fresnelNorm*sin(M_PI*fresnelArg));
//    norm(fresnelCoef) = fresnelNorm;
//    arg(fresnelCoef) = fresnelArg;
    ray* directRay = new ray(m_Receiver->getPosX(),m_Receiver->getPosY(),Transmitter->getPosX(),Transmitter->getPosY(),0,0);
    //rayLine.push_back(directRay);
    //Efield = computeEfield(rayLine);
//    double G = Zvoid/(pow(M_PI, 2)*Ra);
    //Efield = (sqrt(60*G*powerEmettor)/directRay->getMeterLength());  // we can add the phase if we want to take into account the interraction between MPCs
    complex <double> i(0.0, 1.0);
    double Ia = sqrt(2*powerEmettor/Ra); // Ia could be changed for Beamforming application (add exp)
    Efield =-i  * ((Zvoid*Ia)/(2*M_PI)) * (exp(-i*(2.0*M_PI/lambda)*directRay->getMeterLength())/directRay->getMeterLength());
    double power = 1/(8*Ra)*norm((lambda/M_PI)*Efield)*FresnelPower;
    cout << "power: " << power << endl;

//    totalEfield += Efield*fresnelCoef;

    delete(directRay);
    return power;
}


// --> Telecom calculation tools ---------------------------------------------------------------------------------------------------------------------------


double room::binaryDebit(double power){

    /* Given two extreme situations, let us write a linear relation between the power received/sensibility to the binary Debit of informations, knowing two points :
     *
     * -93dBm  -- 6Mb/s
     * -73dBm  -- 54Mb/s
     *
     * we have for y = ax + b the line equation (y being the binary debit and x the power in dBm
     * a = 12/5 and b = 1146/5, and thus
     */
    double logBinaryDebit;

    //if(power<= -93){logBinaryDebit = 6;}
    //else if(power >=-73){logBinaryDebit = 56;}
    //else{

    //double a = 12/5;
    double a = 2.4;
    //double b = 1146/5;
    double b = 229.2;
    logBinaryDebit = a*power + b;
    //}
    if(logBinaryDebit<0){logBinaryDebit=0;}

   return logBinaryDebit;
}


// dBm to watts and watts to dBm conversion
double room::dB(double power){return 10*(log10(power));}
double room::dBm(double power){return 10*(log10(power)) + 30.0;}
double room::dBmRev(double dbm){return pow(10, -3)*pow(10, (dbm/10));}


// --> Miscellaneous ------------------------------------------------------------------------------------------------------------------------------


void room::clearAll(){
    clearLocalParameters();
    allRays.clear(); // Empty all previously calculated vectors
}

void room::clearLocalParameters(){
    totalEfield = 0.0;
    resultsBinaryDebit = 0.0;
    powerReceived = 0.0;
    SNR = 0.0;
    powerRef = 0.0;
    minLength = 0.0;
    maxLength = 0.0;
    LOS = 0.0;
    NLOS = 0.0;
    rayNumber = 0;
    specNumber = 0;
    //coverageDone = false;

    //Efield = 0.0;
}

void room::clearPenDepth(){
    for(int i = 0; i<5;i++){
        stDepth[i]=0;
    }
}


void room::readSettingsFile(){
    /*
     * Takes all problems parameters from the data file in /settings.txt, this will be changed in the settings menu if the user changes it
     */

    ifstream settingsData;
    settingsData.open("settings.txt");

    string line;
    int count =0;
    if (settingsData.is_open())
    {
      while (getline(settingsData,line))
      {
          if(count == 0){
              int wallType = stoi(line);

              if(wallType == 0){
                    wallSigma = 0.02;    // bricks
                    epsilonWallRel = 4.6;

              } else if(wallType == 1){
                    wallSigma = 0.014;   // Concrete
                    epsilonWallRel = 5;

              } else if( wallType == 2){
                    wallSigma = 0.04;    // Separators
                    epsilonWallRel = 2.25;
              }

          }else if(count == 1){
              reflectionsNumber = stoi(line);
          }else if(count == 2){
              wallThickness = stod(line);
          }else if(count == 3){
                square_size = stoi(line);
                rows = 500/square_size; // 950 = window width
                columns = 950/square_size; // 500 = window height
                totalArea = rows * columns; // total number of local area
          }else if(count == 4){
                //powerEmettor = stod(line);
          }else if(count == 5){
                 speed = stod(line);
                 speedReal = speed/3.6;
          }else if(count == 6){
              int dir = stoi(line);
              if (dir == 0){
                  direction = 0;
              }
              else if (dir == 1){
                  direction =-M_PI;
              }
              else if (dir == 2){
                  direction =M_PI/2;
              }
              else if (dir == 3){
                  direction =-M_PI/2;
              }
          }
          count++;
      }
      settingsData.close();
    }
}


float room::distance(){

    /*
     * For display, it calcultes the direct Euclidian distance from the receiver to the emettor, displays the results on the UI
     */

    // QGraphicsLineItem* dist ;

    int x1 = Transmitter->getPosX();
    int y1 = Transmitter->getPosY();
    int x2 = m_Receiver->getPosX();
    int y2 = m_Receiver->getPosY();

    // dist = new QGraphicsLineItem(x1,y1,x2,y2,NULL);
    // //this->addItem(dist);

    // QPen outlinePen(Qt::green);
    // outlinePen.setWidth(2);
    // dist->setPen(outlinePen);

    return sqrt(pow((x2-x1),2)+pow((y2-y1),2))*this->pxToMeter; // conversion (1px == 1dm)
}

// --> Getters and Setters ----------------------------------------------------------------------------------------------------------------


antena* room::getReceiver(){return m_Receiver;}
antena* room::getTransmitter(){return Transmitter;}
double room::getReceivedPower(){return powerReceived;}
Wall* room::getWalls(int i){return walls[i];}
int room::getAmountWalls(){return amount_walls;}
double room::getBinaryDebit(){return resultsBinaryDebit;}
int room::getAmountDiscret(){return amount_discret;}
double room::getpowerEmettor(){return powerEmettor;}
double room::getInitBinaryDeb(){return binaryDebit(powerEmettor);}
complex <double> room::getTotalEfield(){return totalEfield;}
double room::getCarrierFrequency(){return freq;}
double room::getBandwidth(){return BW;}
double room::getMinPrx(){return minPrx;}

void room::setReceiver(antena *new_receiver){m_Receiver = new_receiver;}
void room::setTransmitter(antena *new_transmitter){Transmitter = new_transmitter;}
int room::getRows(){return rows;}
int room::getColumns(){return columns;}
int room::getTotalArea(){return totalArea;}
double room::getSpeed(){return speed;}
double room::getSpeedReal(){return speedReal;}
int room::getMinimalDistance(){return minimalDistance;}
int room::getSquare_size(){return square_size;}
double room::getPxToMeter(){return pxToMeter;}
double* room::getData(){return this->Data;}
int room::getRayNumber(){return this->rayNumber;}
int room::getSpecNumber(){return this->specNumber;}
double* room::getChannelData(){return this->channelData;}
complex <double> * room::getSpectrumField(){return this->spectrumField;}
double* room::getSpectrumAngle(){return this->spectrumAngle;}
double room::getDirection(){return direction;}
map<const char *, int> *room::getStreetsPenDep(){return &(this->streetsPenDep);}
double room::getLambda(){return lambda;}
double room::getRa(){return Ra;}
double room::getCoTime(){return 1.0/2.0*lambda/speedReal*1e+6;}
QPoint room::getMousePosition()const{
    return mousePosition;
}
float* room::getStPenetrationDepth(){return stDepth;}

// ---> Events listeners ----------------------------------------------------------------------------------------------------------------



void room::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (antenaType == 0){
        if (Transmitter != NULL){
            delete Transmitter;
            Transmitter = NULL;};

        Transmitter = new antena(/*this,*/ event->scenePos(),antenaType);
        //Transmitter->setSceneBoundary(sceneRect());
        Transmitter->setSceneBoundary(itemsBoundingRect());


        this->addItem(Transmitter);
    }

    else if (antenaType == 1){
        if (m_Receiver != NULL){
            delete m_Receiver;
            m_Receiver = NULL;};

        m_Receiver = new antena(/*this,*/ event->scenePos(),antenaType);
        this->addItem(m_Receiver);
        m_receiver = new Receiver(event->scenePos(),this);
        m_receiver->addAntenaImage(Transmitter);
        Transmitter->setReceiver(m_receiver);
    }
    QGraphicsScene::mousePressEvent(event);
}

void room::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QPointF pos = event->scenePos();
    mouseScenePosition(pos);
    QGraphicsScene::mouseMoveEvent(event);
}

void room::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    antenaType = 2;
    QGraphicsScene::mouseReleaseEvent(event);
}

void room::setMode(Mode mode){
    m_mode = mode;
}

void room::addToScene(QGraphicsItem *item){
    addItem(item);
}


//---> Draw the heatmap-------------------------------------------------------------------------------------------------------------------


void room::drawCoverege(){
    this->clearAll();
    if(m_Receiver !=NULL){
        delete m_Receiver;
        m_Receiver = NULL;
    }
    if(coverageDone) free(Data);
    m_Receiver = new antena(/*this,*/QPointF(0,0),1);
    //QBrush brush;
    QBrush *brush = new QBrush(QColor(0, 0, 0, 220));
    QPen pen;
    pen.setColor(QColor(0,0,0,0));
    QColor color;
    
    this->Data = (double *)calloc(totalArea * 5, sizeof(double));
    if (!this->Data) {
        printf("mem failure, exiting \n");
        exit(EXIT_FAILURE);
    }
//    cout<<"Ptx[W] = ";
//    cout<<powerEmettor<<endl;
    for(int i=0; i<columns; i++){
        for(int j=0; j<rows; j++){
            this->clearLocalParameters();
            double xRece = square_size/2 + i*square_size;
            double yRece = square_size/2 + j*square_size;

            m_Receiver->setPosi(QPointF(xRece,yRece));
            launch_algo(false);
            this->Data[i*rows+j] = (powerReceived); // Received Power[dBm]
            this->Data[i*rows+j+totalArea] = abs(maxLength-minLength)/c; // Delay Spread
            this->Data[i*rows+j+totalArea*2] = 10*log10(LOS/NLOS); // Rice factor
            this->Data[i*rows+j+totalArea*3] = this->distance(); // Distance from TX
            this->Data[i*rows+j+totalArea*4] = this->computeSNR(powerReceived); // Compute SNR from Prx in dBm

            // Plot results
            // Change binaryDebit which is different for 5G
            //if(250 - 250*resultsBinaryDebit/250>=0){color.setHsv((250 - 250*resultsBinaryDebit/250),255,105 + resultsBinaryDebit*150/260,255);}
            if((-20 - powerReceived)*3>=0){color.setHsv((-20 - powerReceived)*3,255,255 - (-20 - powerReceived),255);}
            else if(powerReceived == 0){
                color.setHsv(240,150,80,255);
            }
            else{color.setHsv(0,255,255,255);}
            brush->setColor(color);
            this->addRect(i*square_size,j*square_size,square_size,square_size,pen,*brush);
        }
    }
    cout<< "Rue du Commerce Up: ";
    cout<< streetsPenDep["commerceUp"]<<endl;
    cout<< "Rue du Commerce Down: ";
    cout<< streetsPenDep["commerceDown"]<<endl;
    cout<< "Rue de deux Eglises: ";
    cout<< streetsPenDep["deuxEg"]<<endl;
    cout<< "Rue de Spa: ";
    cout<< streetsPenDep["spa"]<<endl;
    cout<< "Rue de l'Industrie: ";
    cout<< streetsPenDep["indu"]<<endl;
    cout<< stDepth<<endl;
    //this->myParent->writePenetrationDepth(stDepth);
    drawWalls();
    this->clearAll();
    coverageDone = true;
}

bool room::DataComputed(){
    return coverageDone;
}

void room::getDataIndices(int posX, int posY, int &index_i, int &index_j){
    // Find the indices in the array Data that correspond to the mouse position 
    index_i = (int)(posX/square_size);
    index_j = (int)(posY/square_size);
}

void room::getTxIndices(int &index_i, int &index_j){
    // Find the indices in the array Data that correspond to the TX position 
    index_i = (int)(Transmitter->getPosX()/square_size);
    index_j = (int)(Transmitter->getPosY()/square_size);
}

//---> Minimal results for local area-------------------------------------------------------------------------------------------------------------------
double room::getDelay_local(){
    // Delay spread
    return abs(maxLength-minLength)/c;
}

double room::getCoherenceBandwidth_local(){
    return (1/this->getDelay_local());
}

double room::getRiceFactor_local(){
    return 10*log10(LOS/NLOS);
}

double room::getSNR_local(){
    return computeSNR(powerReceived);
}

double room::getPrx(int i, int j){
    // Narrowband receive power
    double Prx = this->Data[i*rows+j];
    return Prx;
}

double room::getDelay(int i, int j){
    // Delay spread
    double delay = this->Data[i*rows+j+totalArea];
    return delay;
}

double room::getCoherenceBandwidth(int i, int j){
    return (1/this->getDelay(i,j));
}

double room::getRiceFactor(int i, int j){
    double K = this->Data[i*rows+j+totalArea*2];
    return K;
}

double room::getDistance(int i, int j){
    double distance = this->Data[i*rows+j+totalArea*3];
    return distance;
}

double room::getSNR(int i, int j){
    double SNR = this->Data[i*rows+j+totalArea*4];
    return SNR;
}

void room::draw(QGraphicsItem *item){
    addItem(item);
    update();
}

void room::drawRays(vector<ray> *rays){
    for(int j = 0;j<rays->size();j++){
        QGraphicsLineItem *graphicsRay = new QGraphicsLineItem(rays->at(j));
        addItem(graphicsRay);
        m_rays.push_back(graphicsRay);
    }
}

void room::clearRays(){
    foreach(QGraphicsLineItem* ray, m_rays){
        removeItem(ray);
        delete (ray);
    }
    m_rays.clear();
    m_rays.shrink_to_fit();
}

//void room::mouseScenePos(QPointF &pos){

//}

//void room::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{   QPointF x = event->scenePos();
//    mousePosition = x.toPoint();
//    //myParent->onMouseEvent("ll",X);
//}
