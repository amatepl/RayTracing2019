#include "Model.h"

Model::Model(AbstractScene *scene)
{
    QPointF p1(50,50),p2(800,800);
    //Building building1(1,1,1,200,200,200,200,1,scene);
    Building *building1 = new Building(1,1,1,200,200,200,200,1,scene);
    Building *building2 = new Building(250, 1,250, 200,450, 200,450, 1,scene);
    Building *building3 = new Building(500, 1, 500, 200,700, 200, 700, 1,scene);
    Building *building4 = new Building(750, 1, 750, 200,950, 200, 950, 1,scene);
    Building *building5 = new Building(1, 300, 1, 500,200, 500, 200, 300,scene);
    Building *building6 = new Building(250, 300, 250, 500,600, 500, 600, 300,scene);
    Building *building7 = new Building(650, 300, 650, 500,950, 500, 950, 300,scene);

}

vector <Building*> Model::inIlluminationZone()
{

}
