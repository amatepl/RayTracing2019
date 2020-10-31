#include "graphicsheatmap.h"

GraphicsHeatMap::GraphicsHeatMap(HeatMap *heatMap, QGraphicsScene *scene): m_heatMap(heatMap), m_scene(scene)
{
//    double maxe = 0;
//    double mine = 1;
    for (const auto &tile: *heatMap){
//        m_tiles.push_back(QGraphicsRectItem(tile.pos.x(), tile.pos.y(), 10, 10));
        QGraphicsRectItem *gtile = new QGraphicsRectItem(tile.pos.x(), tile.pos.y(), tile.sz, tile.sz);
        QColor color;
        color.setHsv(200/pow(10, abs(tile.eField)), 255,255 - 200/ pow(10, abs(tile.eField)));
        gtile->setBrush(QBrush(color));
        gtile->setPen(QPen(color));
        m_tiles.push_back(gtile);

//        if (mine > abs(tile.eField))
//            mine = abs(tile.eField);
//        else if (maxe < abs(tile.eField)) {
//            maxe = abs(tile.eField);
//        }

//        if (abs(tile.eField) != 0)
//            cout<<"Pos: " << tile.pos.x() << ", " << tile.pos.y() << " E filed: " << abs(tile.eField)<<endl;
    }

//    cout << "Min: " << mine << " Max: " << maxe << endl;
    draw<QGraphicsRectItem>(m_tiles);

}

//void GraphicsHeatMap::draw(vector<QGraphicsItem *> &tiles)
//{
//    for (auto &tile: tiles){
//        m_scene->addItem(tile);
//    }
//}

void GraphicsHeatMap::clear()
{
    for (auto &tile: m_tiles){
        delete tile;
    }
    m_tiles.clear();
    m_heatMap->clear();
}
