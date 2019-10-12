#include "Model.h"

Model::Model(QGraphicsScene *scene)
{
    QPointF p1(50,50),p2(800,800);
    Building building1(1,1,1,200,200,200,200,1,scene);
    Building building2(250, 1,250, 200,450, 200,450, 1,scene);
    Building building3(500, 1, 500, 200,700, 200, 700, 1,scene);
    Building building4(750, 1, 750, 200,950, 200, 950, 1,scene);
    Building building5(1, 300, 1, 500,200, 500, 200, 300,scene);
    Building building6(250, 300, 250, 500,600, 500, 600, 300,scene);
    Building building7(650, 300, 650, 500,950, 500, 950, 300,scene);

}

