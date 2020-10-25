#ifndef GRAPHICSHEATMAP_H
#define GRAPHICSHEATMAP_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Icludes */

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <iostream>

/* Project Specific */

#include "Product/heatmap.h"

//--------------------------------------------------------------------------------------------
//
//          Defines
//
//--------------------------------------------------------------------------------------------

using GraphicsTile = QGraphicsRectItem;
using namespace std;

//--------------------------------------------------------------------------------------------
//
//          Class GraphicsHeatmap
//
//--------------------------------------------------------------------------------------------

class GraphicsHeatMap
{
public:
    GraphicsHeatMap(HeatMap *heatMap, QGraphicsScene *scene);
    void draw(vector<QGraphicsItem *> &tiles);

    template<class T>
    void draw(vector<T *> &tiles)
    {
        for (auto &t: tiles){
            m_scene->addItem(t);
        }
    }
    void clear();

private:
    HeatMap *m_heatMap;
    QGraphicsScene *m_scene;
    vector<QGraphicsRectItem *> m_tiles;
};

#endif // GRAPHICSHEATMAP_H
