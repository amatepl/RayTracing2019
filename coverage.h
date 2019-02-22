#ifndef COVERAGE_H
#define COVERAGE_H

// Dependencies
#include "antena.h"
#include "room.h"
#include "wall.h"
#include "math.h"


// Used libraries
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>

using namespace std;

class room;
class MainWindow;
class antena;
class coverage

{
public:
    coverage(int discretisation,room *initialRoom, MainWindow *w);
    int counter = 0;


private:
    int disc;

    MainWindow *win;

    antena *initialEmettor;
    int sceneWidth;
    int sceneHeight;

    // Results
    double maxDebit = 0;


    // Algorithm methods
    void calculateCoverage();
    void binaryDebit();
    void dBmPower();
    void show_results();

    // GNUplot methods
    void wait_for_key();

    // Getters && Setters

};

#endif // COVERAGE_H
