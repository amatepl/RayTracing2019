#include "coverage.h"
#include "gnuplot-cpp//gnuplot_i.hpp"    // Interfacing with GNUplot to display the heatmap


/*
 * The coverage class generates a grid and places for a placed emettor a transmittor for various positions on the map (avoiding the walls), it stores a grid of the
 * binary debit and generate a visual representation of the map.
 *
 * The idea is that the coverage algorithm creates a two-dimensionnal array, which can be input in GNUplot by binary debit, the highest being displayed in green, the
 * lowest in red. The walls are represented in black.
 */


using namespace std;


coverage::coverage(int discretisation, room *initialRoom, MainWindow *w)


{
    // We choose an uniform discretisation, the map is split into a two-dimensionnal grid in wich the data is stored

    disc = discretisation;
    win = w;

    initialEmettor = initialRoom->getTransmitter();
    sceneWidth = 980;     // x in pixels
    sceneHeight = 510;    // y in pixels

    int pixelGrid[disc][disc];
    double binaryDeb[disc][disc];
    double interferenceMap[disc][disc];

    memset(pixelGrid, 0, sizeof(int) * disc * disc);         // Sets the grid to zero, where "0" --> empty space, "1" wall section, "2" emettor
    memset(binaryDeb, 0.0, sizeof(double) * disc * disc);    // Sets the grid to zero, where "0" --> empty space, "1" wall section, "2" emettor
    memset(interferenceMap, 0.0, sizeof(double) * disc * disc);    // Sets the grid to zero, where "0" --> empty space, "1" wall section, "2" emettor

    // Setting initial discretisation of the room -------------------------------------------------------------------------------------------------

        //Placing the emettor
        double posY = initialEmettor->getPosY();
        double posX = initialEmettor->getPosX();

        int y_emettor = round(disc*(posY/sceneWidth));     // i indice for the emettor
        int x_emettor = round(disc*(posX/sceneHeight));    // j indice for the emettor

        pixelGrid[y_emettor][x_emettor] = 2;

        //Placing the walls
        int amountWalls = initialRoom->getAmountWalls();

        for(int i = 0; i < amountWalls; i++){
            wall *current_wall = initialRoom->getWalls(i);

            double x1 = current_wall->getX1();
            double y1 = current_wall->getY1();
            double x2 = current_wall ->getX2();
            double y2 = current_wall->getY2();

            // Converting to discret form
            int X1p = round(disc*(x1/sceneWidth));
            int Y1p = round(disc*(y1/sceneHeight));
            int X2p = round(disc*(x2/sceneWidth));
            int Y2p = round(disc*(y2/sceneHeight));

            if(X1p == X2p && Y1p < Y2p){
                for(int j = Y1p; j < Y2p; j++){
                    pixelGrid[X1p][j] = -1;
                }
            }
            else if(X1p == X2p && Y1p > Y2p){
                for(int j = Y2p; j < Y1p; j++){
                    pixelGrid[X1p][j] = -1;
                }
            }
            else if(Y1p == Y2p && X1p < X2p){
                for(int j = X1p; j <= X2p; j++){
                    pixelGrid[j][Y1p] = -1;
                        }
                    }
            else if(Y1p == Y2p && X1p > X2p){
                for(int j = X2p; j <= X1p; j++){
                    pixelGrid[j][Y1p] = -1;
                }
            }
        }

    // *** Launching algorithm *** --------------------------------------------------------------------------------------------------------------

        // Binary Debit
        for(int j = 0; j < disc; j++){
            for(int i = 0; i < disc; i++){

                room *newRoom = new room(win);

                if(pixelGrid[i][j] == 0){

                    // We set the middle of each square as the new coordinates of the moving receptor
                    int y_new = (int) sceneHeight/(2*disc) + j*(sceneHeight)/disc;
                    int x_new = (int) sceneWidth/(2*disc) + i*(sceneWidth)/disc;

                    QPointF *pos = new QPointF(x_new, y_new);

                    antena *newAntena = new antena(initialRoom, *pos, 1);

                    newRoom->setTransmitter(initialRoom->getTransmitter());
                    newRoom->setReceiver(newAntena);
                    newRoom->launch_algo();

                    double binaryDebit = newRoom->getBinaryDebit();
                    binaryDeb[i][j] = binaryDebit;

                }else if(pixelGrid[i][j] == -1){
                    binaryDeb[i][j] = INFINITY;
                }else if(pixelGrid[i][j] == 2){
                    binaryDeb[i][j] = newRoom->getInitBinaryDeb();
                }
          }
      }

/*

        // Zone de couverture exacte

        for(int j = 0; j < disc; j++){
            for(int i = 0; i < disc; i++){
                if(pixelGrid[i][j] == 0){

                    // We set the middle of each square as the new coordinates of the moving receptor
                    int y_new = (int) sceneHeight/(2*disc) + j*(sceneHeight)/disc;
                    int x_new = (int) sceneWidth/(2*disc) + i*(sceneWidth)/disc;

                    QPointF *pos = new QPointF(x_new, y_new);

                    antena *newAntena = new antena(initialRoom, *pos, 1);
                    initialRoom->setReceiver(newAntena);
                    initialRoom->launch_algo();

                    double binaryDebit = initialRoom->getBinaryDebit();

                    if(binaryDebit <= 6){
                        binaryDeb[j][i] = 0.0;
                    }else if(binaryDebit >= 56){
                        binaryDeb[j][i] = 56;
                    }else{binaryDeb[j][i] = binaryDebit;}

                    if(maxDebit < binaryDebit){maxDebit = binaryDebit;}   // Saving the maximum debit gotten

                }else if(pixelGrid[j][i] == -1){
                    binaryDeb[j][i] = INFINITY;
                }else if(pixelGrid[j][i] == 2){
                    binaryDeb[j][i] = initialRoom->getInitBinaryDeb();
                }
          }
      }
*/
        // Interference map

        /*
        for(int j = 0; j < disc; j++){
            for(int i = 0; i < disc; i++){
                if(pixelGrid[i][j] == 0){

                    // We set the middle of each square as the new coordinates of the moving receptor
                    int y_new = (int) sceneHeight/(2*disc) + j*(sceneHeight)/disc;
                    int x_new = (int) sceneWidth/(2*disc) + i*(sceneWidth)/disc;

                    QPointF *pos = new QPointF(x_new, y_new);

                    antena *newAntena = new antena(initialRoom, *pos, 1);
                    initialRoom->setReceiver(newAntena);
                    initialRoom->launch_algo();

                    double EfieldNorm = norm((initialRoom->getTotalEfield()));
                    interferenceMap[i][j] = EfieldNorm;

                }else if(pixelGrid[i][j] == -1){
                    interferenceMap[i][j] = -INFINITY;
                }else if(pixelGrid[i][j] == 2){
                    interferenceMap[i][j] =0.0;
                }
          }
      }
*/


    // Saving results

        ofstream binaryDebitData;//, EfieldData;
        // Deleting the previous results (a function to save properly might be made later on)

        binaryDebitData.open("binaryData.txt",ios::out | ios::trunc);
        //EfieldData.open("efieldData.txt",ios::out | ios::trunc);

        binaryDebitData.close();
        //EfieldData.close();


        // Convert and write results to gnuplot
        binaryDebitData.open("binaryData.txt", ios::in | ios::app);
        //EfieldData.open("efieldData.txt", ios::in | ios::app);


        string myLine1 = "";
        string myLine2 = "";


        for (int i = 0; i < disc; i++){
            myLine1 = "";
            myLine2 = "";

            for (int j = 0; j < disc; j++){
                myLine1 += to_string(binaryDeb[i][j]) + " ";
                //myLine2 += to_string(interferenceMap[i][j]) + " ";

            }
            binaryDebitData << myLine1 + "\n";
            //EfieldData << myLine2 + "\n";

        }

        //EfieldData.close();
        binaryDebitData.close();

        // Calling GNUplot
        show_results();
}


// --> GNUplot methods and interfaces

void coverage::show_results(){
    /*
     * Interfaces C++ with GNU to display the heat map relative to the binaryDebit() results. The call opens up GNUplot and launch the datastream, the scare must be worked
     * on too.
     */


    // Binary debit

    Gnuplot g1;

    cout << "*** plotting the coverage map ***" << endl;

    g1.set_title("Coverage map of the level");
    //g1.cmd("set pm3d map");
    g1.cmd("plot 'binaryData.txt' matrix with image");

    g1.showonscreen(); // window output
    wait_for_key();
/*

    Gnuplot g2;

    cout << "*** plotting the interference map ****" << endl;

    g2.set_title("Interference map of the norm of the electric field");
    g2.cmd("plot 'efieldData.txt' matrix with image");

    g2.showonscreen(); // window output
    wait_for_key();
    */
}

// --> Getters && Setters

void coverage::wait_for_key()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}
