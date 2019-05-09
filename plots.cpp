#include "plots.h"
#include "ui_plots.h"
#include "room.h"

plots::plots(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plots)
{
    /*
     * We use an inherited QDialog for a popup window, which does not effect the other windows *plots->show() allow movement, *plots->open() blocks other windows from
     * interacting.
     */

    ui->setupUi(this);
}

plots::~plots()
{
    delete ui;
}

void plots::plotPathLoss(room *scene){
    double *Data = scene->getData();
    int TxIndex_i = 0;
    int TxIndex_j = 0;
    scene->getDataIndices(scene->getTransmitter()->getPosX(), scene->getTransmitter()->getPosY(), TxIndex_i , TxIndex_j );
    int rows = scene->getRows();
    int columns = scene->getColumns();
    int totalArea = scene->getTotalArea();

     int lengthData = 0;
     int bias = 0;
     double minDist = scene->getMinimalDistance();
     double square_size = scene->getSquare_size();
     float pxToMeter = scene->getPxToMeter();
     int distMinBias = ceil(minDist/(square_size*pxToMeter));
     if(TxIndex_i <= columns/2){
         lengthData = columns-TxIndex_i-1;
         bias = TxIndex_i+1+distMinBias;
     }else{
         lengthData = TxIndex_i-1;
         bias = 0;
     }

     lengthData -= distMinBias;

     QVector<double> logD(lengthData), Prx(lengthData);
     for (int i=0; i<(lengthData); ++i){
         logD[i] = log10(Data[(i+bias)*rows+TxIndex_j+totalArea*3]);
         Prx[i] = Data[(i+bias)*rows+TxIndex_j];
     }

     // create graph and assign data to it:
     ui->customPlot->addGraph();
     ui->customPlot->graph(0)->setData(logD, Prx);

     // give the axes some labels:
     ui->customPlot->xAxis->setLabel("Log(d)");
     ui->customPlot->yAxis->setLabel("Prx[dbm]");
     ui->customPlot->replot();
     ui->customPlot->rescaleAxes();
}
