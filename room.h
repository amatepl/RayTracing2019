#ifndef ROOM_H
#define ROOM_H


// Dependencies
#include "MainWindow.h"
#include "antena.h"
#include "math.h"
#include "wall.h"
#include "ray.h"
#include "lineo.h"

// Libraries
#include <complex>
#include <vector>
#include "math.h"

using namespace std;

class antena;
class wall;
class MainWindow;
class ray;

class room : public QGraphicsScene//, private QImage
{

    Q_OBJECT
public:
    explicit room(MainWindow *parent = 0);
    ~room(void);

    void launch_algo(bool drawR);

    float distance();
    void drawWall(qreal &x1, qreal &y1, qreal &x2, qreal &y2);

    // Getters && Setters
    double getReceivedPower();
    antena* getTransmitter();
    antena* getReceiver();
    wall* getWalls(int i);
    int getAmountWalls();
    double getBinaryDebit();
    int getAmountDiscret();
    double getpowerEmettor();
    double getInitBinaryDeb();
    complex <double> getTotalEfield();
    
    double getPrx(int posX, int posY);
    double getDelay(int posX, int posY);

    void setTransmitter(antena *new_transmitter);
    void setReceiver(antena *new_receiver);
    void setAntenaType(int type);

    //Misc tools
    void readSettingsFile();
    void clearAll();

    void drawCoverege();
    bool DataComputed();

signals:

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

    int antenaType;

private:

    // Qt visuals
    MainWindow *myParent;
    QGraphicsView *graphicsView;

    // General objects
    antena *Transmitter;
    antena *Receiver;
    wall *walls[28];    // For easier use walls are put in arrays
    vector <std::array <double,2>> diffractionPoints;
    //lineo *uselessWalls[10];


    // --> Global variables (electrical constants)

    double  epsilonAir = 8.864e-12;   // A²S⁴kg⁻1m⁻3
    double  Zvoid = 120*M_PI;
    double  muAir = 4*M_PI*1e-7;      // Tm/A
    double  c =2.998e+8;              // m/s
//    double  freq = 2.45e+9;           // Hz
    double  freq = 26e+9;           // Hz
    double  antennaHeight = 1.8; //m

    double lambda;
    // double alpha;
    // double beta;
    double Beta = 2*M_PI*freq*sqrt(muAir*epsilonAir); // Used for the diffraction.

    // complex <double> gamma;
    double power = 0;
    double diffractedPower = 0;


    double  Ra = 71.0;   // Ohms, its a typical resistance data for \lambda/2 emettors
    struct Drawer;

    // Algo parameters
    int ray_counter;
    vector< vector <ray*>> allRays;  // Declaring the multi-ray vector
    vector < vector <ray*>> allDiffractedRays;

    vector <ray*> completeRay;
    vector <ray*> current; // algo power

    complex <double> Efield = 0;
    complex <double> totalEfield = 0.0;


    //lineo *current_wall = NULL;
    lineo *current_ray;
    QLineF lineToVirtualSource;

    int recursionState = 0;
    wall* wallRecursiveNumber[9];
    double transmitterSerie[9][2];


    double angle_wall;
    qreal x2wall;
    qreal y2wall;

    double imCoordinates[2];

    // Wall parameters
    double wallThickness;
    double wallSigma;
    double wallEps;
    double epsilonWallRel;

    // Problem parameters
    int reflectionsNumber;
    unsigned int amount_walls = 18;
    int amount_useless_walls = 10;
    unsigned int amount_all_walls = 28;
    int amount_discret = 20;
    map<char,int[4]> streets;

    double minLength, maxLength;
    double *Data;
    bool coverageDone = false;

//    double powerEmettor = 20.0;   // In watts the power of the emettor
    double powerEmettor = 2.0;   // In watts the power of the emettor
    double Zwall;
    double eps;
    bool diffractOn = false;


    // Results
    double resultsBinaryDebit;
    double powerReceived;

// ---------- Methods ------------------------

    // Computation methods
    void imagesMethod(double transmitterPosX,double transmitterPosY ,double reveiverPosX,double receiverPosY, int numberOfReflections);
    void recursion(double transmitterPosX, double transmitterPosY, double receiverPosX, double receiverPosY, int numberOfReflections, void (*draw)(double, double, double, double, room *));
    static void drawRay(double TransmitterImagePosX, double TransmitterImagePosY, double OriginX, double OriginY, room *scene);
    static void buildRay(double TransmitterPosX, double TransmitterPosY, double OriginX, double OriginY, room *scene);
    bool intersectionCheck(lineo* line1, lineo* line2);
    bool intersectionCheckNonInclusive(lineo* line1, lineo* line2);
    bool checkTransmission(lineo* line1, lineo* line2, int x1, int y1,int x2,int y2);
    static void drawDiffraction(room* scene);
    static void buildDiffraction(room* scene);
    bool workingZone();
    void setUpStreets();

    // Numerical analysis

    complex <double> FtIntegral(double x);

    // Geometric methods
    //bool pointOnLine(lineo* line1, double x, double y);
    bool pointOnLine(lineo* line1, const double xp, const double yp);
    bool pointOnLineNonInclusive(lineo* line1, const double xp, const double yp);
    vector<double> intersection(lineo* line1, lineo* line2 );

    double distInWall(double tetai);
    void distCorrection(vector<ray*> oneCompleteRay, wall walls[]);

    bool commonToAnyWall(double posX, double posY, int indWall);

    void drawWalls();
    void findDiffractionPoints();

    // Telecom calculation tools
    double dBm(double power);
    double dBmRev(double dbm);
    double binaryDebit(double power);

    double diffractedRayPower(ray* rayReceiver, ray*rayTransmitter);

    //Misc
    void setDefaultSettings();

    double computePrx(complex <double> totalEfield);
    complex <double> computeEfield(vector<ray*> rayLine);
    double computeReflexionPar(double thetaI, double epsilonR);
    double computeReflexionPer(double thetaI, double epsilonR);
    complex <double> computeEfieldGround();

public slots:


};

#endif // ROOM_H
