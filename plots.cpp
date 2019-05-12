#include "plots.h"
#include "ui_plots.h"
#include "room.h"
#include <stdlib.h>
#include <math.h>
// Libraries
#include <complex>

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
    if(scene->DataComputed()){
        ui->tabWidget->setCurrentWidget(ui->tab_1);
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

        QVector<double> D(lengthData), logD(lengthData), Prx(lengthData), pathLoss(lengthData), fading(lengthData);
        for (int i=0; i<(lengthData); ++i){
            D[i] = Data[(i+bias)*rows+TxIndex_j+totalArea*3];
            logD[i] = log10(D[i]);
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
        ui->customPlot_1->addGraph();
        ui->customPlot_1->graph(0)->setPen(QPen(Qt::blue));
        ui->customPlot_1->graph(0)->setData(D, Prx);

        ui->customPlot_1->addGraph();
        ui->customPlot_1->graph(1)->setPen(QPen(Qt::red));
        ui->customPlot_1->graph(1)->setData(D, pathLoss);

        // give the axes some labels:
        ui->customPlot_1->xAxis->setLabel("Distance[m]");
        ui->customPlot_1->yAxis->setLabel("Prx[dbm]");
        ui->customPlot_1->xAxis->setScaleType(QCPAxis::stLogarithmic);
        ui->customPlot_1->yAxis->grid()->setSubGridVisible(true);
        ui->customPlot_1->xAxis->grid()->setSubGridVisible(true);
        ui->customPlot_1->rescaleAxes();
        ui->customPlot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->customPlot_1->replot();

        // add the text label at the top:
        QCPItemText *textLabel = new QCPItemText(ui->customPlot_1);
        textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
        textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
        textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
        textLabel->setText(QString("Path Loss Exponent = ") + QString::number(abs(m/10)) + QString("\n") + QString("Std Deviation[dB] = ") + QString::number(fadingVariability));
        textLabel->setFont(QFont(font().family(), 10)); // make font a bit larger
        textLabel->setPen(QPen(Qt::black)); // show black border around text

        // Plot model
        plotModel(m, b, fadingVariability);

        // Cell Range vs Probability
        plotCellRange(m, b, fadingVariability);
    }

    if(scene->getRayNumber()>0){
        ui->tabWidget->setCurrentWidget(ui->tab_5);
        // Physical impulse response
        physicalImpulseResponse(scene);
        TDLImpulseResponse(scene);
        TDL_US(scene);
    }
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
    double res = sqrt(sDeviation/count);
    if(res<1e-5){res = 0;}
    return res;
}



//  Create the plots

void plots::plotModel(double m, double b, double fadingVariability){
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, fadingVariability);

    double minDist = log10(10); //m
    double maxDist = log10(50000);// 50km
    double step = 0.01;
    int lengthData = (maxDist-minDist)/step;
    QVector<double> D_model(lengthData), logD_model(lengthData), Prx_model(lengthData), pathLoss_model(lengthData), threshold(lengthData);
    double L_fading_model;
    for (int i=0; i<lengthData; ++i){
        logD_model[i] = minDist + i*step;
        D_model[i] = pow(10, logD_model[i]);
        pathLoss_model[i] =  m*logD_model[i] + b;
        L_fading_model = distribution(generator);
        Prx_model[i] = pathLoss_model[i] + L_fading_model;
        threshold[i] = -102;
    }

    // create graph and assign data to it:
    ui->customPlot_2->addGraph();
    ui->customPlot_2->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot_2->graph(0)->setData(D_model, Prx_model);

    ui->customPlot_2->addGraph();
    ui->customPlot_2->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot_2->graph(1)->setData(D_model, pathLoss_model);

    ui->customPlot_2->addGraph();
    ui->customPlot_2->graph(2)->setPen(QPen(Qt::green));
    ui->customPlot_2->graph(2)->setData(D_model, threshold);

    // give the axes some labels:
    ui->customPlot_2->xAxis->setLabel("Distance[m]");
    ui->customPlot_2->yAxis->setLabel("Prx[dbm]");
    ui->customPlot_2->xAxis->setScaleType(QCPAxis::stLogarithmic); 
    ui->customPlot_2->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot_2->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot_2->rescaleAxes();
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_2->replot();

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(ui->customPlot_2);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText(QString("Path Loss Exponent = ") + QString::number(abs(m/10)) + QString("\n") + QString("Std Deviation[dB] = ") + QString::number(fadingVariability));
    textLabel->setFont(QFont(font().family(), 10)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text
}


void plots::plotCellRange(double m, double b, double fadingVariability){
    // minDBM = <Prx> - L_fading     (minDBM = -102dBm)
    // <Prx> = mx + b; where x = log10(d) 
    // Pr[L_fading<gamma] = 1 - 1/2* erfc(gamma/(fadingVariability * sqrt(2)))

    // Sweep gamma [0; 3*fadingVariability] => Compute probability Pr[L_fading<gamma] for each gamma => Compute R such that minDBM = <Prx(R)> - gamma
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
    ui->customPlot_3->addGraph();
    ui->customPlot_3->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot_3->graph(0)->setData(Pr, cellRange);

    // give the axes some labels:
    ui->customPlot_3->xAxis->setLabel("Connection probability");
    ui->customPlot_3->yAxis->setLabel("Cell range[m]");
    ui->customPlot_3->yAxis->setScaleType(QCPAxis::stLogarithmic); 
    ui->customPlot_3->rescaleAxes();
    ui->customPlot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_3->replot();

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(ui->customPlot_3);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText(QString("For a minimal received power of -102 dBm"));
    textLabel->setFont(QFont(font().family(), 10)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text
}


void plots::physicalImpulseResponse(room* scene){
    int rayNumber = scene->getRayNumber();
    double *channelData = scene->getChannelData();
    double  c =2.998e+8; // m/s

    QVector<double> h(rayNumber), tau(rayNumber);
    for (int i=0; i<(rayNumber); ++i){
        h[i] = 10*log10(abs(channelData[i])); // alpha
        tau[i] = channelData[i+20]/c*1e9; // tau

        QCPItemLine *line = new QCPItemLine(ui->customPlot_4);
        line->start->setCoords(tau[i], h[i]);  // location of point 1 in plot coordinate
        line->end->setCoords(tau[i], -100);  // location of point 2 in plot coordinate

        // For the TDL plot
        QCPItemLine *line2 = new QCPItemLine(ui->customPlot_6);
        line2->start->setCoords(tau[i], h[i]);  // location of point 1 in plot coordinate
        line2->end->setCoords(tau[i], -100);  // location of point 2 in plot coordinate
        line2->setPen(QPen(Qt::blue));
    }

    // Plot physiscal impulse response
    ui->customPlot_4->addGraph();
    ui->customPlot_4->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot_4->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_4->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    ui->customPlot_4->graph(0)->setData(tau, h);

    // give the axes some labels:
    ui->customPlot_4->xAxis->setLabel("\u03C4[ns]");
    ui->customPlot_4->yAxis->setLabel("h(\u03C4)[dB]");
    ui->customPlot_4->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot_4->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot_4->rescaleAxes();
    ui->customPlot_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_4->replot();


    // Plot together with TDL
    ui->customPlot_6->addGraph();
    ui->customPlot_6->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot_6->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_6->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    ui->customPlot_6->graph(0)->setData(tau, h);
    ui->customPlot_6->graph(0)->setName("Physical");
}

void plots::TDLImpulseResponse(room* scene){
    int rayNumber = scene->getRayNumber();
    double *channelData = scene->getChannelData();
    double  c =2.998e+8; // m/s
    double freq = scene->getCarrierFrequency();
    double minBW = 100e+6;
    double maxBW = 700e+6;
    int lengthData = 200;
    double step = (maxBW-minBW)/lengthData;
    double deltaTau;

    // Sweep Bandwidth BW from 100MHz -> 700 MHz
    QVector<double> BW(lengthData), h_l(lengthData);
    complex <double> h_l_temp[lengthData];
    complex <double> p(0.0, 1.0);
    int l = 0;
    double tau = 0;
    for (int i=0; i<lengthData; ++i){
        BW[i] = minBW + i*step;
        deltaTau = 1/(2*BW[i]);
        h_l[i] = 0;
        h_l_temp[i] = 0;
        for (int j=0; j<(rayNumber); ++j){
            tau = channelData[j+20]/c;
            h_l_temp[i] += channelData[j]*exp(-p * 2.0*M_PI * freq * tau) * (sin(2*BW[i]*(tau-l*deltaTau))/(2*BW[i]*(tau-l*deltaTau)));
        }
        h_l[i] = 10*log10(abs(h_l_temp[i]));
        BW[i] = BW[i]*1e-6;

        QCPItemLine *line = new QCPItemLine(ui->customPlot_5);
        line->start->setCoords(BW[i], h_l[i]);  // location of point 1 in plot coordinate
        line->end->setCoords(BW[i], -100);  // location of point 2 in plot coordinate
    }
    
    // Plot physiscal impulse response
    ui->customPlot_5->addGraph();
    ui->customPlot_5->graph(0)->setPen(QPen(Qt::blue));
//    ui->customPlot_5->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_5->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));

    ui->customPlot_5->graph(0)->setData(BW, h_l);

    // give the axes some labels:
    ui->customPlot_5->xAxis->setLabel("B[MHz]");
    ui->customPlot_5->yAxis->setLabel("h\u2097[dB]");
    ui->customPlot_5->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot_5->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot_5->rescaleAxes();
    ui->customPlot_5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_5->replot();
}

void plots::TDL_US(room* scene){
    int rayNumber = scene->getRayNumber();
    double *channelData = scene->getChannelData();
    double  c = 2.998e+8; // m/s
    double freq = scene->getCarrierFrequency();
    double BW = 100e+6; // Hz
    double deltaTau = 1/(2*BW);

    double x[rayNumber];
    complex <double> y[rayNumber];
    complex <double> p(0.0, 1.0);
    double tau_check;
    for (int i=0; i<(rayNumber); ++i){
        tau_check = channelData[i+20]/c;
        int l = 0;
        while(!(l*deltaTau-deltaTau/2<=tau_check && tau_check<l*deltaTau+deltaTau/2)){
            l++;
        }
        x[i] = l*deltaTau*1e9;
        y[i] = channelData[i] * exp(-p * 2.0*M_PI * freq * tau_check);
    }

    for (int i=0; i<rayNumber; ++i){
        for (int j=0; j<rayNumber; ++j){
            if(i<j && x[i] == x[j]){
                y[i] += y[j];
                y[j] = 0;
            }
        }
    }

    int counter = 0;
    for (int i=0; i<rayNumber; ++i){
        if(y[i]!=0.0){counter++;}
    }

    QVector<double> h_TDL(counter), tau(counter);
    int k = 0, counter2 = 0;
    while(k<rayNumber){
        if(y[k] != 0.0){
            tau[counter2] = x[k];
            h_TDL[counter2] = 10*log10(abs(y[k]));
            QCPItemLine *line = new QCPItemLine(ui->customPlot_6);
            line->start->setCoords(tau[counter2], h_TDL[counter2]);  // location of point 1 in plot coordinate
            line->end->setCoords(tau[counter2], -100);  // location of point 2 in plot coordinate
            line->setPen(QPen(Qt::red));
            counter2++;
        }
        k++;
    }
    
    // Plot physiscal impulse response
    ui->customPlot_6->addGraph();
    ui->customPlot_6->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot_6->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_6->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    ui->customPlot_6->graph(1)->setData(tau, h_TDL);
    ui->customPlot_6->graph(1)->setName("TDL");

    // give the axes some labels:
    ui->customPlot_6->xAxis->setLabel("\u03C4[ns]");
    ui->customPlot_6->yAxis->setLabel("h_TDL(\u03C4)[dB]");
    ui->customPlot_6->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot_6->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot_6->rescaleAxes();
    ui->customPlot_6->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_6->legend->setVisible(true);
    ui->customPlot_6->replot();
}
