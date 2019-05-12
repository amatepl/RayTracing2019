#include "room.h"
//#include "plots.h"


using namespace std;

room::room(MainWindow *parent) :
    QGraphicsScene(parent)
  //, QImage(1000,1000, QImage::Format_RGB32)
{   myParent = parent;

    readSettingsFile();

    antenaType = 2; // 0 for transmitter 1 for receiver 2 for nothing
    Transmitter = NULL;
    Receiver = NULL;

    // Absolute electric permittivity
    //eps = epsilonAir*epsilonWallRel;

    // impedance of the wall
    //Zwall = sqrt((muAir/eps));

    // Propagation constants for small-loss hypothesis
    // alpha = 2*M_PI*freq*sqrt((muAir*eps)/2)*sqrt((sqrt(1 + pow((wallSigma/(2*M_PI*freq*eps)), 2)) -1 ));
    // beta = 2*M_PI*freq*sqrt((muAir*eps)/2)*sqrt((sqrt(1 + pow((wallSigma/(2*M_PI*freq*eps)), 2)) + 1 ));

    // gamma = alpha + i*beta;

    // Let us define the walls and draw the view

    //Building 1
    walls[0] = new wall(200,1,200,200, 0.0, 0.0, 0.0, 0);
    walls[18] = new wall(200,1,1,1, 0.0, 0.0, 0.0, 18);
    walls[1] = new wall(200,200,1,200, 0.0, 0.0, 0.0, 1);
    walls[19] = new wall(1,200,1,1, 0.0, 0.0, 0.0, 19);

    //Building 2
    walls[2] = new wall(250, 1, 250, 200, 0.0, 0.0, 0.0, 2);
    walls[3] = new wall(250, 200, 450, 200, 0.0, 0.0, 0.0, 3);
    walls[4] = new wall(450, 200, 450, 1, 0.0, 0.0, 0.0, 4);
    walls[20] = new wall(450, 1, 250, 1, 0.0, 0.0, 0.0,20);

    //Building 3
    walls[5] = new wall(500, 1, 500, 200, 0.0, 0.0, 0.0, 5);
    walls[6] = new wall(500, 200, 700, 200, 0.0, 0.0, 0.0, 6);
    walls[7] = new wall(700, 200, 700, 1, 0.0, 0.0, 0.0, 7);
    walls[21] = new wall(700, 1, 500, 1, 0.0, 0.0, 0.0, 21);

    //Building 4
    walls[8] = new wall(750, 1, 750, 200, 0.0, 0.0, 0.0, 8);
    walls[9] = new wall(750, 200, 950, 200, 0.0, 0.0, 0.0, 9);
    walls[10] = new wall(950, 200, 950, 1, 0.0, 0.0, 0.0, 10);
    walls[22] = new wall(950, 1, 750, 1, 0.0, 0.0, 0.0, 22);

    //Building 5
    walls[11] = new wall(200, 300, 200, 500, 0.0, 0.0, 0.0, 11);
    walls[23] = new wall(200, 500, 1, 500, 0.0, 0.0, 0.0, 23);
    walls[24] = new wall(1, 500, 1, 300, 0.0, 0.0, 0.0, 24);
    walls[12] = new wall(1, 300, 200, 300, 0.0, 0.0, 0.0, 12);

    //Building 6
    walls[13] = new wall(250, 300, 250, 500, 0.0, 0.0, 0.0, 13);
    walls[25] = new wall(250, 500, 600, 500, 0.0, 0.0, 0.0, 25);
    walls[14] = new wall(600, 500, 600, 300, 0.0, 0.0, 0.0, 14);
    walls[15] = new wall(600, 300, 250, 300, 0.0, 0.0, 0.0, 15);

    //Building 7
    walls[16] = new wall(650, 300, 650, 500, 0.0, 0.0, 0.0, 16);
    walls[26] = new wall(650, 500, 950, 500, 0.0, 0.0, 0.0, 26);
    walls[27] = new wall(950, 500, 950, 300, 0.0, 0.0, 0.0, 27);
    walls[17] = new wall(950, 300, 650, 300, 0.0, 0.0, 0.0, 17);

    drawWalls();
    //findDiffractionPoints();

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


bool room::workingZone(){
    int Rx = Receiver->getPosX();
    int Ry = Receiver->getPosY();

//    int Tx = Receiver->getPosX();
//    int Ty = Receiver->getPosY();
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


    for(unsigned int i = 0;i<amount_walls;i++){
        for(unsigned int j = 0;j<amount_walls;j++){
            if(walls[i]->getIndWall() != walls[j]->getIndWall()){
                if(pointOnLine(walls[j],walls[i]->getX1(),walls[i]->getY1())){
                    bool check = true;
                    unsigned int c = 0;
                    while(c<diffractionPoints.size()&& check){
                        check = (diffractionPoints[c][0] != walls[i]->getX1() || diffractionPoints[c][1] != walls[i]->getY1());
                        c++;    cout<<(double)950/500<<endl;
                    }

                    if(check){diffractionPoints.push_back({walls[i]->getX1(),walls[i]->getY1()});}
                }
                else if(pointOnLine(walls[j],walls[i]->getX2(),walls[i]->getY2())){
                    bool check = true;
                    unsigned int c = 0;
                    while(c<diffractionPoints.size()&& check){
                        check = (diffractionPoints[c][0] != walls[i]->getX2() || diffractionPoints[c][1] !=walls[i]->getY2());
                        c++;
                    }

                    if(check){diffractionPoints.push_back({walls[i]->getX2(),walls[i]->getY2()});}
                }
            }
        }
    }
}


void room::drawWalls(){
    QPen outlinePen(QColor(0, 0, 0, 255));
    outlinePen.setWidth(2);
    for(int i = 0;i<amount_all_walls;i++){
        this->addLine(walls[i]->getX1(),walls[i]->getY1(),walls[i]->getX2(),walls[i]->getY2(),outlinePen);
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

    if(!workingZone()){
        // Calculate power -- Reflexion and transmission

        current_ray = new lineo(Receiver->getPosX(),Receiver->getPosY(),Transmitter->getPosX(),Transmitter->getPosY());
        bool reflection = true;
        unsigned int i = 0;
        while(i<amount_walls && reflection){
            reflection = !intersectionCheck(current_ray,walls[i]);
            i++;
        }
        delete(current_ray);

        if(drawR){
            if(reflection){recursion(Transmitter->getPosX(), Transmitter->getPosY(),Receiver->getPosX(),Receiver->getPosY(),reflectionsNumber,drawRay);}
            else{
                drawDiffraction(this);}
        }
        else{
            if(reflection){recursion(Transmitter->getPosX(), Transmitter->getPosY(),Receiver->getPosX(),Receiver->getPosY(),reflectionsNumber, buildRay);}
            else{buildDiffraction((this));}
        }
        //cout<<diffractedPower<<endl;
        //if(diffractedPower !=0){power = power + dBmRev(diffractedPower);}

        //if(diffractedPower !=0){powerRef = powerRef + dBmRev(diffractedPower);}
        if(reflection){
            powerRef = computePrx(totalEfield);
            //cout<<"power: ";
            //cout<<powerRef<<endl;
            powerReceived = dBm(powerRef);
        }
        if(powerReceived){
            resultsBinaryDebit = binaryDebit(powerReceived);
        }
    }
}


// ------------------------------ Image method ------------------------------------------------


void room::recursion(double transmitterPosX, double transmitterPosY, double receiverPosX, double receiverPosY, int numberOfReflections,void (*draw)(double, double, double, double,room*)){

    /*
     * The recursion method generalize the image method for any amount of reflections. Keeps track of the depth of the recursive algorithm.
     * Calls drawRay and stores the rays as they are being created.
     */

    transmitterSerie[recursionState][0] = transmitterPosX;
    transmitterSerie[recursionState][1] = transmitterPosY;

    lineo* current_wall = wallRecursiveNumber[recursionState];

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

                angle_wall = current_wall->getAngle();

                //------------TRANSMITTER IMAGE CONSTRUCTION--------------------------

                double ray_vector_length = sqrt(pow(transmitterPosY - current_wall->getY2(),2) + pow(transmitterPosX - current_wall->getX2(),2));
                double virtual_slope;

                if (transmitterPosY - current_wall->getY2() < 0 && transmitterPosX - current_wall->getX2()){
                    virtual_slope = -acos((transmitterPosX - current_wall->getX2())/ray_vector_length);
                }

                else{
                    virtual_slope = acos((transmitterPosX - current_wall->getX2())/ray_vector_length);
                }

                double ray_slope = angle_wall + (angle_wall - virtual_slope);
                double ray_vector[2] ={cos(ray_slope) , sin(ray_slope)};
                double x2 = ray_vector_length * ray_vector[0];
                double y2 = ray_vector_length * ray_vector[1];
                double transmitterImagePosX = current_wall->getX2() + x2;
                double transmitterImagePosY = current_wall->getY2() + y2;

                //---------END OF TRANSMITTER IMAGE CONSTRUCTION--------------------------

                current_ray = new lineo(transmitterImagePosX, transmitterImagePosY,receiverPosX,receiverPosY);
                imCoordinates[0] = intersection(current_ray,current_wall)[0];
                imCoordinates[1] = intersection(current_ray,current_wall)[1];
                delete(current_ray);
                //if(pointOnLine(current_wall,imCoordinates[0],imCoordinates[1]) && pointOnLine(current_ray,imCoordinates[0],imCoordinates[1])){
                    recursion(transmitterImagePosX, transmitterImagePosY,receiverPosX,receiverPosY,NumberOfReflections - 1,draw);
                //}

            }

        if(i == amount_walls - 1){recursionState -=1;}
        }
    }
}



void room::drawRay(double transmitterPosX,double transmitterPosY,double originX,double originY,room* scene){

    /*
     * Called back from the recursion method, draws the rays when necessary, then removes the excess
     */

    // Freeing memory
    vector <ray*> completeRay;
    completeRay.clear();
    lineo *current_ray;
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

        wall* walle = (*scene).wallRecursiveNumber[(*scene).recursionState -j];
        transmitterPosX = (*scene).transmitterSerie[(*scene).recursionState-j][0];
        transmitterPosY = (*scene).transmitterSerie[(*scene).recursionState-j][1];
        current_ray= new lineo(transmitterPosX,transmitterPosY,originX,originY);

        // To get rid of this if the original transmitter has to be added to the transmitterSrerie
        if(j != (*scene).recursionState){

            double imageCoordinates[2] = {(*scene).intersection(current_ray,walle)[0],(*scene).intersection(current_ray,walle)[1]};

            if((*scene).pointOnLine(walle,imageCoordinates[0],imageCoordinates[1]) && (*scene).pointOnLine(current_ray,imageCoordinates[0],imageCoordinates[1])){

                receiver_ray = new ray(imageCoordinates[0],imageCoordinates[1],originX,originY,M_PI/2 - abs(abs(current_ray->getAngle())-abs(walle->getAngle())),walle->getIndWall());

                completeRay.push_back(receiver_ray);
                originX = imageCoordinates[0];
                originY = imageCoordinates[1];
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
            current_ray = new lineo(receiver_ray->getX1(),receiver_ray->getY1(),receiver_ray->getX2(),receiver_ray->getY2());

            if((*scene).intersectionCheck(current_ray,(*scene).walls[j])&& !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->getX2(), completeRay[i]->getY2()) && !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->getX1(), completeRay[i]->getY1())){
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
            scene->addLine(completeRay[i]->getX1(),completeRay[i]->getY1(),completeRay[i]->getX2(),completeRay[i]->getY2(),outlinePen);
//            cout<<"Ray's slope: ";
//            cout<<completeRay[i]->getSlope()<<endl;
//            cout<<"Intersection x: ";
//            cout<<(*scene).intersection(completeRay[i],(*scene).walls[4])[0]<<endl;
//            cout<<"Intersection y: ";
//            cout<<(*scene).intersection(completeRay[i],(*scene).walls[4])[1]<<endl;
//            cout<<"Intersection bool: ";
//            cout<<(*scene).intersectionCheck(completeRay[i],(*scene).walls[4])<<endl;
//            cout<<"Ray reflects on wall start: ";
//            cout<<(*scene).pointOnLine((*scene).walls[4],completeRay[i]->getX1(),completeRay[i]->getY1())<<endl;
//            cout<<"Ray reflects on wall end: ";
//            cout<<(*scene).pointOnLine((*scene).walls[4],completeRay[i]->getX2(),completeRay[i]->getY2())<<endl;

            cout<<"x1 and y1: ";
            cout<<completeRay[i]->getX1();
            cout<<", ";
            cout<<completeRay[i]->getY1()<<endl;

            cout<<"x2 and y2: ";
            cout<<completeRay[i]->getX2();
            cout<<", ";
            cout<<completeRay[i]->getY2()<<endl;
            cout<<"--------------------------"<<endl;
            i++;
        }
        (*scene).totalEfield += scene->computeEfield(completeRay);

        delete(receiver_ray);
        completeRay.clear();
        completeRay.shrink_to_fit();

//        cout<<"Ray's power: ";
//        cout<< (*scene).power<<endl;
    }

}

///////////////////////////////build///////////////////////////////

void room::buildRay(double transmitterPosX,double transmitterPosY,double originX,double originY,room* scene){

    /*
     * Called back from the recursion method, draws the rays when necessary, then removes the excess
     */

    // Freeing memory
    vector <ray*> completeRay;
    completeRay.clear();
    lineo *current_ray;
    ray* receiver_ray;

    unsigned char j = 0;
    while(j<=(*scene).recursionState){

        /*
         * We need to check if our rays reflects on the right walls. For that purpouse we check the
         * intersection of the last ray component with the wall that was used to build the transmitter image.
        */

        wall* walle = (*scene).wallRecursiveNumber[(*scene).recursionState -j];
        transmitterPosX = (*scene).transmitterSerie[(*scene).recursionState-j][0];
        transmitterPosY = (*scene).transmitterSerie[(*scene).recursionState-j][1];
        current_ray= new lineo(transmitterPosX,transmitterPosY,originX,originY);

        // To get rid of this if the original transmitter has to be added to the transmitterSrerie
        if(j != (*scene).recursionState){

            double imageCoordinates[2] = {(*scene).intersection(current_ray,walle)[0],(*scene).intersection(current_ray,walle)[1]};

            if((*scene).pointOnLine(walle,imageCoordinates[0],imageCoordinates[1]) && (*scene).pointOnLine(current_ray,imageCoordinates[0],imageCoordinates[1])){

                receiver_ray = new ray(imageCoordinates[0],imageCoordinates[1],originX,originY,M_PI/2 - abs(abs(current_ray->getAngle())-abs(walle->getAngle())),walle->getIndWall());
                delete(current_ray);
                completeRay.push_back(receiver_ray);
                originX = imageCoordinates[0];
                originY = imageCoordinates[1];

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
            current_ray = new lineo(receiver_ray->getX1(),receiver_ray->getY1(),receiver_ray->getX2(),receiver_ray->getY2());
            if((*scene).intersectionCheck(current_ray,(*scene).walls[j])&& !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->getX2(), completeRay[i]->getY2()) && !(*scene).pointOnLine((*scene).walls[j], completeRay[i]->getX1(), completeRay[i]->getY1())){
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
    lineo* pathTester;
    lineo* pathTester2;

    //Actual rays that we chould obtein when the diffracation happens.
    ray* rayReceiver;
    ray* rayTransmitter;

    (*scene).diffractionPoints.clear();

    pathTester = new lineo((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).Receiver->getPosX(),(*scene).Receiver->getPosY());
    bool notDiffracted = true;          // Since only one diffracation is allowed this parameter will stop the loop when it happens.
    unsigned int i = 0;
    while(i<(*scene).amount_all_walls && notDiffracted){
        // First we check if the direct ray intersects with any wall. If no then there is on diffraction.
        if((*scene).intersectionCheck(pathTester,(*scene).walls[i])){
            pathTester2 = new lineo((*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),(*scene).Receiver->getPosX(),(*scene).Receiver->getPosY());
            bool check = true;
            unsigned int j = 0;
            while(j<(*scene).amount_all_walls && check){
                check = !(*scene).intersectionCheckNonInclusive(pathTester2,(*scene).walls[j]);
                j++;
            }
            delete(pathTester2);
            pathTester2 = new lineo((*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),(*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY());
            j =0;
            while(j<(*scene).amount_all_walls && check){
                check = !(*scene).intersectionCheckNonInclusive(pathTester2,(*scene).walls[j]);
                j++;
            }
            if(check){
                scene->addLine((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),outlinePen);
                scene->addLine((*scene).Receiver->getPosX(),(*scene).Receiver->getPosY(),(*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),outlinePen);
                rayReceiver = new ray((*scene).Receiver->getPosX(),(*scene).Receiver->getPosY(),(*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),0,0);
                rayTransmitter = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),0,0);
                double diffractPower = (*scene).diffractedRayPower(rayReceiver,rayTransmitter);
                (*scene).powerRef = diffractPower;
                (*scene).powerReceived = (*scene).dBm(diffractPower);
                //(*scene).diffractedPower+= diffractPower;
                notDiffracted =false;
            }
            delete(pathTester2);
            pathTester2 = new lineo((*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),(*scene).Receiver->getPosX(),(*scene).Receiver->getPosY());
            j = 0;
            while(j<(*scene).amount_all_walls && !check){
                check = (*scene).intersectionCheckNonInclusive(pathTester2,(*scene).walls[j]);
                j++;
            }
            delete(pathTester2);
            pathTester2 = new lineo((*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),(*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY());
            j=0;
            while(j<(*scene).amount_all_walls && !check){
                check = (*scene).intersectionCheckNonInclusive(pathTester2,(*scene).walls[j]);
                j++;
            }
            if(!check){
                scene->addLine((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),outlinePen);
                scene->addLine((*scene).Receiver->getPosX(),(*scene).Receiver->getPosY(),(*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),outlinePen);
                rayReceiver = new ray((*scene).Receiver->getPosX(),(*scene).Receiver->getPosY(),(*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),0,0);
                rayTransmitter = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),0,0);
                double diffractPower = (*scene).diffractedRayPower(rayReceiver,rayTransmitter);
                (*scene).powerRef = diffractPower;
                (*scene).powerReceived = (*scene).dBm(diffractPower);
                //(*scene).diffractedPower+= diffractPower;
                delete(rayReceiver);
                delete(rayTransmitter);
                notDiffracted = false;
            }
            delete(pathTester2);

        }
        i++;
    }
    delete(pathTester);



//    int walls_indices[2];
//    int indice = 0;
//    int c = 0;
//    while(c<(*scene).amount_walls && indice<2){
//        if((*scene).intersectionCheck(pathTester,(*scene).walls[c])){
//            walls_indices[indice] = c;
//            indice += 1;
//        }
//        c++;
//    }
//    if(indice == 2){
//        wall* wall1 = (*scene).walls[walls_indices[0]];
//        wall* wall2 = (*scene).walls[walls_indices[1]];
//        if((wall1->getX1() == wall2->getX1() && wall1->getY1() == wall2->getY1()) || (wall1->getX1() == wall2->getX2() && wall1->getY1() == wall2->getY2())){
//            (*scene).diffractionPoints.push_back({wall1->getX1(),wall1->getY1()});
//        }
//        else if((wall1->getX2() == wall2->getX2() && wall1->getY2() == wall2->getY2()) || (wall1->getX2() == wall2->getX1() && wall1->getY2() == wall2->getY1())){
//            (*scene).diffractionPoints.push_back({wall1->getX2(),wall1->getY2()});
//        }
//        scene->addLine((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).diffractionPoints[0][0],(*scene).diffractionPoints[0][1],outlinePen);
//        scene->addLine((*scene).Receiver->getPosX(),(*scene).Receiver->getPosY(),(*scene).diffractionPoints[0][0],(*scene).diffractionPoints[0][1],outlinePen);
//        rayReceiver = new ray((*scene).Receiver->getPosX(),(*scene).Receiver->getPosY(),(*scene).diffractionPoints[0][0],(*scene).diffractionPoints[0][1],0,0);
//        rayTransmitter = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).diffractionPoints[0][0],(*scene).diffractionPoints[0][1],0,0);
//        double diffractPower = (*scene).diffractedRayPower(rayReceiver,rayTransmitter);
//        (*scene).diffractedPower+= diffractPower;
//    }
}


void room::buildDiffraction(room* scene){
    /* This function builds the diffracted ray and asks to calculate its power.
     * Only one diffraction is allowed for a given position of the transmitter and the receiver.
     */

    // Those will check the intersections with the walls.
    lineo* pathTester;
    lineo* pathTester2;

    //Actual rays that we chould obtein when the diffracation happens.
    ray* rayReceiver;
    ray* rayTransmitter;

    (*scene).diffractionPoints.clear();

    pathTester = new lineo((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).Receiver->getPosX(),(*scene).Receiver->getPosY());
    bool notDiffracted = true;          // Since only one diffracation is allowed this parameter will stop the loop when it happens.
    unsigned int i = 0;
    while(i<(*scene).amount_all_walls && notDiffracted){
        // First we check if the direct ray intersects with any wall. If no then there is on diffraction.
        if((*scene).intersectionCheck(pathTester,(*scene).walls[i])){
            pathTester2 = new lineo((*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),(*scene).Receiver->getPosX(),(*scene).Receiver->getPosY());
            bool check = true;
            unsigned int j = 0;
            while(j<(*scene).amount_all_walls && check){
                check = !(*scene).intersectionCheckNonInclusive(pathTester2,(*scene).walls[j]);
                j++;
            }
            delete(pathTester2);
            pathTester2 = new lineo((*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),(*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY());
            j =0;
            while(j<(*scene).amount_all_walls && check){
                check = !(*scene).intersectionCheckNonInclusive(pathTester2,(*scene).walls[j]);
                j++;
            }
            if(check){
                rayReceiver = new ray((*scene).Receiver->getPosX(),(*scene).Receiver->getPosY(),(*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),0,0);
                rayTransmitter = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).walls[i]->getX1(),(*scene).walls[i]->getY1(),0,0);
                double diffractPower = (*scene).diffractedRayPower(rayReceiver,rayTransmitter);
                (*scene).powerRef = diffractPower;
                (*scene).powerReceived = (*scene).dBm(diffractPower);
                //(*scene).diffractedPower+= diffractPower;
                notDiffracted =false;
            }
            delete(pathTester2);
            pathTester2 = new lineo((*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),(*scene).Receiver->getPosX(),(*scene).Receiver->getPosY());
            j = 0;
            while(j<(*scene).amount_all_walls && !check){
                check = (*scene).intersectionCheckNonInclusive(pathTester2,(*scene).walls[j]);
                j++;
            }
            delete(pathTester2);
            pathTester2 = new lineo((*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),(*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY());
            j=0;
            while(j<(*scene).amount_all_walls && !check){
                check = (*scene).intersectionCheckNonInclusive(pathTester2,(*scene).walls[j]);
                j++;
            }
            delete(pathTester2);
            if(!check){
                rayReceiver = new ray((*scene).Receiver->getPosX(),(*scene).Receiver->getPosY(),(*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),0,0);
                rayTransmitter = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),(*scene).walls[i]->getX2(),(*scene).walls[i]->getY2(),0,0);
                double diffractPower = (*scene).diffractedRayPower(rayReceiver,rayTransmitter);
                (*scene).powerRef = diffractPower;
                (*scene).powerReceived = (*scene).dBm(diffractPower);
                //(*scene).diffractedPower+= diffractPower;
                delete(rayReceiver);
                delete(rayTransmitter);
                notDiffracted = false;
            }

        }
        i++;
    }
    delete(pathTester);


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



std::vector<double> room::intersection(lineo* line1, lineo* line2){

   /*
    * Two-equations line system, determines the intersection point if it exists
    *    y = ax + b
    *    y = cx + d
    */

   std::vector<double> coord(2);

   double xpos;
   double ypos;

   long double a = line1->getSlope();
   double b = line1->getYorigin();
   long double c = line2->getSlope();
   double d = line2->getYorigin();

   if(a == INFINITY){
       xpos = line1->getX1();
       ypos = c * xpos + d;
   }

   else if(c == INFINITY){
       xpos = line2->getX1();
       ypos = a * xpos + b;
   }
   else{
   xpos = (d - b)/(a - c);
   ypos = (a * xpos) + b;
   }

   coord[0] = round(xpos);
   coord[1] = round(ypos);
   return coord;
}


//bool room::pointOnLine(lineo* line1, double x, double y){
bool room::pointOnLine(lineo* line1,const double xp,const double yp){
    /*
     * As the intersection is computed by lines equations, it is required to check whether or not the intersection is placed on the the wall line, an line
     * equation being define from [-INF, +INF]
     */

    int x1 = (int)line1->getX1();
    int y1 = (int)line1->getY1();
    int x2 = (int)line1->getX2();
    int y2 = (int)line1->getY2();

    bool answer = false;

    int x = xp;
    int y = yp;

    if(x1 == x2){   // Cas du mur vertical
        answer = ((y<y2 && y>y1) || ( y>y2 && y<y1)) && x == x1;
    }
    else if (y1 == y2){   // Cas du mur horizental
        answer = ((x>x2 && x<x1) || (x<x2 && x>x1)) && y == y1;
    }
    else {
       answer = ((x1<x && y1<y && x2>x && y2 >y) ||(x1>x && y1>y && x2<x && y2 <y)||(x>x2 && y<y2 && x<x1 && y>y1) || (x<x2 && y>y2 && x>x1 && y<y1));
    }
    return answer;


//    bool answer1 = false;

//    int x = ceil(xp);
//    int y = ceil(yp);

//    if(x1 == x2){   // Cas du mur vertical
//        answer1 = ((y<=y2 && y>=y1) || ( y>=y2 && y<=y1)) && x == x1;
//    }
//    else if (y1 == y2){   // Cas du mur horizental
//        answer1 = ((x>=x2 && x<=x1) || (x<=x2 && x>=x1)) && y == y1;
//    }
//    else {
//       answer1 = ((x1<=x && y1<=y && x2>=x && y2 >=y) ||(x1>=x && y1>=y && x2<=x && y2 <=y)||(x>=x2 && y<=y2 && x<=x1 && y>=y1) || (x<=x2 && y>=y2 && x>=x1 && y<=y1));
//    }


//    x = floor(xp);
//    y = floor(yp);

//    bool answer2;

//    if(x1 == x2){   // Cas du mur vertical
//        answer2 = ((y<=y2 && y>=y1) || ( y>=y2 && y<=y1)) && x == x1;
//    }
//    else if (y1 == y2){   // Cas du mur horizental
//        answer2 = ((x>=x2 && x<=x1) || (x<=x2 && x>=x1)) && y == y1;
//    }
//    else {
//       answer2 = ((x1<=x && y1<=y && x2>=x && y2 >=y) ||(x1>=x && y1>=y && x2<=x && y2 <=y)||(x>=x2 && y<=y2 && x<=x1 && y>=y1) || (x<=x2 && y>=y2 && x>=x1 && y<=y1));
//    }

//    x = floor(xp);
//    y = ceil(yp);

//    bool answer3;

//    if(x1 == x2){   // Cas du mur vertical
//        answer3 = ((y<=y2 && y>=y1) || ( y>=y2 && y<=y1)) && x == x1;
//    }
//    else if (y1 == y2){   // Cas du mur horizental
//        answer3 = ((x>=x2 && x<=x1) || (x<=x2 && x>=x1)) && y == y1;
//    }
//    else {
//       answer3 = ((x1<=x && y1<=y && x2>=x && y2 >=y) ||(x1>=x && y1>=y && x2<=x && y2 <=y)||(x>=x2 && y<=y2 && x<=x1 && y>=y1) || (x<=x2 && y>=y2 && x>=x1 && y<=y1));
//    }

//    x = ceil(xp);
//    y = floor(yp);

//    bool answer4;

//    if(x1 == x2){   // Cas du mur vertical
//        answer4 = ((y<=y2 && y>=y1) || ( y>=y2 && y<=y1)) && x == x1;
//    }
//    else if (y1 == y2){   // Cas du mur horizental
//        answer4 = ((x>=x2 && x<=x1) || (x<=x2 && x>=x1)) && y == y1;
//    }
//    else {
//       answer4 = ((x1<=x && y1<=y && x2>=x && y2 >=y) ||(x1>=x && y1>=y && x2<=x && y2 <=y)||(x>=x2 && y<=y2 && x<=x1 && y>=y1) || (x<=x2 && y>=y2 && x>=x1 && y<=y1));
//    }

//    return answer1 || answer2 || answer3 || answer4;
}

bool room::pointOnLineNonInclusive(lineo* line1,const double xp,const double yp){

    /*
     * As the intersection is computed by lines equations, it is required to check whether or not the intersection is placed on the the wall line, an line
     * equation being define from [-INF, +INF]
     */


    int x1 = (int)line1->getX1();
    int y1 = (int)line1->getY1();
    int x2 = (int)line1->getX2();
    int y2 = (int)line1->getY2();

    bool answer1 = false;

    int x = ceil(xp);
    int y = ceil(yp);

    if(x1 == x2){   // Cas du mur vertical
        answer1 = ((y<y2 && y>y1) || ( y>y2 && y<y1)) && x == x1;
    }
    else if (y1 == y2){   // Cas du mur horizental
        answer1 = ((x>x2 && x<x1) || (x<x2 && x>x1)) && y == y1;
    }
    else {
       answer1 = ((x1<x && y1<y && x2>x && y2 >y) ||(x1>x && y1>y && x2<x && y2 <y)||(x>x2 && y<y2 && x<x1 && y>y1) || (x<x2 && y>y2 && x>x1 && y<y1));
    }


    x = floor(xp);
    y = floor(yp);

    bool answer2;

    if(x1 == x2){   // Cas du mur vertical
        answer2 = ((y<y2 && y>y1) || ( y>y2 && y<y1)) && x == x1;
    }
    else if (y1 == y2){   // Cas du mur horizental
        answer2 = ((x>x2 && x<x1) || (x<x2 && x>x1)) && y == y1;
    }
    else {
       answer2 = ((x1<x && y1<y && x2>x && y2 >y) ||(x1>x && y1>y && x2<x && y2 <y)||(x>x2 && y<y2 && x<x1 && y>y1) || (x<x2 && y>y2 && x>x1 && y<y1));
    }

    return answer1 || answer2;

// bool room::pointOnLineNonInclusive(lineo* line1,const double xp,const double yp){
//     double x1 = line1->getX1();
//     double y1 = line1->getY1();
//     double x2 = line1->getX2();
//     double y2 = line1->getY2();

//     bool answer;
    
//     if(x1==x2){ // Cas du mur vertical
//         answer = (x1=<xp && xp=<x1+1 && ( (y1<yp && yp<y2) || (y2<yp && yp<y1) ) )
//     }else if(y1 == y2){ // Cas du mur horizontal
//         answer = (y1=<yp && yp=<y1+1 && ( (x1<xp && xp<x2) || (x2<xp && xp<x1) ) )
//     }else{
//         answer = false;
//     }
//     return answer;
}

bool room::intersectionCheck(lineo* line1, lineo* line2){
    /*
     * Two-equations line system, determines the intersection point if it exists
     *    y = ax + b
     *    y = cx + d
     */

    double xpos;
    double ypos;

    long double a = line1->getSlope();
    double b = line1->getYorigin();
    long double c = line2->getSlope();
    double d = line2->getYorigin();

    if(a == INFINITY){
        xpos = line1->getX1();
        ypos = c * xpos + d;
    }

    else if(c == INFINITY){
        xpos = line2->getX1();
        ypos = a * xpos + b;
    }
    else{
    xpos = (d - b)/(a - c);
    ypos = (a * xpos) + b;
    }

    return (pointOnLine(line1,xpos,ypos) && pointOnLine(line2,xpos,ypos));

}

bool room::intersectionCheckNonInclusive(lineo* line1, lineo* line2){
    /*
     * Two-equations line system, determines the intersection point if it exists
     *    y = ax + b
     *    y = cx + d
     */

    double xpos;
    double ypos;

    long double a = line1->getSlope();
    double b = line1->getYorigin();
    long double c = line2->getSlope();
    double d = line2->getYorigin();

    if(a == INFINITY){
        xpos = line1->getX1();
        ypos = c * xpos + d;
    }

    else if(c == INFINITY){
        xpos = line2->getX1();
        ypos = a * xpos + b;
    }
    else{
    xpos = (d - b)/(a - c);
    ypos = (a * xpos) + b;
    }

    return (pointOnLineNonInclusive(line1,xpos,ypos) && pointOnLineNonInclusive(line2,xpos,ypos));

}


bool room::checkTransmission(lineo* line1, lineo* line2, int x1, int y1,int x2,int y2){
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
    double R = (cos(thetaI) - sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)))/(cos(thetaI) + sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)));
    return R;
}

double room::computeReflexionPar(double thetaI, double epsilonR){
    double R = (cos(thetaI) - (1/sqrt(epsilonR))*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)))/(cos(thetaI) + (1/sqrt(epsilonR))*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)));
    return R;
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
    double R = 1;
    complex <double> Efield = 0.0;
    ray *currentRay;
    for (int i=0; i<amountSegment; i++){
        currentRay = rayLine.at(i);
        if((i != amountSegment-1)){   // The last segment, the one that reach the receptor does not have a rebound
            double tethaI = abs(currentRay->getTetai());
            R *= computeReflexionPer(tethaI,epsilonWallRel);
        }
        completeLength += currentRay->getMeterLength(); // Get each length of each ray segment after the meter conversion (1px == 1dm)
    }

    double Ia = sqrt(2.0*powerEmettor/Ra); // Ia could be changed for Beamforming application (add exp)
    double a = R * ((Zvoid*Ia)/(2.0*M_PI))/completeLength;
    Efield = -i * a * exp(-i*(2.0*M_PI/lambda)*completeLength);

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
    if(computePhysicalResponse){
        // Store attenuation a and distance completeLength 
        channelData[rayNumber] = R/completeLength;
        channelData[rayNumber+20] = completeLength;
        rayNumber += 1;
    }

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

double room::diffractedRayPower(ray* rayReceiver, ray* rayTransmitter){

    // Direct distance between the receiver and the transmitter
    double direct_dist = sqrt(pow(Transmitter->getPosX()-Receiver->getPosX(),2) + pow(Transmitter->getPosY()-Receiver->getPosY(),2)); //convertir px to cm?

    // The vactor that will contain the direct ray.
    //vector<ray*> rayLine;
    //rayLine.clear();

    complex<double> Efield =0.0;

    // The length defference between the path going through the tip of the obstacle, and the direct path.

    double delta_r = rayReceiver->getLength()+rayTransmitter->getLength() - direct_dist*pow(10, -1.0);


    double nu = sqrt(2*Beta*delta_r/M_PI);

    // The ITU's approximation for |F(nu)|^2
    double FresnelPowerdB = -6.9 - 20*log10(sqrt(pow(nu-0.1,2)+1)+nu-0.1);
//    double FresnelPowerdB = 6.9 + 20*log10(sqrt(pow(nu-0.1,2)+1)+nu-0.1);
    double FresnelPower = pow(10,FresnelPowerdB/20);
//    double fresnelPowerW = pow(10,FresnelPower/20);
    //double fresnelNorm = sqrt(-6.9 - 20*log10(sqrt(pow(nu-0.1,2)+1)+nu-0.1));
//    double fresnelNorm = sqrt(fresnelPowerW);
//    double fresnelArg = -(M_PI/4)-(M_PI/2)*pow(nu,2);
//    double fresnelArg = -(1/4)-(1/2)*pow(nu,2);
//    complex <double> fresnelCoef = fresnelNorm*exp(fresnelArg);
//    complex <double> fresnelCoef = (fresnelNorm*cos(M_PI*fresnelArg),fresnelNorm*sin(M_PI*fresnelArg));
//    norm(fresnelCoef) = fresnelNorm;
//    arg(fresnelCoef) = fresnelArg;
    ray* directRay = new ray(Receiver->getPosX(),Receiver->getPosY(),Transmitter->getPosX(),Transmitter->getPosY(),0,0);
    //rayLine.push_back(directRay);
    //Efield = computeEfield(rayLine);
//    double G = Zvoid/(pow(M_PI, 2)*Ra);
    //Efield = (sqrt(60*G*powerEmettor)/directRay->getMeterLength());  // we can add the phase if we want to take into account the interraction between MPCs
    complex <double> i(0.0, 1.0);
    double Ia = sqrt(2*powerEmettor/Ra); // Ia could be changed for Beamforming application (add exp)
    Efield =-i  * ((Zvoid*Ia)/(2*M_PI)) * (exp(-i*(2.0*M_PI/lambda)*directRay->getMeterLength())/directRay->getMeterLength());
    double power = 1/(8*Ra)*norm((lambda/M_PI)*Efield)*FresnelPower;

//    totalEfield += Efield*fresnelCoef;

    delete(directRay);
//    cout<< "Fresnel coeffiecient: ";
//    cout<<fresnelCoef<<endl;
//    cout<< "Fresnel norm: ";
//    cout<<fresnelNorm<<endl;
//    cout<< "Fresnel argument: ";
//    cout<<fresnelArg<<endl;
//    cout<< "Fresnel power: ";
//    cout<<FresnelPower<<endl;
//    cout<< "Electric field: ";
//    cout<<Efield<<endl;
//    cout<< "Electric field power: ";
//    cout<<1/(8*Ra)*pow(norm((lambda/M_PI)*Efield),2)<<endl;
//    cout<< "Electric field power(dBm): ";
//    cout<<dBm(1/(8*Ra)*pow(norm((lambda/M_PI)*Efield),2))<<endl;
//    cout<< "power: ";
//    cout<<power<<endl;
//    cout<< "power(dBm): ";
//    cout<<dBm(power)<<endl;
//    cout<< "nu: ";
//    cout<<nu<<endl;
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
    powerRef = 0.0;
    minLength = 0.0;
    maxLength = 0.0;
    LOS = 0.0;
    NLOS = 0.0;
    rayNumber = 0;
    //Efield = 0.0;
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
              if(line == "true"){diffractOn = true;}else{
                  diffractOn = false;
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
    int x2 = Receiver->getPosX();
    int y2 = Receiver->getPosY();

    // dist = new QGraphicsLineItem(x1,y1,x2,y2,NULL);
    // //this->addItem(dist);

    // QPen outlinePen(Qt::green);
    // outlinePen.setWidth(2);
    // dist->setPen(outlinePen);

    return sqrt(pow((x2-x1),2)+pow((y2-y1),2))*this->pxToMeter; // conversion (1px == 1dm)
}

// --> Getters and Setters ----------------------------------------------------------------------------------------------------------------


antena* room::getReceiver(){return Receiver;}
antena* room::getTransmitter(){return Transmitter;}
double room::getReceivedPower(){return powerReceived;}
wall* room::getWalls(int i){return walls[i];}
int room::getAmountWalls(){return amount_walls;}
double room::getBinaryDebit(){return resultsBinaryDebit;}
int room::getAmountDiscret(){return amount_discret;}
double room::getpowerEmettor(){return powerEmettor;}
double room::getInitBinaryDeb(){return binaryDebit(powerEmettor);}
complex <double> room::getTotalEfield(){return totalEfield;}
double room::getCarrierFrequency(){return freq;}

void room::setReceiver(antena *new_receiver){Receiver = new_receiver;}
void room::setTransmitter(antena *new_transmitter){Transmitter = new_transmitter;}
int room::getRows(){return rows;}
int room::getColumns(){return columns;}
int room::getTotalArea(){return totalArea;}
int room::getMinimalDistance(){return minimalDistance;}
int room::getSquare_size(){return square_size;}
double room::getPxToMeter(){return pxToMeter;}
double* room::getData(){return this->Data;}
int room::getRayNumber(){return this->rayNumber;}
double* room::getChannelData(){return this->channelData;}

// ---> Events listeners ----------------------------------------------------------------------------------------------------------------


void room::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{   QPointF x = event->scenePos();
    QPoint X = x.toPoint();

    myParent->onMouseEvent("ll",X);
}


void room::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (antenaType == 0){
        if (Transmitter != NULL){
            delete Transmitter;
            Transmitter = NULL;};

        Transmitter = new antena(this, event->scenePos(),antenaType);
        this->addItem(Transmitter);
    }

    else if (antenaType == 1){
        if (Receiver != NULL){
            delete Receiver;
            Receiver = NULL;};

        Receiver = new antena(this, event->scenePos(),antenaType);
        this->addItem(Receiver);
    }
}

void room::mouseReleaseEvent(QGraphicsSceneMouseEvent */*unused event*/){antenaType = 2;}




//---> Draw the heatmap-------------------------------------------------------------------------------------------------------------------


void room::drawCoverege(){
    this->clearAll();
    if(Receiver !=NULL){
        delete Receiver;
        Receiver = NULL;
    }
    if(coverageDone) free(Data);
    Receiver = new antena(this,QPointF(0,0),1);
    //QBrush brush;
    QBrush *brush = new QBrush(QColor(0, 0, 0, 220));
    QPen pen;
    pen.setColor(QColor(0,0,0,0));
    QColor color;
    
    this->Data = (double *)calloc(totalArea * 4, sizeof(double));
    if (!this->Data) {
        printf("mem failure, exiting \n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<columns; i++){
        for(int j=0; j<rows; j++){
            this->clearLocalParameters();
            double xRece = square_size/2 + i*square_size;
            double yRece = square_size/2 + j*square_size;

            Receiver->setPosi(QPointF(xRece,yRece));
            launch_algo(false);
            this->Data[i*rows+j] = (powerReceived); // Received Power[W]
            this->Data[i*rows+j+totalArea] = abs(maxLength-minLength)/c; // Delay Spread
            this->Data[i*rows+j+totalArea*2] = 10*log10(LOS/NLOS); // Rice factor
            this->Data[i*rows+j+totalArea*3] = this->distance(); // Distance from TX

           // Plot results
           // Change binaryDebit which is different for 5G
           if(250 - 250*resultsBinaryDebit/250>=0){color.setHsv((250 - 250*resultsBinaryDebit/250),255,105 + resultsBinaryDebit*150/260,255);}
           else{color.setHsv(0,255,255,255);}
           brush->setColor(color);
           this->addRect(i*square_size,j*square_size,square_size,square_size,pen,*brush);
        }
    }
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
