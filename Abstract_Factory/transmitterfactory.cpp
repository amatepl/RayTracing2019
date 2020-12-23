#include "transmitterfactory.h"

TransmitterFactory::TransmitterFactory(QMenu* productmenu, QGraphicsScene* scene,const float scale)
{
    m_productmenu = productmenu;
    m_scene = scene;
    px_to_meter = scale;
}


GraphicsProduct* TransmitterFactory::createGraphicsProduct(int posX, int posY){
    GraphicsTx* graphicsProduct = new GraphicsTx(m_productmenu, m_scene);
    Tx* mathematicalProduct = new Tx(posX, posY);
    mathematicalProduct->setScale(px_to_meter);
    graphicsProduct->attachObserver(mathematicalProduct);
    graphicsProduct->setX(posX);
    graphicsProduct->setY(posY);
    mathematicalProduct->MathematicalProduct::attachObservable(graphicsProduct);
//    DerivedDialogWinFctry <DialogTx, QDialog, TxInterface> fctry (dynamic_cast<TxInterface*>(mathematicalProduct));//;= new DerivedDialogWinFctry(dynamic_cast<TxInterface*>(mathematicalProduct));
    DerivedDialogWinFctry <DialogTx, QDialog, TxInterface> *fctry = new DerivedDialogWinFctry <DialogTx, QDialog, TxInterface> (mathematicalProduct);
    graphicsProduct->setDialogFctry(fctry);
    double rad = 1;
    vector<QPointF> pl_points = mathematicalProduct->pathLossPoints();
    for (unsigned i = 0; i < pl_points.size(); i++)
    {
        m_scene->addEllipse(pl_points.at(i).x()-rad, pl_points.at(i).y()-rad, rad*2.0, rad*2.0,
            QPen(QColor(Qt::red)), QBrush(Qt::SolidPattern));
    }

    return graphicsProduct;
}

MathematicalProduct* TransmitterFactory::createMathematicalProduct(int posX, int posY, bool linkgraphic){
    Tx* mathematicalProduct = new Tx(posX,posY);
    mathematicalProduct->setScale(px_to_meter);
    if (linkgraphic){
        GraphicsTx* graphicsProduct = new GraphicsTx(m_productmenu, m_scene);

        graphicsProduct->attachObserver(mathematicalProduct);
//        graphicsProduct->setX(posX);
//        graphicsProduct->setY(posY);
//        mathematicalProduct->MathematicalProduct::attachObservable(graphicsProduct);
    }
    return mathematicalProduct;
}
