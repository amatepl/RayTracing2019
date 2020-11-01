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

//using GraphicsTile = QGraphicsRectItem;
using namespace std;

//--------------------------------------------------------------------------------------------
//
//          Class GraphicsTile
//
//--------------------------------------------------------------------------------------------

class GraphicsTile:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    GraphicsTile(const double eField, int x, int y, int width, int height, QGraphicsItem *parent = nullptr);

signals:
    void eField(double eField);
protected:
    double m_eField;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
};

//--------------------------------------------------------------------------------------------
//
//          Class GraphicsHeatmap
//
//--------------------------------------------------------------------------------------------

class GraphicsHeatMap: public QObject
{
    Q_OBJECT
public:
    GraphicsHeatMap(HeatMap *heatMap, QGraphicsScene *scene);
    void draw(vector<QGraphicsItem *> &tiles);

    template<class T>
    void draw(vector<T *> &tiles)
    {
        for (auto &t: tiles){
            t->setZValue(-1);
            m_scene->addItem(t);
        }
    }
    void clear();

signals:
    void eField(double eField);

public slots:
    void updateEField(double eField);

private:
    HeatMap *m_heatMap;
    QGraphicsScene *m_scene;
    vector<QGraphicsRectItem *> m_tiles;
};

#endif // GRAPHICSHEATMAP_H
