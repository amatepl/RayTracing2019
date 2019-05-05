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

void plots::plotPathLoss(double *Data, int TxIndex_i, int TxIndex_j, int amount_discret){
    unsigned char discret = amount_discret;
    QVector<double> logD(discret-TxIndex_i-1), Prx(discret-TxIndex_i-1);
    for (int i=0; i<(discret-TxIndex_i-1); ++i){
        logD[i] = log10(Data[(i+TxIndex_i+1)*discret+TxIndex_j+((int)(discret*ceil(double(950/500))) * (int)amount_discret)*3]);
        Prx[i] = Data[(i+TxIndex_i+1)*discret+TxIndex_j];
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
