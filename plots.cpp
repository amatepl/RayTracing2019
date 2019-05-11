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

    QVector<double> logD(lengthData), Prx(lengthData), pathLoss(lengthData), fading(lengthData);
    for (int i=0; i<(lengthData); ++i){
        logD[i] = log10(Data[(i+bias)*rows+TxIndex_j+totalArea*3]);
        Prx[i] = Data[(i+bias)*rows+TxIndex_j];
    }

    // Plot Path Loss (linear regression y = mx + b); m/10 = path loss exponent
    double m , b, r;
    linreg(lengthData, logD, Prx, &m, &b, &r);
    for (int i=0; i<(lengthData); ++i){
        pathLoss[i] = m*logD[i]+b;
        fading[i] = Prx[i]-pathLoss[i];
    }

    // Fading variability (standard deviation)
    double fadingVariability = findStandardDeviation(fading);

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



    // Cell Range vs Probability
    plotCellRange(m, b, fadingVariability);
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

void plots::plotCellRange(double m, double b, double fadingVariability){
    // minDBM = <Prx> - L_fading
    // <Prx> = mx + b; where x = log10(d) 
    // Pr[L_fading<gamma] = 1 - 1/2* erfc(gamma/(fadingVariability * sqrt(2)))

    // Sweep gamma [0; 3*fadingVariability] => Compute probability Pr[L_fading<gamma] for each gamma => plot R vs Pr
    int lengthData = 100;
    double step = (3*fadingVariability)/lengthData;
    double gamma;
    QVector<double> Pr(lengthData), cellRange(lengthData);
    for (int i=0; i<lengthData; ++i){
        gamma = i*step;
        Pr[i] = 1 - 0.5*erfc(gamma/(fadingVariability * sqrt(2)));// Pr[L_fading<gamma]

        // -102[dBm] = mx + b - gamma[dBm] => x = (-102 + gamma - b)/m => log10(d) = (-102 + gamma - b)/m => d = 10((-102 + gamma - b)/m)
        cellRange[i] = pow(10,(-102 + gamma - b)/m);
    }


    // Plot Range vs Probability
    // create graph and assign data to it:
    ui->customPlot_2->addGraph();
    ui->customPlot_2->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot_2->graph(0)->setData(Pr, cellRange);

    // give the axes some labels:
    ui->customPlot_2->xAxis->setLabel("Connection probability");
    ui->customPlot_2->yAxis->setLabel("Cell range[m]");
    ui->customPlot_2->rescaleAxes();
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_2->replot();

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(ui->customPlot_2);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText(QString("For a minimal received power of -102 dBm"));
    textLabel->setFont(QFont(font().family(), 10)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text
}
