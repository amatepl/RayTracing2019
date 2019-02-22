#ifndef ALGO_H
#define ALGO_H

#include "algo.h"
#include "wall.h"
#include "antena.h"
#include "ray.h"

class wall;

class antena;

class ray;

class algo
{
public:
    algo(int n,wall *walls[], antena *Transmitter, antena *Receiver);
    ray returnResults();

protected:
    ray *rays;   // We need an array of rays, which will be read to be displayed
    wall **wallsL;
    int amount_reflect;
    int amount_walls;
    void createRay();
private:
    double a_wall;
    double a_ray_wall;

};

#endif // ALGO_H
