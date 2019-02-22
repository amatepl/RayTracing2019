#include "wall.h"
#include <math.h>

wall::wall(room *scene,qreal x01, qreal y01, qreal x02, qreal y02, double thickness, double relEps, double sig, int listInd):
    lineo(x01, y01, x02, y02, scene)

  /*
   * inherits from lineo, basic line function to be called when interacting with rays
   */

{
    thick = thickness;
    epsilon = relEps;
    sigma = sig;
    indWall = listInd;
}

// --> Getters && Setters

double wall::getEpsilon(){return thick;}
double wall::getSigma(){return epsilon;}
double wall::getThick(){return sigma;}
int wall::getIndWall(){return indWall;}
