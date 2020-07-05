#include "dialogreceiverproduct.h"

DialogReceiverProduct::DialogReceiverProduct(ReceiverProduct *mathematicalproduct):
    m_mathematicalproduct(mathematicalproduct)
{
    setWindowTitle("Receiver properties: ");
    setWindowIcon(QIcon(GraphicsReceiverProduct::getImage()));
    setMinimumSize(500,500);

    m_tabwidget = new QTabWidget;
    m_tabwidget->addTab(GeneralTabDialog(), tr("General"));
    m_tabwidget->addTab(PhysicalImpulseResponse(),tr("Impulse Response"));
    //m_tabwidget->addTab(TDLImpulseResponse(),tr("TDL"));
    m_tabwidget->addTab(ModelPathLossDialog(), tr("Model Path-Loss"));
    m_tabwidget->addTab(RealPathLossDialog(), tr("Real Path-Loss"));
    m_tabwidget->addTab(CellRange(),tr("Cellule range"));
    m_tabwidget->addTab(DopplerSpectrum(), tr("Doppler Spectrum"));

    m_buttonbox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addWidget(m_tabwidget);
    mainlayout->addWidget(m_buttonbox);
    setLayout(mainlayout);

    setAttribute(Qt::WA_DeleteOnClose,true);
    connect(m_buttonbox, SIGNAL(rejected()), this, SLOT(close()));
    connect(m_buttonbox, SIGNAL(accepted()), this, SLOT(saveProperties()));
    open();
}

DialogReceiverProduct::~DialogReceiverProduct(){

}

QWidget* DialogReceiverProduct::GeneralTabDialog(){
    QWidget *widget = new QWidget;

    m_posx = new QSpinBox(this);
    m_posy = new QSpinBox(this);
    m_posx->setRange(0,5000);
    m_posx->setAccelerated(true);
    m_posy->setRange(0,5000);
    m_posy->setAccelerated(true);

    m_power = new QLineEdit("Received power [dB]: ", this);
    m_power->setEnabled(false);
    m_e_field = new QLineEdit("Electric fiedl [V/m]: ", this);
    m_e_field->setEnabled(false);

    QFormLayout *geoProperties = new QFormLayout(this);
    geoProperties->addRow("X center: ",m_posx);
    geoProperties->addRow("Y center: ",m_posy);

    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QFormLayout *phyProperties = new QFormLayout(this);
    phyProperties->addRow(m_power);
    phyProperties->addRow(m_e_field);

    QGroupBox *phy = new QGroupBox("Physical properties");
    phy->setLayout(phyProperties);

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(geo,0,0);
    firstLayout->addWidget(phy,1,0);

    widget->setLayout(firstLayout);

    setPosX(m_mathematicalproduct->getPosX());
    setPosY(m_mathematicalproduct->getPosY());
    setPower(m_mathematicalproduct->getPower());
    setEField(m_mathematicalproduct->getEField());
    setEnable(m_mathematicalproduct->getEnable());

    return widget;
}

QWidget* DialogReceiverProduct::RealPathLossDialog(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;

    customplot->xAxis->setLabel("Distance[m]");
    customplot->yAxis->setLabel("Prx[dbm]");
    customplot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Real line of sight path-loss", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::ModelPathLossDialog(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;

    customplot->xAxis->setLabel("Distance[m]");
    customplot->yAxis->setLabel("Prx[dbm]");
    customplot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Model line of sight path-loss", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::CellRange(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;

    customplot->xAxis->setLabel("Connection probability");
    customplot->yAxis->setLabel("Cell range[m]");
    customplot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Connection probabibility between cellule range", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::PhysicalImpulseResponse(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    setRayLength(m_mathematicalproduct->rayLength());
    setAttenuation(m_mathematicalproduct->attenuation());
    setFrequency(m_mathematicalproduct->frequency());
    setBandwidth(m_mathematicalproduct->bandwidth());
    // Number of rays = Number of powers received:
    unsigned long rayNumber = m_raylength.size();
    // Speed of light
    double  c =2.998e+8; // m/s
    // Creation of two vectors (impusle) and time of each impulse
    std::vector <double> h(rayNumber), tau(rayNumber);
    // Creation of TDL delay
    double deltaTau = 1.0/(2.0*double(m_transmitterbandwidth));
    std::vector<double> x(rayNumber);
    std::vector <std::complex <double>> y(rayNumber);
    complex <double> k(0.0, 1.0);

    // loop over all rays
    double tau_check;
    for (unsigned long i=0; i<(rayNumber); ++i){
        // Compute attenuation factor
        h[i] = 10*log10(abs(m_attenuation.at(i))); // alpha
        // Compute time of arrival in ns
        tau[i] = m_raylength.at(i)/c*1e9; // tau

        tau_check = m_raylength.at(i)/c;
        int l = 0;
        while(!(l*deltaTau-deltaTau/2<=tau_check && tau_check<l*deltaTau+deltaTau/2)){
            l++;
        }
        x[i] = l*deltaTau*1e9;
        y[i] = m_attenuation.at(i) * exp(-k * 2.0*M_PI * std::complex<double>(m_transmitterbandwidth * tau_check));

        QCPItemLine *line = new QCPItemLine(customplot);
        line->start->setCoords(tau[i], h[i]);  // location of point 1 in plot coordinate
        line->end->setCoords(tau[i], -100);  // location of point 2 in plot coordinate
    }

    for (unsigned long i=0; i<rayNumber; ++i){
        for (unsigned long j=0; j<rayNumber; ++j){
            if(i<j && round(x.at(i)*1.0e3) == round(x.at(j)*1.0e3)){
                y[i] += y[j];
                y[j] = 0;
            }
        }
    }

    int counter = 0;
    for (unsigned long i=0; i<rayNumber; ++i){
        if(y[i]!=0.0){counter++;}
    }

    QVector<double> h_TDL(counter), tau_delay(counter);
    unsigned long p = 0;
    int counter2 = 0;
    while(p<rayNumber){
        if(y[p] != 0.0){
            tau_delay[counter2] = x[p];
            h_TDL[counter2] = 10*log10(abs(y[p]));
            QCPItemLine *line = new QCPItemLine(customplot);
            line->start->setCoords(tau_delay[counter2], h_TDL[counter2]);  // location of point 1 in plot coordinate
            line->end->setCoords(tau_delay[counter2], -100);  // location of point 2 in plot coordinate
            line->setPen(QPen(Qt::red));
            counter2++;
        }
        p++;
    }

    // Plot physiscal impulse response
    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::blue));
    customplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    QVector<double> vec_tau = QVector<double>(tau.begin(),tau.end());
    QVector<double> vec_h = QVector<double>(h.begin(),h.end());
    customplot->graph(0)->setData(vec_tau, vec_h);
    customplot->graph(0)->setName("Impulse");

    customplot->addGraph();
    customplot->graph(1)->setPen(QPen(Qt::red));
    customplot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customplot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customplot->graph(1)->setData(tau_delay, h_TDL);
    customplot->graph(1)->setName("TDL");

    customplot->xAxis->setLabel("\u03C4[ns]");
    customplot->yAxis->setLabel("h(\u03C4)[dB]");
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();
    customplot->legend->setVisible(true);
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Physical impulse response and TDL", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::TDLImpulseResponse(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    setRayLength(m_mathematicalproduct->rayLength());
    setAttenuation(m_mathematicalproduct->attenuation());
    setFrequency(m_mathematicalproduct->frequency());
    setBandwidth(m_mathematicalproduct->bandwidth());
    // Number of rays = Number of powers received:
    unsigned long rayNumber = m_raylength.size();
    // Speed of light
    double  c =2.998e+8; // m/s
    double deltaTau = 1.0/(2.0*double(m_transmitterbandwidth));
    std::vector<double> x(rayNumber);
    std::vector <std::complex <double>> y(rayNumber);
    complex <double> k(0.0, 1.0);

    double tau_check;
    for (unsigned long i=0; i<(rayNumber); ++i){
        tau_check = m_raylength.at(i)/c;
        int l = 0;
        while(!(l*deltaTau-deltaTau/2<=tau_check && tau_check<l*deltaTau+deltaTau/2)){
            l++;
        }
        x[i] = l*deltaTau*1e9;
        y[i] = m_attenuation.at(i) * exp(-k * 2.0*M_PI * std::complex<double>(m_transmitterbandwidth * tau_check));
    }

    for (unsigned long i=0; i<rayNumber; ++i){
        for (unsigned long j=0; j<rayNumber; ++j){
            if(i<j && round(x.at(i)*1.0e3) == round(x.at(j)*1.0e3)){
                y[i] += y[j];
                y[j] = 0;
            }
        }
    }

    int counter = 0;
    for (unsigned long i=0; i<rayNumber; ++i){
        if(y[i]!=0.0){counter++;}
    }

    QVector<double> h_TDL(counter), tau(counter);
    unsigned long p = 0;
    int counter2 = 0;
    while(p<rayNumber){
        if(y[p] != 0.0){
            tau[counter2] = x[p];
            h_TDL[counter2] = 10*log10(abs(y[p]));
            QCPItemLine *line = new QCPItemLine(customplot);
            line->start->setCoords(tau[counter2], h_TDL[counter2]);  // location of point 1 in plot coordinate
            line->end->setCoords(tau[counter2], -100);  // location of point 2 in plot coordinate
            line->setPen(QPen(Qt::red));
            counter2++;
        }
        p++;
    }
    // Plot physiscal impulse response
    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::red));
    customplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customplot->graph(0)->setData(tau, h_TDL);
    customplot->graph(0)->setName("TDL");

    customplot->xAxis->setLabel("\u03C4[ns]");
    customplot->yAxis->setLabel("h_TDL(\u03C4)[dB]");
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->legend->setVisible(true);
    customplot->replot();

    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "TDL impulse response", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::DopplerSpectrum(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;

    customplot->xAxis->setLabel("\u03C9[rad/s]");
    customplot->yAxis->setLabel("Prx[dBm]");
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();

    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Dopler spectrum", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

void DialogReceiverProduct::setEnable(bool enable){
    this->enable = enable;
    m_posx->setEnabled(this->enable);
    m_posy->setEnabled(this->enable);
}

void DialogReceiverProduct::newProperties(){
    m_mathematicalproduct->setPosX(getPosX());
    m_mathematicalproduct->setPosY(getPosY());
    m_mathematicalproduct->newProperties();
    close();
}

void DialogReceiverProduct::saveProperties(){
    newProperties();
}
