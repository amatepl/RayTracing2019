#include "dialogreceiverproduct.h"

DialogReceiverProduct::DialogReceiverProduct(ReceiverProduct *mathematicalproduct):
    m_mathematicalproduct(mathematicalproduct)
{
    setWindowTitle("Receiver properties: ");
    setWindowIcon(QIcon(GraphicsReceiverProduct::getImage()));
    setMinimumSize(1000,900);
    show_tdl = true;

    m_tabwidget = new QTabWidget;
    m_tabwidget->addTab(GeneralTabDialog(),         tr("General"));
    m_tabwidget->addTab(PhysicalImpulseResponse(),  tr("Impulse Response"));
    m_tabwidget->addTab(TDLImpulseResponse(),       tr("TDL"));
    m_tabwidget->addTab(ModelPathLossDialog(),      tr("Model Path-Loss"));
    m_tabwidget->addTab(RealPathLossDialog(),       tr("Real Path-Loss"));
    m_tabwidget->addTab(CellRange(),                tr("Cellule range"));
    m_tabwidget->addTab(DopplerSpectrum(),          tr("Doppler Spectrum"));
    m_tabwidget->addTab(InterferencePattern(),      tr("Interference Pattern"));
    m_tabwidget->addTab(DistributionInterference(), tr("Interference Distribution"));
    m_tabwidget->addTab(PrxAngularSpctr(),          tr("Power Angular Spectrum"));
    m_tabwidget->addTab(AngularDistr(),             tr("Angular Distrubution"));

    m_buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok
                                       | QDialogButtonBox::Cancel
                                       | QDialogButtonBox::Save);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addWidget(m_tabwidget);
    mainlayout->addWidget(m_buttonbox);
    setLayout(mainlayout);

    setAttribute(Qt::WA_DeleteOnClose,true);
    connect(m_buttonbox, &QDialogButtonBox::rejected, this, &DialogReceiverProduct::close);
    connect(m_buttonbox, &QDialogButtonBox::accepted, this, &DialogReceiverProduct::saveProperties);
//    connect(m_buttonbox, &QDialogButtonBox::accepted, this, &DialogReceiverProduct::saveToDisk);
    connect(m_buttonbox, &QDialogButtonBox::clicked, this, &DialogReceiverProduct::buttonBoxClicked);

    open();
}


//void DialogReceiverProduct::handleButtonClick(self, button)
//{
//    sb = self.buttonBox.standardButton(button)
//    if sb == QtGui.QDialogButtonBox.Apply:
//    print('Apply Clicked')
//        elif sb == QtGui.QDialogButtonBox.Reset:
//    print('Reset Clicked')
//}


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

    QGridLayout *orientation = new QGridLayout(this);
    QLabel *myimage = new QLabel();
    QPixmap pix(":/Images/anti-clockwize.png");
    QPixmap newpix = pix.scaled(12,12);
    myimage->setPixmap(newpix);
    orientation->addWidget(myimage,0,1);
    orientation->addWidget(m_orientation,0,0);
    orientation->setColumnStretch(0,20);

    geoProperties->addRow("Orientation [°]: ", orientation);
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
    friis_loss = m_mathematicalproduct->friisLoss();
    double n = m_mathematicalproduct->pathLossExponent();
    fading_variability = m_mathematicalproduct->fadingVariability();

    QCPGraph *path_loss_graph = new QCPGraph(customplot->xAxis, customplot->yAxis);

    path_loss_graph->setPen(QColor(Qt::blue));
    path_loss_graph->setName("Power received");
    path_loss_graph->setLineStyle(QCPGraph::lsLine);
    path_loss_graph->setData(D, Prx);

    customplot->addGraph();
    customplot->graph(1)->setPen(QPen(Qt::red));
    customplot->graph(1)->setData(D, path_loss);
    customplot->graph(1)->setName("Path Loss");

    customplot->addGraph();
    customplot->graph(2)->setPen(QPen(Qt::darkGreen));
    customplot->graph(2)->setData(D, friis_loss);
    customplot->graph(2)->setName("Free propagation loss");

    customplot->xAxis->setLabel("Distance[m]");
    customplot->yAxis->setLabel("Prx[dbm]");
    customplot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Simulation path loss", QFont("sans", 12, QFont::Bold)));
    customplot->legend->setVisible(true);

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(customplot);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText(QString("Path Loss Exponent = ") + QString::number(abs(n)) + QString("\n") + QString("Fading variability[dB] = ") + QString::number(fading_variability));
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

    doppler = m_mathematicalproduct->getDoppler();
    omega = m_mathematicalproduct->getOmega();

    for(int i = 0; i < doppler.size(); i++){
        QCPItemLine *line_doppler = new QCPItemLine(customplot);
        line_doppler->start->setCoords(omega[i], doppler[i]);  // location of point 1 in plot coordinate
        line_doppler->end->setCoords(omega[i], -130);  // location of point 2 in plot coordinate
        line_doppler->setPen(QPen(Qt::blue));
    }

    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::red));
    customplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customplot->graph(0)->setData(omega, doppler);
    customplot->graph(0)->setName("Doppler spectrum");

    customplot->xAxis->setLabel("\u03C9[rad/s]");
    customplot->yAxis->setLabel("a(\u03c9)[dB]");
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

QWidget* DialogReceiverProduct::InterferencePattern()
{
    Q3DSurface *graph = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return container;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *graph_layout = new QVBoxLayout();
    QLabel *label = new QLabel("Experimental Interference Pattern In A Local Area");
    QFont font;
    font.setPointSize(30);
    label->setFont(font);
    label->setAlignment(Qt::AlignHCenter);
    graph_layout->addWidget(label);
    graph_layout->addWidget(container);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addLayout(graph_layout);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

    QRadioButton *modeNoneRB = new QRadioButton(widget);
    modeNoneRB->setText(QStringLiteral("No selection"));
    modeNoneRB->setChecked(false);

    QRadioButton *modeItemRB = new QRadioButton(widget);
    modeItemRB->setText(QStringLiteral("Item"));
    modeItemRB->setChecked(false);

    QRadioButton *modeSliceRowRB = new QRadioButton(widget);
    modeSliceRowRB->setText(QStringLiteral("Row Slice"));
    modeSliceRowRB->setChecked(false);

    QRadioButton *modeSliceColumnRB = new QRadioButton(widget);
    modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
    modeSliceColumnRB->setChecked(false);

    QVBoxLayout *selectionVBox = new QVBoxLayout;
    selectionVBox->addWidget(modeNoneRB);
    selectionVBox->addWidget(modeItemRB);
    selectionVBox->addWidget(modeSliceRowRB);
    selectionVBox->addWidget(modeSliceColumnRB);
    selectionGroupBox->setLayout(selectionVBox);

    QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, widget);
    axisMinSliderX->setMinimum(0);
    axisMinSliderX->setTickInterval(1);
    axisMinSliderX->setEnabled(true);
    QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderX->setMinimum(1);
    axisMaxSliderX->setTickInterval(1);
    axisMaxSliderX->setEnabled(true);
    QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMinSliderZ->setMinimum(0);
    axisMinSliderZ->setTickInterval(1);
    axisMinSliderZ->setEnabled(true);
    QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderZ->setMinimum(1);
    axisMaxSliderZ->setTickInterval(1);
    axisMaxSliderZ->setEnabled(true);

    QPushButton *send_data = new QPushButton("Draw Interference",widget);
    connect(send_data,&QPushButton::clicked,this,&DialogReceiverProduct::interferenceActivated);

    vLayout->addWidget(send_data);
    vLayout->addWidget(selectionGroupBox);
    vLayout->addWidget(new QLabel(QStringLiteral("Column range")));
    vLayout->addWidget(axisMinSliderX);
    vLayout->addWidget(axisMaxSliderX);
    vLayout->addWidget(new QLabel(QStringLiteral("Row range")));
    vLayout->addWidget(axisMinSliderZ);
    vLayout->addWidget(axisMaxSliderZ);

    m_interferencepattern = new InterfererencePattern(graph);

    QObject::connect(modeNoneRB, &QRadioButton::toggled,
                     m_interferencepattern, &InterfererencePattern::toggleModeNone);
    QObject::connect(modeItemRB,  &QRadioButton::toggled,
                     m_interferencepattern, &InterfererencePattern::toggleModeItem);
    QObject::connect(modeSliceRowRB,  &QRadioButton::toggled,
                     m_interferencepattern, &InterfererencePattern::toggleModeSliceRow);
    QObject::connect(modeSliceColumnRB,  &QRadioButton::toggled,
                     m_interferencepattern, &InterfererencePattern::toggleModeSliceColumn);
    QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                     m_interferencepattern, &InterfererencePattern::adjustXMin);
    QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                     m_interferencepattern, &InterfererencePattern::adjustXMax);
    QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                     m_interferencepattern, &InterfererencePattern::adjustZMin);
    QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                     m_interferencepattern, &InterfererencePattern::adjustZMax);

    m_interferencepattern->setAxisMinSliderX(axisMinSliderX);
    m_interferencepattern->setAxisMaxSliderX(axisMaxSliderX);
    m_interferencepattern->setAxisMinSliderZ(axisMinSliderZ);
    m_interferencepattern->setAxisMaxSliderZ(axisMaxSliderZ);

    return widget;
}

QWidget*
DialogReceiverProduct::DistributionInterference()
{
    QWidget *widget = new QWidget;
    m_distribution = new QCustomPlot;

    m_distribution->xAxis->setLabel("|h|");
    m_distribution->yAxis->setLabel("PDF");
    m_distribution->xAxis->setRange(0, 1);
    m_distribution->yAxis->setRange(0, 0.03);
    m_distribution->yAxis->grid()->setSubGridVisible(true);
    m_distribution->xAxis->grid()->setSubGridVisible(true);
    m_distribution->rescaleAxes();
    m_distribution->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    m_distribution->legend->setVisible(true);

    m_distribution->plotLayout()->insertRow(0);
    m_distribution->plotLayout()->addElement(0, 0, new QCPTextElement(m_distribution, "Histogram of |h| and Rice distribution fitting", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(m_distribution,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget*
DialogReceiverProduct::PrxAngularSpctr()
{
    QWidget *widget = new QWidget;
    angular_distr_plot = new QCustomPlot;
//    angular_distr_plot = new QCustomPlot;

    pas = m_mathematicalproduct->prxAngularSpread();
    angular_distr = m_mathematicalproduct->angularDistr();
    u = m_mathematicalproduct->getu();

    for (int i = 0; i < pas.size(); i++) {
        QCPItemLine *line_impulse = new QCPItemLine(angular_distr_plot);
        line_impulse->start->setCoords(u[i], pas[i]);  // location of point 1 in plot coordinate
//        cout << "u " << u[i] <<", S(u): " << pas[i] << endl;
        line_impulse->end->setCoords(u[i], -600);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }
//    for (int i = 0; i<angular_distr.size(); i++) {
//        QCPItemLine *line_tdl = new QCPItemLine(angular_distr_plot);
//        impulse_tdl.push_back(line_tdl);
//        line_tdl->start->setCoords(u[i], angular_distr[i]);  // location of point 1 in plot coordinate
//        line_tdl->end->setCoords(u[i], -600);  // location of point 2 in plot coordinate
//        line_tdl->setPen(QPen(Qt::red));
//    }

//    for (const auto &i : u) {
//        cout << "Are you negative in dialog? " << i <<endl;
//    }

    // Plot physiscal impulse response
    angular_distr_plot->addGraph();
    angular_distr_plot->graph(0)->setPen(QPen(Qt::blue));
    angular_distr_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    angular_distr_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    angular_distr_plot->graph(0)->setData(u, pas);
    angular_distr_plot->graph(0)->setName("PAS");

//    angular_distr_plot->addGraph();
//    angular_distr_plot->graph(1)->setPen(QPen(Qt::red));
//    angular_distr_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
//    angular_distr_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
//    angular_distr_plot->graph(1)->setData(u, angular_distr);
//    angular_distr_plot->graph(1)->setName("Angular Distribution");

    angular_distr_plot->xAxis->setLabel("u[rad/m]");
    angular_distr_plot->yAxis->setLabel("S(u)[dB]");
    angular_distr_plot->yAxis->grid()->setSubGridVisible(true);
    angular_distr_plot->xAxis->grid()->setSubGridVisible(true);
    angular_distr_plot->rescaleAxes();
    angular_distr_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    angular_distr_plot->replot();
    angular_distr_plot->legend->setVisible(true);
    angular_distr_plot->plotLayout()->insertRow(0);
    angular_distr_plot->plotLayout()->addElement(0, 0, new QCPTextElement(angular_distr_plot, "Power Angular Density (PAS) and Angular Distribution", QFont("sans", 12, QFont::Bold)));
    QPushButton *show_tdl = new QPushButton("Show/Hide TDL");

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(angular_distr_plot,0,0);
    firstLayout->addWidget(show_tdl,1,0);

    widget->setLayout(firstLayout);

    connect(show_tdl,&QPushButton::clicked,this,&DialogReceiverProduct::showTDL);
    return widget;
}

QWidget*
DialogReceiverProduct::AngularDistr()
{
    QWidget *widget = new QWidget;
    m_distribution = new QCustomPlot;

    m_distribution->xAxis->setLabel("|h|");
    m_distribution->yAxis->setLabel("PDF");
    m_distribution->xAxis->setRange(0, 1);
    m_distribution->yAxis->setRange(0, 0.03);
    m_distribution->yAxis->grid()->setSubGridVisible(true);
    m_distribution->xAxis->grid()->setSubGridVisible(true);
    m_distribution->rescaleAxes();
    m_distribution->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    m_distribution->legend->setVisible(true);

    m_distribution->plotLayout()->insertRow(0);
    m_distribution->plotLayout()->addElement(0, 0, new QCPTextElement(m_distribution, "Histogram of |h| and Rice distribution fitting", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(m_distribution,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

void DialogReceiverProduct::changeGraph(){
}

void
DialogReceiverProduct::setInterferencePattern(vector<double> impulse_r, double min, double max)
{
    m_interferencepattern->enableImpulseInterference(impulse_r, min, max);
}

void
DialogReceiverProduct::setDistributionInterference(map<double,double> impulse,QVector<double> rice_distribution)
{
    QVector<double> impulse_value;
    QVector<double> probability;
    for(auto const &imp: impulse)
    {
        impulse_value.push_back(imp.first);
        probability.push_back(imp.second);
    }
    // create empty bar chart objects:
    QCPBars *distribution = new QCPBars(m_distribution->xAxis, m_distribution->yAxis);
    QCPGraph *rice = new QCPGraph(m_distribution->xAxis, m_distribution->yAxis);
    distribution->setWidth(0.01);
    // set names and colors:
    distribution->setName("|h| histogram");
    distribution->setPen(QPen(QColor(0, 0, 0)));
    distribution->setBrush(QBrush(QColor(255,0,0)));

    rice->setPen(QColor(Qt::black));
    rice->setName("Rice Distribution");
    rice->setLineStyle(QCPGraph::lsLine);
    rice->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    rice->setData(probability, impulse_value);

    // Add data:
    distribution->setData(impulse_value, probability);
    rice->setData(impulse_value,rice_distribution);
    m_distribution->replot();
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


void DialogReceiverProduct::buttonBoxClicked(QAbstractButton *button)
{
    if (button->text() == "OK") {

        saveProperties();

    } else if (button->text() == "Save") {

        saveToDisk();

    }
}


void DialogReceiverProduct::saveProperties(){
    newProperties();
}

void DialogReceiverProduct::saveToDisk()
{

    QString fichier = QFileDialog::getSaveFileName(this, "Save file", QString(), "Table (*.csv)");
    emit save(fichier.toStdString());

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
