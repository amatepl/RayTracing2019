#include "plots.h"
#include "ui_plots.h"

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

void plots::plotPathLoss(double *Data, int TxIndex_i, int TxIndex_j, int rows, int columns, int totalArea){
//    QVector<double> logD(columns-TxIndex_i-1), Prx(columns-TxIndex_i-1);
//    for (int i=0; i<(columns-TxIndex_i-1); ++i){
//        logD[i] = log10(Data[(i+TxIndex_i+1)*rows+TxIndex_j+totalArea*3]);
//        Prx[i] = Data[(i+TxIndex_i+1)*rows+TxIndex_j];
//    }

    int lengthData = 0;
    int bias = 0;
    if(TxIndex_i <= columns/2){
        lengthData = columns-TxIndex_i-1;
        bias = TxIndex_i+1;
    }else{
        lengthData = TxIndex_i-1;
    }

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
