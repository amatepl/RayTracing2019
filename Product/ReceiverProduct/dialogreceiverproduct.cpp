#include "dialogreceiverproduct.h"

DialogReceiverProduct::DialogReceiverProduct(ReceiverProduct *mathematicalproduct):
    m_mathematicalproduct(mathematicalproduct)
{
    setWindowTitle("Receiver properties: ");
    setWindowIcon(QIcon(GraphicsReceiverProduct::getImage()));
    setMinimumSize(1000,500);
    show_tdl = true;

    m_tabwidget = new QTabWidget;
    m_tabwidget->addTab(GeneralTabDialog(), tr("General"));
    m_tabwidget->addTab(PhysicalImpulseResponse(),tr("Impulse Response"));
    m_tabwidget->addTab(TDLImpulseResponse(),tr("TDL"));
    m_tabwidget->addTab(ModelPathLossDialog(), tr("Model Path-Loss"));
    m_tabwidget->addTab(RealPathLossDialog(), tr("Real Path-Loss"));
    m_tabwidget->addTab(CellRange(),tr("Cellule range"));
    m_tabwidget->addTab(DopplerSpectrum(), tr("Doppler Spectrum"));
    std::cout << "h_tdl: " << h_tdl.size() << endl;
    std::cout << "h: " << h.size() << endl;
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
    m_orientation = new QDoubleSpinBox(this);
    m_orientation->setRange(0,360.0);
    m_orientation->setAccelerated(true);
    m_speed = new QDoubleSpinBox(this);
    m_speed->setRange(0,90.0);
    m_speed->setAccelerated(true);


    m_target_snr = new QSpinBox(this);
    m_noise_figure = new QSpinBox(this);
    m_interferencemargin = new QSpinBox(this);
    m_target_snr->setRange(0,20);
    m_noise_figure->setRange(0,20);
    m_interferencemargin->setRange(0,20);
    m_power = new QLineEdit("Received power [dB]: ", this);
    m_power->setEnabled(false);
    m_e_field = new QLineEdit("Electric fiedl [V/m]: ", this);
    m_e_field->setEnabled(false);

    QFormLayout *geoProperties = new QFormLayout(this);
    geoProperties->addRow("X center: ",m_posx);
    geoProperties->addRow("Y center: ",m_posy);
    geoProperties->addRow("Orientation [°]: ", m_orientation);
    geoProperties->addRow("Speed [km/h]: ", m_speed);

    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QFormLayout *phyProperties = new QFormLayout(this);
    phyProperties->addRow("Target SNR [dB]: ", m_target_snr);
    phyProperties->addRow("Noise Figure [dB]: ", m_noise_figure);
    phyProperties->addRow("Interference Margin [dB]: ", m_interferencemargin);
    phyProperties->addRow(m_power);
    phyProperties->addRow(m_e_field);

    QGroupBox *phy = new QGroupBox("Physical properties");
    phy->setLayout(phyProperties);

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(geo,0,0);
    firstLayout->addWidget(phy,1,0);

    widget->setLayout(firstLayout);

    setOrientation(m_mathematicalproduct->getOrientation());
    setSpeed(m_mathematicalproduct->getSpeed());
    setPosX(m_mathematicalproduct->getPosX());
    setPosY(m_mathematicalproduct->getPosY());
    setPower(m_mathematicalproduct->getPower());
    setEField(m_mathematicalproduct->getEField());
    setEnable(m_mathematicalproduct->getEnable());
    setTargetSNR(m_mathematicalproduct->targetSNR());
    setNoiseFigure(m_mathematicalproduct->noiseFigure());
    setInterferecenceMargin(m_mathematicalproduct->interFerenceMargin());

    return widget;
}

QWidget* DialogReceiverProduct::RealPathLossDialog(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    D = m_mathematicalproduct->distancePathLoss();
    Prx = m_mathematicalproduct->powerPathLoss();
    path_loss = m_mathematicalproduct->linearPathLoss();
    double n = m_mathematicalproduct->pathLossExponent();
    fading_variability = m_mathematicalproduct->fadingVariability();

    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::blue));
    customplot->graph(0)->setData(D, Prx);
    customplot->graph(0)->setName("Power Received");


    customplot->addGraph();
    customplot->graph(1)->setPen(QPen(Qt::red));
    customplot->graph(1)->setData(D, path_loss);
    customplot->graph(1)->setName("Path Loss");

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
    customplot->legend->setVisible(true);

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(customplot);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText(QString("Path Loss Exponent = ") + QString::number(abs(n)) + QString("\n") + QString("Std Deviation[dB] = ") + QString::number(fading_variability));
    textLabel->setFont(QFont(font().family(), 10)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::ModelPathLossDialog(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    D_model = m_mathematicalproduct->distancePathLossModel();
    Prx_model = m_mathematicalproduct->powerPathLossModel();
    path_loss_model = m_mathematicalproduct->linearPathLossModel();
    double n = m_mathematicalproduct->pathLossExponent();
    fading_variability = m_mathematicalproduct->fadingVariability();
    min_prx = m_mathematicalproduct->minPower();
    QVector<double> threshold(Prx_model.size());
    for (int i =0; i< Prx_model.size(); i++){
        threshold[i] = min_prx;
    }
    // create graph and assign data to it:
    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::blue));
    customplot->graph(0)->setData(D_model, Prx_model);
    customplot->graph(0)->setName("Theoretical Power Received");

    customplot->addGraph();
    customplot->graph(1)->setPen(QPen(Qt::red));
    customplot->graph(1)->setData(D_model, path_loss_model);
    customplot->graph(1)->setName("Path Loss");

    customplot->addGraph();
    customplot->graph(2)->setPen(QPen(Qt::green));
    customplot->graph(2)->setData(D_model, threshold);
    customplot->graph(2)->setName("Minimal Power Accepted");

    // give the axes some labels:
    customplot->xAxis->setLabel("Distance[m]");
    customplot->yAxis->setLabel("Prx[dbm]");
    customplot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    customplot->xAxis->setTicker(logTicker);
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Model line of sight path-loss", QFont("sans", 12, QFont::Bold)));
    customplot->legend->setVisible(true);

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(customplot);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText(QString("Path Loss Exponent = ") + QString::number(abs(n)) + QString("\n") + QString("Std Deviation[dB] = ") + QString::number(fading_variability));
    textLabel->setFont(QFont(font().family(), 10)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::CellRange(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    probability = m_mathematicalproduct->probabilityConnection();
    cell_range = m_mathematicalproduct->cellRangeConnection();

    // Plot Range vs Probability
    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::blue));
    customplot->graph(0)->setData(probability, cell_range);

    // give the axes some labels:
    customplot->xAxis->setLabel("Connection probability");
    customplot->yAxis->setLabel("Cell range[m]");
    customplot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Cell Range For Probability Connection", QFont("sans", 12, QFont::Bold)));
    customplot->replot();

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(customplot);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText(QString("For a minimal received power of ") + QString::number(min_prx) + QString("dBm"));
    textLabel->setFont(QFont(font().family(), 10)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::PhysicalImpulseResponse(){
    QWidget *widget = new QWidget;
    impulse_plot = new QCustomPlot;
    h = m_mathematicalproduct->impulse();
    h_tdl = m_mathematicalproduct->impulseTDL();
    tau = m_mathematicalproduct->impulseTau();
    tau_tdl = m_mathematicalproduct->impulseTauTDL();
    for(int i = 0; i < h.size(); i++){
        QCPItemLine *line_impulse = new QCPItemLine(impulse_plot);
        line_impulse->start->setCoords(tau[i], h[i]);  // location of point 1 in plot coordinate
        line_impulse->end->setCoords(tau[i], -130);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }
    for (int i=0; i<h_tdl.size();i++){
        QCPItemLine *line_tdl = new QCPItemLine(impulse_plot);
        impulse_tdl.push_back(line_tdl);
        line_tdl->start->setCoords(tau_tdl[i], h_tdl[i]);  // location of point 1 in plot coordinate
        line_tdl->end->setCoords(tau_tdl[i], -130);  // location of point 2 in plot coordinate
        line_tdl->setPen(QPen(Qt::red));
    }

    // Plot physiscal impulse response
    impulse_plot->addGraph();
    impulse_plot->graph(0)->setPen(QPen(Qt::blue));
    impulse_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    impulse_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    impulse_plot->graph(0)->setData(tau, h);
    impulse_plot->graph(0)->setName("Impulse");

    impulse_plot->addGraph();
    impulse_plot->graph(1)->setPen(QPen(Qt::red));
    impulse_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    impulse_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    impulse_plot->graph(1)->setData(tau_tdl, h_tdl);
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
    impulse_plot->plotLayout()->addElement(0, 0, new QCPTextElement(impulse_plot, "Physical impulse response (and TDL model under US assumption)", QFont("sans", 12, QFont::Bold)));
    QPushButton *show_tdl = new QPushButton("Show/Hide TDL");

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(impulse_plot,0,0);
    firstLayout->addWidget(show_tdl,1,0);

    widget->setLayout(firstLayout);

    connect(show_tdl,&QPushButton::clicked,this,&DialogReceiverProduct::showTDL);
    return widget;
}

QWidget* DialogReceiverProduct::TDLImpulseResponse(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    for(int i = 0; i<h_tdl.size(); i++){
        QCPItemLine *line = new QCPItemLine(customplot);
        line->start->setCoords(tau_tdl[i], h_tdl[i]);  // location of point 1 in plot coordinate
        line->end->setCoords(tau_tdl[i], -130);  // location of point 2 in plot coordinate
        line->setPen(QPen(Qt::red));
    }
    // Plot physiscal impulse response
    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::red));
    customplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customplot->graph(0)->setData(tau_tdl, h_tdl);
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
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "TDL model under US assumption", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::DopplerSpectrum(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;

    doppler_shift = m_mathematicalproduct->dopplerShift();

    for(int i = 0; i < h.size(); i++){
        QCPItemLine *line_doppler = new QCPItemLine(customplot);
        line_doppler->start->setCoords(doppler_shift[i], h[i]);  // location of point 1 in plot coordinate
        line_doppler->end->setCoords(doppler_shift[i], -130);  // location of point 2 in plot coordinate
        line_doppler->setPen(QPen(Qt::blue));
    }

    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::red));
    customplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customplot->graph(0)->setData(doppler_shift, h);
    customplot->graph(0)->setName("Doppler spectrum");

    customplot->xAxis->setLabel("\u03C9[rad/s]");
    customplot->yAxis->setLabel("h[dB]");
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

void DialogReceiverProduct::changeGraph(){
}

void DialogReceiverProduct::setEnable(bool enable){
    this->enable = enable;
    m_posx->setEnabled(this->enable);
    m_posy->setEnabled(this->enable);
}

void DialogReceiverProduct::newProperties(){
    m_mathematicalproduct->setSpeed(getSpeed());
    m_mathematicalproduct->setOrientation(getOrientation());
    m_mathematicalproduct->setPosX(getPosX());
    m_mathematicalproduct->setPosY(getPosY());
    m_mathematicalproduct->setTargetSNR(targetSNR());
    m_mathematicalproduct->setNoiseFigure(noiseFigure());
    m_mathematicalproduct->setInterferecenceMargin(interFerenceMargin());
    m_mathematicalproduct->newProperties();
    close();
}

void DialogReceiverProduct::saveProperties(){
    newProperties();
}

void DialogReceiverProduct::showTDL(){
    show_tdl = !show_tdl;
    if (show_tdl){
        for (int i=0; i<h_tdl.size();i++){
            QCPItemLine *line_tdl = new QCPItemLine(impulse_plot);
            impulse_tdl.push_back(line_tdl);
            line_tdl->start->setCoords(tau_tdl[i], h_tdl[i]);  // location of point 1 in plot coordinate
            line_tdl->end->setCoords(tau_tdl[i], -130);  // location of point 2 in plot coordinate
            line_tdl->setPen(QPen(Qt::red));
        }
        impulse_plot->addGraph();
        impulse_plot->graph(1)->setPen(QPen(Qt::red));
        impulse_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
        impulse_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
        impulse_plot->graph(1)->setData(tau_tdl, h_tdl);
        impulse_plot->graph(1)->setName("TDL");
        impulse_plot->replot();
    }
    else{
        for(int i = 0; i<impulse_tdl.count(); i++)
        {
             impulse_plot->removeItem(impulse_tdl[i]); //returns true
        }
        impulse_plot->removeGraph(impulse_plot->graph(1));
        impulse_plot->replot();
    }
}
