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

/*!
 * \class GraphicsTile
 *
 * A graphics tile is a single element of a GraphicsHeatMap.
 *
 * It manages the curser hoverEnterEvent by signaling the value of the electric
 * field or power encoded in the tile.
 */
class GraphicsTile:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    /*!
     * \fn GraphicsTile::GraphicsTile(const double eField, int x, int y, int width, int height,
                 QGraphicsItem *parent = nullptr)
     *
     * GrphicsTile constructor.
     *
     * It take as parameters \a eField which is the local electric field of
     * power, \a x and \a y which is the position at which the the eletric field
     * or power was computed, \a heigth and \a width which are the height and width
     * of the tile. Those should be proportional to the heatmap density.
     */
    GraphicsTile(const double eField, int x, int y, int width, int height,
                 QGraphicsItem *parent = nullptr);

signals:
    /*!
     * \brief eField
     */
    void eField(double eField);
protected:
    double m_eField;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
};

//--------------------------------------------------------------------------------------------
//
//          Class GraphicsHeatmap
//
//--------------------------------------------------------------------------------------------

/*!
 * \brief The GraphicsHeatMap class
 */
class GraphicsHeatMap: public QObject
{
    Q_OBJECT
public:
    enum class Mode {field, prx};
    GraphicsHeatMap(HeatMap *heatMap, QGraphicsScene *scene, Mode mode=Mode::field);
    void drawPrxTile(HeatMap *heatmap);
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
    Mode m_mode {Mode::field};
};

#endif // GRAPHICSHEATMAP_H
