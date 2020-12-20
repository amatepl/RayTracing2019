#include "graphicsheatmap.h"

//--------------------------------------------------------------------------------------------
//
//          Class GraphicsTile
//
//--------------------------------------------------------------------------------------------
GraphicsTile::GraphicsTile(const double eField, int x, int y, int width, int height, QGraphicsItem *parent ):
      QGraphicsRectItem(x, y, width, height, parent), m_eField(eField)
{

}

void GraphicsTile::hoverEnterEvent(QGraphicsSceneHoverEvent */*event*/)
{
    eField(m_eField);
}

//--------------------------------------------------------------------------------------------
//
//          Class GraphicsHeatmap
//
//--------------------------------------------------------------------------------------------

GraphicsHeatMap::GraphicsHeatMap(HeatMap *heatMap, QGraphicsScene *scene, Mode mode):
      m_heatMap(heatMap), m_scene(scene), m_mode(mode)
{
    if (m_mode == GraphicsHeatMap::Mode::field) {
        for (const auto &tile: *heatMap){
            GraphicsTile *gtile = new GraphicsTile(abs(tile.eField), tile.pos.x(), tile.pos.y(), tile.sz, tile.sz);
            QColor color;
            color.setHsv(200/pow(10, abs(tile.eField)), 255,255 - 200/ pow(10, abs(tile.eField)));
            gtile->setBrush(QBrush(color));
            gtile->setPen(QPen(color));
            gtile->setAcceptHoverEvents(true);
            connect(gtile, &GraphicsTile::eField, this, &GraphicsHeatMap::updateEField);
            m_tiles.push_back(gtile);
        }
    } else if (m_mode == GraphicsHeatMap::Mode::prx) {
        drawPrxTile(heatMap);
    }
    draw<QGraphicsRectItem>(m_tiles);
}

void GraphicsHeatMap::drawPrxTile(HeatMap* heatmap)
{
    for (const auto &tile: *heatmap){
//        cout << "Tile power: "<< tile.eField<<endl;
GraphicsTile *gtile = new GraphicsTile(10*log10(abs(tile.eField)) + 30, tile.pos.x(), tile.pos.y(), tile.sz, tile.sz);
        QColor color;
        color.setHsv(200/pow(10, abs(tile.eField)*pow(10,8)), 255,255 - 200/ pow(10, abs(tile.eField)*pow(10,8)));
//        color.setHsv(abs(tile.eField) * 2, 255,255 - 200/ pow(10, abs(tile.eField)));
//        color.setHsv((abs(tile.eField) - 40)* 255 / 100 , 255,255 - (abs(tile.eField) - 20)*200/110);
        gtile->setBrush(QBrush(color));
        gtile->setPen(QPen(color));
        gtile->setAcceptHoverEvents(true);
        connect(gtile, &GraphicsTile::eField, this, &GraphicsHeatMap::updateEField);
        m_tiles.push_back(gtile);
    }
}

void GraphicsHeatMap::clear()
{
    for (auto &tile: m_tiles){
        delete tile;
    }
    m_tiles.clear();
    m_heatMap->clear();
}

void GraphicsHeatMap::updateEField(double eField)
{
    GraphicsHeatMap::eField(eField);
}
