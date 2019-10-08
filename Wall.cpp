#include "Wall.h"
#include <math.h>

Wall::Wall(double x01, double y01, double x02, double y02, double thickness, double relEps, double sig, int listInd):
    Line(x01, y01, x02, y02),thick(thickness),epsilon(relEps),sigma(sig),indWall(listInd)

  /*
   * inherits from Line, basic line function to be called when interacting with rays
   */

{

}

// --> Getters && Setters
Wall::~Wall(void){

}

double Wall::getEpsilon() const{return thick;}
double Wall::getSigma() const{return epsilon;}
double Wall::getThick() const{return sigma;}
int Wall::getIndWall() const{return indWall;}
