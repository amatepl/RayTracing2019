#include "room.h"


using namespace std;

room::room(MainWindow *parent) :
    QGraphicsScene(parent)
  //, QImage(1000,1000, QImage::Format_RGB32)
{   myParent = parent;

    readSettingsFile();

    antenaType = 2; // 0 for transmitter 1 for receiver 2 for nothing
    Transmitter = NULL;
    Receiver = NULL;

    complex <double> i(0.0, 1.0);
    lambda = c/freq;

    // Absolute electric permittivity
    eps = epsilonAir*epsilonWallRel;

    // impedance of the wall
    Zwall = sqrt((muAir/eps));

    // Propagation constants for small-loss hypothesis
    alpha = 2*M_PI*freq*sqrt((muAir*eps)/2)*sqrt((sqrt(1 + pow((wallSigma/(2*M_PI*freq*eps)), 2)) -1 ));
    beta = 2*M_PI*freq*sqrt((muAir*eps)/2)*sqrt((sqrt(1 + pow((wallSigma/(2*M_PI*freq*eps)), 2)) + 1 ));

    gamma = alpha + i*beta;

    // Let us define the walls and draw the view
    walls[0] = new wall(970,1,970,485, 0.0, 0.0, 0.0, 0);
    walls[1] = new wall(970,1,1,1, 0.0, 0.0, 0.0, 1);
    walls[2] = new wall(1,1,1,485, 0.0, 0.0, 0.0, 2);
    walls[3] = new wall(970,485,1,485, 0.0, 0.0, 0.0, 3);
    walls[4] = new wall(250, 1, 250, 250, 0.0, 0.0, 0.0, 4);
    walls[5] = new wall(250, 300, 250, 485, 0.0, 0.0, 0.0, 5);
    walls[6] = new wall(250, 150, 500, 150, 0.0, 0.0, 0.0, 6);
    walls[7] = new wall(550, 150, 970, 150, 0.0, 0.0, 0.0, 7);
    walls[8] = new wall(750, 150, 750, 390, 0.0, 0.0, 0.0, 8);
    walls[9] = new wall(750, 390, 840, 390, 0.0, 0.0, 0.0, 9);
    walls[10] = new wall(900, 390, 970, 390, 0.0, 0.0, 0.0, 10);

    QPen outlinePen(QColor(0, 0, 0, 255));
    outlinePen.setWidth(2);
    this->addLine(*walls[0],outlinePen);
    this->addLine(*walls[1],outlinePen);
    this->addLine(*walls[2],outlinePen);
    this->addLine(*walls[3],outlinePen);
    this->addLine(*walls[4],outlinePen);
    this->addLine(*walls[5],outlinePen);
    this->addLine(*walls[6],outlinePen);
    this->addLine(*walls[7],outlinePen);
    this->addLine(*walls[8],outlinePen);
    this->addLine(*walls[9],outlinePen);

    this->addLine(*walls[10],outlinePen);

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

    // Calculate power -- Reflexion and transmission
    if(drawR){
    recursion(Transmitter->getPosX(), Transmitter->getPosY(),Receiver->getPosX(),Receiver->getPosY(),reflectionsNumber,drawRay);
    }
    else{recursion(Transmitter->getPosX(), Transmitter->getPosY(),Receiver->getPosX(),Receiver->getPosY(),reflectionsNumber, buildRay);}
    //powerReceived =  calculatePower(allRays);


    // Calculate power -- Diffraction
//    if(diffractOn == true){
//        calculateDiffractedRays();
//        double secondarypower = calculatePowerDiff(allDiffractedRays);
//        powerReceived += secondarypower;
//    }

    powerReceived = dBm(power);
    resultsBinaryDebit = binaryDebit(powerReceived);
    //cout<<resultsBinaryDebit<<"\n";
    //cout << "->";
}


// ------------------------------ Image method ------------------------------------------------


void room::recursion(double transmitterPosX, double transmitterPosY, double receiverPosX, double receiverPosY, int numberOfReflections,void (*draw)(double, double, double, double,room*)){

    /*
     * The recursion method generalize the image method for any amount of reflections. Keeps track of the depth of the recursive algorithm.
     * Calls drawRay and stores the rays as they are being created.
     */

    transmitterSerie[recursionState][0] = transmitterPosX;
    transmitterSerie[recursionState][1] = transmitterPosY;

    QLineF* current_wall = wallRecursiveNumber[recursionState];

    int NumberOfReflections = numberOfReflections;

    // ---- Drawing of the ray on the screen && saving ----
    (*draw)(transmitterPosX,transmitterPosY,receiverPosX,receiverPosY,this);



    // --- Re-loop starts -------------
    if(NumberOfReflections > 0 ){
        recursionState += 1;

        //Direct ray beteween the transmitter and the receiver

        for(int i = 0;i < amount_walls;i++){

           current_wall = walls[i];

            if(current_wall != wallRecursiveNumber[recursionState -1]){
                wallRecursiveNumber[recursionState] = walls[i];

                angle_wall = current_wall->angle()*M_PI/180.0;

                //------------TRANSMITTER IMAGE CONSTRUCTION--------------------------

                double ray_vector_length = sqrt(pow(transmitterPosY - current_wall->y2(),2) + pow(transmitterPosX - current_wall->x2(),2));
                double virtual_slope;

                if (transmitterPosY - current_wall->y2() < 0 && transmitterPosX - current_wall->x2()){
                    virtual_slope = -acos((transmitterPosX - current_wall->x2())/ray_vector_length);
                }

                else{
                    virtual_slope = acos((transmitterPosX - current_wall->x2())/ray_vector_length);
                }

                double ray_slope = angle_wall + (angle_wall - virtual_slope);
                double ray_vector[2] ={cos(ray_slope) , sin(ray_slope)};
                double x2 = ray_vector_length * ray_vector[0];
                double y2 = ray_vector_length * ray_vector[1];
                double transmitterImagePosX = current_wall->x2() + x2;
                double transmitterImagePosY = current_wall->y2() + y2;

                //---------END OF TRANSMITTER IMAGE CONSTRUCTION--------------------------

                recursion(transmitterImagePosX, transmitterImagePosY,receiverPosX,receiverPosY,NumberOfReflections - 1,draw);
            }

        if(i == amount_walls - 1){recursionState -=1;}
        }
    }
}



void room::drawRay(double transmitterPosX,double transmitterPosY,double originX,double originY,room* scene){

    /*
     * Called back from the recursion method, draws the rays starting from the receivrer when necessary, then removes the excess if
     * one branch of the whole ray isn't intersecting the wall on which it should reflect (the wall which was used to build the image).
     *
     * wholeRay - list of all the branches of a ray
     */

    // Freeing memory

    (*scene).completeRay.clear();

    ray* wholeRay[(*scene).recursionState];
    ray* receiver_ray;
    QPen outlinePen(QColor(0, 0, 255, 255));
    outlinePen.setWidth(1);
    QPointF intersectionPoint;
    QPointF intersectWall;

    unsigned char j = 0;
    while(j<=(*scene).recursionState){
        /*
         * If we are in the recursion we have to build the whole ray using the transmitters and walls from
         * wall recursiveNumber and transmitterSerie
         */

        //walle = a wall from wallRecursiceNumber beggening from the last one
        wall* walle = (*scene).wallRecursiveNumber[(*scene).recursionState -j];

        //Takking the cooridinates of the consecutives inages of transmitters begging with the last one
        transmitterPosX = (*scene).transmitterSerie[(*scene).recursionState-j][0];
        transmitterPosY = (*scene).transmitterSerie[(*scene).recursionState-j][1];

        //Builiding a temporary ray from the transmitter to the receiver
        (*scene).current_ray= new QLineF(transmitterPosX,transmitterPosY,originX,originY);

        if(j != (*scene).recursionState){
            (*scene).current_ray->intersect(*walle,&intersectWall);
            (*scene).imCoordinates[0] = intersectWall.x();
            (*scene).imCoordinates[1] = intersectWall.y();

            //ray* receiver_ray;

            if((*scene).current_ray->intersect(*walle,&intersectionPoint)==1){
                receiver_ray = new ray(intersectionPoint.x(),intersectionPoint.y(),originX,originY,M_PI/2 - abs(abs((*scene).current_ray->angle()*M_PI/180)-abs(walle->angle())*M_PI/180),walle->getIndWall());
                wholeRay[j] = receiver_ray;
                (*scene).completeRay.push_back(receiver_ray);

                originX = intersectionPoint.x();
                originY = intersectionPoint.y();
            }
            else{
                (*scene).completeRay.clear();
                j = (*scene).recursionState+1;
            }
        }
        else if(j == (*scene).recursionState){

            //Ray from transmitter
            receiver_ray = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),originX,originY,0,0);
            (*scene).completeRay.push_back(receiver_ray);

        }
        j+=1;
    }
    (*scene).completeRay.shrink_to_fit();

    if(!(*scene).completeRay.empty()){

        for(unsigned char i=0;i<(*scene).completeRay.size();i++){

            outlinePen.setColor(QColor(0,255 -  (255/((*scene).reflectionsNumber + 1))*(i),255,255));
            scene->addLine(*(*scene).completeRay[i],outlinePen);
        }

        (*scene).power +=1/(8*(*scene).Ra)*(*scene).calculateRay((*scene).completeRay);   
    }
}


void room::buildRay(double transmitterPosX,double transmitterPosY,double originX,double originY,room* scene){

    /*
     * Called back from the recursion method, draws the rays when necessary, then removes the excess
     */

    // Freeing memory

    (*scene).completeRay.clear();

    ray* wholeRay[(*scene).recursionState];
    ray* receiver_ray;
    QPointF intersectionPoint;
    QPointF intersectWall;

    unsigned char j = 0;
    while(j<=(*scene).recursionState){

        wall* walle = (*scene).wallRecursiveNumber[(*scene).recursionState -j];
        transmitterPosX = (*scene).transmitterSerie[(*scene).recursionState-j][0];
        transmitterPosY = (*scene).transmitterSerie[(*scene).recursionState-j][1];
        (*scene).current_ray= new QLineF(transmitterPosX,transmitterPosY,originX,originY);

        if(j != (*scene).recursionState){
            (*scene).current_ray->intersect(*walle,&intersectWall);
            (*scene).imCoordinates[0] = intersectWall.x();
            (*scene).imCoordinates[1] = intersectWall.y();

            //ray* receiver_ray;

            if((*scene).current_ray->intersect(*walle,&intersectionPoint)==1){
                receiver_ray = new ray(intersectionPoint.x(),intersectionPoint.y(),originX,originY,M_PI/2 - abs(abs((*scene).current_ray->angle()*M_PI/180)-abs(walle->angle())*M_PI/180),walle->getIndWall());
                wholeRay[j] = receiver_ray;
                (*scene).completeRay.push_back(receiver_ray);

                originX = intersectionPoint.x();
                originY = intersectionPoint.y();
            }
            else{
                (*scene).completeRay.clear();
                j = (*scene).recursionState+1;
            }
        }
        else if(j == (*scene).recursionState){

            //Ray from transmitter
            receiver_ray = new ray((*scene).Transmitter->getPosX(),(*scene).Transmitter->getPosY(),originX,originY,0,0);
            (*scene).completeRay.push_back(receiver_ray);

        }
        j+=1;
    }
    (*scene).completeRay.shrink_to_fit();

    if(!(*scene).completeRay.empty()){(*scene).power +=1/(8*(*scene).Ra)*(*scene).calculateRay((*scene).completeRay);}
}


// ----------------------------------------------- Diffraction -----------------------------------------------------


void room::calculateDiffractedRays(){
    /*
     * The first part is a search algorithm to find all the door edges, for each wall we check if the two extreme points are met with only one wall line, if it is
     * the case, it is an edge
     */

    vector <vector <int>> edges;

    // Search algorithm

    for (int i = 0; i < amount_walls; i ++){

        wall *current_wall = walls[i];

            double x1_check = current_wall->x1();
            double y1_check = current_wall->y1();

            double x2_check = current_wall->x2();
            double y2_check = current_wall->y2();

                if(commonToAnyWall(x1_check, y1_check, i) != false){

                    vector <int> coord;
                    coord.push_back(x1_check);
                    coord.push_back(y1_check);

                    edges.push_back(coord);
                    }

                if(commonToAnyWall(x2_check, y2_check, i) != false){

                    vector <int> coord;
                    coord.push_back(x2_check);
                    coord.push_back(y2_check);

                    edges.push_back(coord);
                }
        }

    // Drawing the diffracted rays

    edges.shrink_to_fit();

    for(unsigned char i = 0; i < edges.size(); i ++){
        completeRay.clear();
        completeRay.shrink_to_fit();

        int x = edges.at(i)[0];
        int y = edges.at(i)[1];

        // Starting ray
        ray *transmitter_ray = new ray(Transmitter->getPosX(),Transmitter->getPosY(),x,y,0,0);
        completeRay.push_back(transmitter_ray);


        // Arriving ray
        ray *receiver_ray = new ray(Receiver->getPosX(),Receiver->getPosY(),x,y,0,0);
        completeRay.push_back(transmitter_ray);


            // Starting ray
//            this->addItem(transmitter_ray);   // Send the ray to be displayed

//            QPen outlinePen(QColor(255, 0, 0, 220));
//            outlinePen.setWidth(1);
//            transmitter_ray->setPen(outlinePen);

            // Arriving ray
//            this->addItem(receiver_ray);   // Send the ray to be displayed
//            receiver_ray->setPen(outlinePen);

            allDiffractedRays.push_back(completeRay);
    }
}


// --> Numerical computing --------------------------------------------------------------------------------------------------------------


complex <double> room::FtIntegral(double x){
    /*
     * For improper integral methods, the trapez method is usually not the good way to come by, however for a rapidelly oscillating integral this method works very well (in that case)
     * The integral from sqrt(x) -> INFINITY is the integral from 0 -> INFINTY from which the integral from 0 -> sqrt(x) has been cut.
     *
     * Fortunately, there is an analytical solution to the first integral, and we will evaluate the second one with the trapez method.
     */

    complex <double> j(0,1);
    complex <double> res(0, 0) ;
    complex <double> completIntegral (sqrt((M_PI/2.0))*1/2, -sqrt((M_PI/2.0))*1/2);

    complex <double> coeff = 2.0*j*sqrt(x)*exp(j*x);;

    // Lets compute the approximate of the integral

    double step = 1;
    double i = 0.0;
    double MAX_RANGE = sqrt(x);

    // Trapez method

    while(i < MAX_RANGE){
        if(i == sqrt(x) || i == MAX_RANGE){
            res+= exp(-1.0*j*pow(i, 2));
        }else{
            res += 2.0*exp(-1.0*j*pow(i, 2));
        }
        i += step;
    }

    complex <double> integral = (step/2.0)*coeff*(completIntegral - res);
    return integral;
}

// --> geometric tools ------------------------------------------------------------------------------------------------------------------


bool room::commonToAnyWall(double posX, double posY, int indwall){

    /*
     * To know whether or not an extremety of a wall is an edge, it is requered to check if the point is shared with another wall of the list
     */

    bool ans = true;

    for (int i = 0; i < amount_walls; i ++){

            if(pointOnLine(walls[i], posX, posY)  && i != indwall /*&& walls[i]->line().intersect(walls[indwall]->line(), NULL) == 0*/){
                ans = false;
            }
    }
    return ans;
}






bool room::pointOnLine(QLineF *line1, double x, double y){

    /*
     * As the intersection is computed by lines equations, it is required to check whether or not the intersection is placed on the the wall line, an line
     * equation being define from [-INF, +INF]
     */

    int x1 = line1->x1();
    int y1 = line1->y1();
    int x2 = line1->x2();
    int y2 = line1->y2();

    bool answer;


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



double room::distInWall(double tetai){

/*
 * It is requiered to know the distance travelled in the wall, we will use Snell's rule to determine the angle in the transmitted ray inside the wall, then
 * knowing the thickness determine the length in the wall by simple trigonometry.
 */
    double tetaTrans = asin((sqrt(epsilonAir)*sin(tetai))/(sqrt(epsilonWallRel*epsilonAir)));    // Snell's rule

    return wallThickness*pow(10, -2)/cos(tetaTrans);    // L/cos(\teta_Transmitted) cosine projection, the 1/2 factor for the pixel to Cm conversion
}

// --> Electrical power calculation --------------------------------------------------------------------------------------------------------------------


double room::calculatePower(vector< vector<ray*>> allRays){

    /* All rays evaluated by the image method are vectors of rays, stored in a bigger vector structure, (so that one vector is one complet n-sized ray), for each the
     * amount of reflections is computed as well as the intersections with all walls, in which the T transmission coefficient is computed. The distance the ray went
     * through in the wall is corrected in the ray object.
     */

    double results = 0;
    int amountRays = allRays.size();
    current.clear();
    current.shrink_to_fit();

    for(int i =0; i < amountRays; i++){
        current = allRays.at(i);

        if(current.size() != 0){
            results += calculateRay(current);
        }
    }
    return 1/(8*Ra)*results;   // Mean power per meter squared
}


double room::calculatePowerDiff(vector< vector<ray*>> allRays){

    /* All rays evaluated by the image method are vectors of rays, stored in a bigger vector structure, (so that one vector is one complet n-sized ray), for each the
     * amount of reflections is computed as well as the intersections with all walls, in which the T transmission coefficient is computed. The distance the ray went
     * through in the wall is corrected in the ray object.
     */

    double results = 0;
    int amountRays = allRays.size();


    for(int i =0; i < amountRays; i++){

        current.clear();
        current.shrink_to_fit();
        current = allRays.at(i);

        if(current.size() != 0){
            results += calculateRay(current);
        }
    }
    return 1/(8*Ra)*results;   // Mean power per meter squared
}

double room::calculateRay(vector<ray*> rayLine){

    /* One vector is one multi-path componant, the size of the vector determine the n-level we are in, for each ray only the power in the last ray is transmitted to
     * the receptor. As seen in the power formula, n rays -> n-1 additions to the power.
     *
     * The caracteristic length is only determined by the angle the last ray makes with the receptor, assuming the optimal orientation is set to angle zero, relative
     * to the x-axis.
     */

    int amountSegment = rayLine.size();  // Après avoir shrink to fit dans launch_algo()

    double completeLength = 0.0;
    Efield = 0.0;

    complex <double> T (1.0, 0.0);   // let us define a global transmission coefficient
    complex <double> R (1.0, 0.0);   // Definition global reflection coefficient
    complex <double> Rp;
    complex <double> k(0.0, 1.0);

    ray *current_r;

    for (int i = 0; i < amountSegment; i++){
        current_r = rayLine.at(i);
        std::cout<<"I'm alive!"<<endl;
        double x1 = current_r->x1();
        double y1 = current_r->y1();

        double x2 = current_r->x2();
        double y2 = current_r->y2();

        // Transmission --------------------------------

        for(int j = 0; j < amount_walls; j++){
            std::cout<<"x1:"<<x1<<endl;
            if((current_r->intersect(*walls[j],NULL)==1) && pointOnLine(walls[j], x2, y2) == false && pointOnLine(walls[j], x1, y1) == false){

                double tetai = abs(abs(current_r->angle()*M_PI/180)-abs(walls[j]->angle()*M_PI/180));
                std::cout<<"Wall:"<<walls[j]->x1()<<endl;
                //std::cout<<"Tetai:"<<tetai<<endl;

                double tetat = asin(sqrt(epsilonAir/eps)*sin(tetai));   //Snell's law

                double s = distInWall(tetai);
                current_r->updateLength(s);

                /*
                 * The propagation constant is a complex number \gamma, in the exponantial we leave out the complex part, as it has only
                 * consequences on the phase, which is not interesting for now.
                 *
                 * We are in the context of low-loss in the walls. And then j\beta = \gamma
                 */

                Rp = (Zwall*cos(tetai) - Zvoid*cos(tetat))/(Zwall*cos(tetai) + Zvoid*cos(tetat));
                T *= ((1.0 - pow(Rp, 2.0))*exp(-gamma*s))/(1.0 - pow(Rp, 2)*exp(-2.0*gamma*s)*exp(k*(2*M_PI/lambda)*s*sin(tetai)*sin(tetat)));

            }else{}
        }


      //  Reflection -----------------------------


        if((i != amountSegment - 1)){   // The last segment, the one that reach the receptor does not have a rebound

            // Lets check which wall was hit by this ray

            double tetai = abs(current_r->getTetai());
            //std::cout<<"Tetai:"<<tetai<<endl;
            double tetat = asin(sqrt(epsilonAir/eps)*sin(tetai));    // Snell's law

            double s = distInWall(tetai);

            Rp = (Zwall*cos(tetai) - Zvoid*cos(tetat))/(Zwall*cos(tetai) + Zvoid*cos(tetat));
            R *= Rp + (1.0 - pow(Rp, 2.0))*(Rp*exp(-2.0*gamma*s)*exp(k*2.0*(2*M_PI/lambda)*s*sin(tetai)*sin(tetat)))/(1.0 - pow(Rp, 2.0)*exp(-2.0*gamma*s)*exp(2.0*(2*M_PI/lambda)*s*sin(tetat)*sin(tetai)));
        }
        completeLength += current_r->getMeterLength();    // Get each length of each ray segment after the meter conversion (1px == 2cm)
    }


    // From the caracteristic surface of a \lamda/2, and the definition of the maximum gain for the receptor.Which means that \teta = M_PI/2

    double G = Zvoid/(pow(M_PI, 2)*Ra);

    // Carateristic length
    double h = lambda / M_PI;

    if(completeLength != 0.0){
        //std::cout<<completeLength<<endl;
        Efield = T * R * sqrt(60.0 * G * dBmRev(powerEmettor)) * exp(-1.0*k*(2.0*M_PI/lambda)*completeLength)/completeLength;

        double powerTransmitted = pow(norm(h*Efield), 2);
        //cout<<powerTransmitted<<"\n";
        return powerTransmitted;   // Returns the transmitted power in dBm for it te be added right away

    }else{return -1;}
}




double room::calculateRayDiff(vector<ray*> rayLine){

    /* One vector is one multi-path componant, the size of the vector determine the n-level we are in, for each ray only the power in the last ray is transmitted to
     * the receptor. As seen in the power formula, n rays -> n-1 additions to the power.
     *
     * The caracteristic length is only determined by the angle the last ray makes with the receptor, assuming the optimal orientation is set to angle zero, relative
     * to the x-axis.
     */

    int amountSegment = rayLine.size();  // Après avoir shrink to fit dans launch_algo()

    double completeLength = 0.0;
    Efield = 0.0;

    complex <double> T (1.0, 0.0);   // let us define a global transmission coefficient
    complex <double> D (1.0, 0.0);   // Definition global reflection coefficient
    complex <double> Rp;
    complex <double> k(0.0, 1.0);

    ray *current_r;

    for (int i = 0; i < amountSegment; i++){
        current_r = rayLine.at(i);

        double x1 = current_r->x1();
        double y1 = current_r->y1();

        double x2 = current_r->x2();
        double y2 = current_r->y2();


        // Transmission --------------------------------

        for(int j = 0; j < amount_walls; j++){

            if(current_r->intersect(*walls[j],NULL)&& pointOnLine(walls[j], x2, y2) == false && pointOnLine(walls[j], x1, y1) == false){

                double tetai = abs(abs(current_r->angle())-abs(walls[j]->angle()));
                double tetat = asin(sqrt(epsilonAir/eps)*sin(tetai));   //Snell's law

                double s = distInWall(tetai);
                current_r->updateLength(s);

                /*
                 * The propagation constant is a complex number \gamma, in the exponantial we leave out the complex part, as it has only
                 * consequences on the phase, which is not interesting for now.
                 *
                 * We are in the context of low-loss in the walls. And then j\beta = \gamma
                 */

                Rp = (Zwall*cos(tetai) - Zvoid*cos(tetat))/(Zwall*cos(tetai) + Zvoid*cos(tetat));
                T *= ((1.0 - pow(Rp, 2.0))*exp(-gamma*s))/(1.0 - pow(Rp, 2)*exp(-2.0*gamma*s)*exp(k*(2*M_PI/lambda)*s*sin(tetai)*sin(tetat)));

            }else{}
        }
    }


          //  Diffraction -----------------------------
    current_r = rayLine.at(0);
    ray *current_r2 = rayLine.at(1);

    completeLength = current_r->getMeterLength() + current_r2->getMeterLength();    // Get each length of each ray segment after the meter conversion (1px == 2cm)

        double L = (current_r->getMeterLength()*current_r2->getMeterLength())/completeLength;
        double delt = M_PI - abs(current_r->getTetai() - current_r2->getTetai());

        double arg = 2.0*(lambda/2.0*M_PI)*L*pow(sin(delt/2.0), 2);
        D = - (exp(-1.0*k*(M_PI/4))/(2.0*(sqrt(2.0*lambda*L)))) * (FtIntegral(arg)/(sin(delt/2)));

    double G = Zvoid/(pow(M_PI, 2)*Ra);

    // Carateristic length
    double h = lambda / M_PI; // * ((M_PI/2)*cos(M_PI/2))/(pow(sin(M_PI), 2));

    if(completeLength != 0.0){
        Efield = T * D * sqrt(60.0 * G * dBmRev(powerEmettor)) * exp(-1.0*k*(lambda/2.0*M_PI)*completeLength)/completeLength;
        totalEfield += Efield;

        double powerTransmitted = pow(norm(h*Efield), 2);
        //cout<<powerTransmitted<<"\\n";
        return powerTransmitted;   // Returns the transmitted power in dBm for it te be added right away
    }else{return -1;}
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

double room::dBm(double power){return 10*(log10(power)) + 30.0;}
double room::dBmRev(double dbm){return pow(10, -3)*pow(10, (dbm/10));}


// --> Miscellaneous ------------------------------------------------------------------------------------------------------------------------------


void room::clearAll(){
    totalEfield = 0.0;
    resultsBinaryDebit = 0.0;
    powerReceived = 0.0;
    allRays.clear();   // Empty all previously calculated vectors
    Efield = 0.0;
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
              amount_discret = stoi(line);
          }else if(count == 4){
              powerEmettor = stod(line);
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

    QGraphicsLineItem* dist ;

    int x1 = Transmitter->getPosX();
    int y1 = Transmitter->getPosY();
    int x2 = Receiver->getPosX();
    int y2 = Receiver->getPosY();

    dist = new QGraphicsLineItem(x1,y1,x2,y2,NULL);
    //this->addItem(dist);

    QPen outlinePen(Qt::green);
    outlinePen.setWidth(2);
    dist->setPen(outlinePen);

    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
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

void room::setReceiver(antena *new_receiver){Receiver = new_receiver;}
void room::setTransmitter(antena *new_transmitter){Transmitter = new_transmitter;}


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

    unsigned char discret = amount_discret;
    double square_size = 970/(double)discret;
    if(Receiver !=NULL){
        delete Receiver;
        Receiver = NULL;

    }
    Receiver = new antena(this,QPointF(0,0),1);
    //QBrush brush;
    QBrush *brush = new QBrush(QColor(0, 0, 0, 220));
    QPen pen;
    pen.setColor(QColor(0,0,0,0));
    QColor color;

    for(int i=0;i < discret;i++){
        for(int j=0;j < (int)discret/2;j++){
            power = 0;
            double xRece = square_size/2 + i*square_size;
            double yRece = square_size/2 + j*square_size;

            Receiver->setPosi(QPointF(xRece,yRece));
            launch_algo(false);
            if(250 - 250*resultsBinaryDebit/250>=0){color.setHsv((250 - 250*resultsBinaryDebit/250),255,105 + resultsBinaryDebit*150/260,255);}
            else{color.setHsv(0,255,255,255);}
            brush->setColor(color);
            this->addRect(i*square_size,j*square_size,square_size,square_size,pen,*brush);
       }
    }
    for(int i;i<=10;i++){
//        this->removeItem(walls[i]);
//        this->addItem(walls[i]);
    }
}
