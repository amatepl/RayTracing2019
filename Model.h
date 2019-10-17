#ifndef MODEL_H
#define MODEL_H

//#include "Visualizer.h"
#include <QGraphicsScene>
#include "Building.h"
#include "antena.h"
#include <vector>

class Model
{
public:
    Model(QGraphicsScene *scene);
    vector <Building*> inIlluminationZone();
    void addAntena();

private:
    vector <antena*> m_antennas;
};

#endif // MODEL_H
