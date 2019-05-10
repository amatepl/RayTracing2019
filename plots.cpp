#include "plots.h"
#include "ui_plots.h"
#include "room.h"
#include <stdlib.h>
#include <math.h>

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
    double pxToMeter = scene->getPxToMeter();
    int distMinBias = floor(minDist/(square_size*pxToMeter));
    if(TxIndex_i <= columns/2){
        lengthData = columns-TxIndex_i-1;
        bias = TxIndex_i+1+distMinBias;
    }else{
        lengthData = TxIndex_i-1;
        bias = 0;
    }

    lengthData -= distMinBias;

    QVector<double> logD(lengthData), Prx(lengthData), pathLoss(lengthData);
    for (int i=0; i<(lengthData); ++i){
        logD[i] = log10(Data[(i+bias)*rows+TxIndex_j+totalArea*3]);
        Prx[i] = Data[(i+bias)*rows+TxIndex_j];
    }

    // Plot Path Loss (linear regression y = mx + b)
    double m , b, r;
    linreg(lengthData, logD, Prx, &m, &b, &r);
    for (int i=0; i<(lengthData); ++i){
        pathLoss[i] = m*logD[i]+b;
    }

    // Fading variability (standard deviation)
    double fadingVariability = findStandardDeviation(pathLoss);

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(0)->setData(logD, Prx);

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot->graph(1)->setData(logD, pathLoss);

    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("Log(d/1m)");
    ui->customPlot->yAxis->setLabel("Prx[dbm]");
    ui->customPlot->rescaleAxes();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot->replot();

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(ui->customPlot);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText(QString("Path Loss Exponent = ") + QString::number(abs(m/10)) + QString("\n") + QString("Std Deviation[dB] = ") + QString::number(fadingVariability));
    textLabel->setFont(QFont(font().family(), 10)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text
}

int plots::linreg(int n, QVector<double> x, QVector<double> y, double* m, double* b, double* r){
    /*
    n = number of data points
    x,y  = arrays of data
    *b = output intercept
    *m  = output slope
    *r = output correlation coefficient (can be NULL if you don't want it)
    */

    double   sumx = 0.0;                      /* sum of x     */
    double   sumx2 = 0.0;                     /* sum of x**2  */
    double   sumxy = 0.0;                     /* sum of x * y */
    double   sumy = 0.0;                      /* sum of y     */
    double   sumy2 = 0.0;                     /* sum of y**2  */

    for (int i=0;i<n;i++){ 
        sumx  += x[i];       
        sumx2 += pow(x[i],2);  
        sumxy += x[i] * y[i];
        sumy  += y[i];      
        sumy2 += pow(y[i],2); 
    } 

    double denom = (n * sumx2 - pow(sumx,2));
    if (denom == 0) {
        // singular matrix. can't solve the problem.
        *m = 0;
        *b = 0;
        if (r) *r = 0;
            return 1;
    }

    *m = (n * sumxy  -  sumx * sumy) / denom;
    *b = (sumy * sumx2  -  sumx * sumxy) / denom;
    if (r!=NULL) {
        *r = (sumxy - sumx * sumy / n) /    /* compute correlation coeff */
              sqrt((sumx2 - pow(sumx,2)/n) *
              (sumy2 - pow(sumy,2)/n));
    }
    return 0; 
}

double plots::findStandardDeviation(QVector<double> array){
    double sum = 0.0, sDeviation = 0.0, mean;
    int count = array.size();
    int i;
    for(i = 0; i < count; i++) {
        sum += array[i];
    }
    // Calculating mean 
    mean = sum/count;
    for(i = 0; i < count; ++i) {
        sDeviation += pow(array[i] - mean, 2);
    }
    return sqrt(sDeviation/count);
}
