#include "dialogreceiverproduct.h"

DialogReceiverProduct::DialogReceiverProduct(ReceiverProduct *mathematicalproduct):
    m_mathematicalproduct(mathematicalproduct)
{
    setWindowTitle("Receiver properties: ");
    setWindowIcon(QIcon(GraphicsReceiverProduct::getImage()));
    setMinimumSize(1000,500);

    m_tabwidget = new QTabWidget;
    m_tabwidget->addTab(GeneralTabDialog(), tr("General"));
    m_tabwidget->addTab(PhysicalImpulseResponse(),tr("Impulse Response"));
    m_tabwidget->addTab(TDLImpulseResponse(),tr("TDL"));
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
    setPathLoss(m_mathematicalproduct->pathLoss());
    QVector<double> D(m_pathloss.size()), logD(m_pathloss.size()), Prx(m_pathloss.size()), pl(m_pathloss.size()), fading(m_pathloss.size());
    int i = 0;
    for(const auto &path : m_pathloss){
        D[i] = path.first;
        logD[i] = log10(D[i]);
        Prx[i] = path.second;
        i++;
    }

    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::blue));
    customplot->graph(0)->setData(D, Prx);

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
    QCustomPlot *impulse_plot = new QCustomPlot;
    setImpulseRayLength(m_mathematicalproduct->impulseRayLength());
    setImpulseAttenuation(m_mathematicalproduct->impulseAttenuation());
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
    int i = 0;
    map<vector<double>,double>::iterator it;
    it = m_attenuation.begin();
    for(const auto &imp : m_raylength){
        // Compute attenuation factor
        h[i] = 10*log10(abs(it->second));
        // Compute time of arrival in ns
        tau[i] = imp.second/c*1e9; // tau
        tau_check = imp.second/c;

        int l = 0;
        while(!(l*deltaTau-deltaTau/2<=tau_check && tau_check<l*deltaTau+deltaTau/2)){
            l++;
        }
        x[i] = l*deltaTau*1e9;
        y[i] = it->second * exp(-k * 2.0*M_PI * std::complex<double>(m_transmitterbandwidth * tau_check));

        QCPItemLine *line = new QCPItemLine(impulse_plot);
        line->start->setCoords(tau[i], h[i]);  // location of point 1 in plot coordinate
        line->end->setCoords(tau[i], -100);  // location of point 2 in plot coordinate
        i++;
        it++;
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

    h_TDL.resize(counter);
    tau_delay.resize(counter);
    unsigned long p = 0;
    int counter2 = 0;
    while(p<rayNumber){
        if(y[p] != 0.0){
            tau_delay[counter2] = x[p];
            h_TDL[counter2] = 10*log10(abs(y[p]));
            QCPItemLine *line = new QCPItemLine(impulse_plot);
            line->start->setCoords(tau_delay[counter2], h_TDL[counter2]);  // location of point 1 in plot coordinate
            line->end->setCoords(tau_delay[counter2], -100);  // location of point 2 in plot coordinate
            line->setPen(QPen(Qt::red));
            counter2++;
        }
        p++;
    }

    // Plot physiscal impulse response
    impulse_plot->addGraph();
    impulse_plot->graph(0)->setPen(QPen(Qt::blue));
    impulse_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    impulse_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    QVector<double> vec_tau = QVector<double>(tau.begin(),tau.end());
    QVector<double> vec_h = QVector<double>(h.begin(),h.end());
    impulse_plot->graph(0)->setData(vec_tau, vec_h);
    impulse_plot->graph(0)->setName("Impulse");

    impulse_plot->addGraph();
    impulse_plot->graph(1)->setPen(QPen(Qt::red));
    impulse_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    impulse_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    impulse_plot->graph(1)->setData(tau_delay, h_TDL);
    impulse_plot->graph(1)->setName("TDL");

    impulse_plot->xAxis->setLabel("\u03C4[ns]");
    impulse_plot->yAxis->setLabel("h(\u03C4)[dB]");
    impulse_plot->yAxis->grid()->setSubGridVisible(true);
    impulse_plot->xAxis->grid()->setSubGridVisible(true);
    impulse_plot->rescaleAxes();
    impulse_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    impulse_plot->replot();
    impulse_plot->legend->setVisible(true);
    impulse_plot->plotLayout()->insertRow(0);
    impulse_plot->plotLayout()->addElement(0, 0, new QCPTextElement(impulse_plot, "Physical impulse response and TDL", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(impulse_plot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::TDLImpulseResponse(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    for(int i = 0; i<h_TDL.size(); i++){
        QCPItemLine *line = new QCPItemLine(customplot);
        line->start->setCoords(tau_delay[i], h_TDL[i]);  // location of point 1 in plot coordinate
        line->end->setCoords(tau_delay[i], -100);  // location of point 2 in plot coordinate
    }
    // Plot physiscal impulse response
    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::red));
    customplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customplot->graph(0)->setData(tau_delay, h_TDL);
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
