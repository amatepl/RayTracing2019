#include "dialogrx.h"

DialogRx::DialogRx(ReceiverProduct *mathematicalproduct, QWidget *parent):QDialog(parent, Qt::WindowStaysOnTopHint | Qt::Tool),
    m_mathematicalproduct(mathematicalproduct)
{
//    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle("Receiver properties: ");
    setWindowIcon(QIcon(GraphicsRx::getImage()));
    setMinimumSize(1000,900);
    show_tdl = true;

    m_tabwidget = new QTabWidget;
    m_tabwidget->addTab(GeneralTabDialog(),         tr("General"));
    m_tabwidget->addTab(PhysicalImpulseResponse(),  tr("Impulse Response"));
//    m_tabwidget->addTab(TDLImpulseResponse(),       tr("TDL"));
    m_tabwidget->addTab(fqResp(),                   tr("Frequency Response"));
    m_tabwidget->addTab(InterferencePattern(),      tr("Interference Pattern"));
//    m_tabwidget->addTab(DistributionInterference(), tr("Interference Distribution"));
//    m_tabwidget->addTab(DopplerSpectrum(),          tr("Doppler Spectrum"));
    m_tabwidget->addTab(PrxAngularSpctr(), tr("Power Angular Spectrum"));
    m_tabwidget->addTab(PrxDopplerSpctr(),          tr("Power Doppler Spectrum"));
    m_tabwidget->addTab(SpcCrltn(), tr("Spacial Correlation"));
    m_tabwidget->addTab(timeCrltn(), tr("Time Correltaion"));
    m_tabwidget->addTab(PDP(), tr("Power Delay Profile"));

    m_buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok
                                       | QDialogButtonBox::Cancel
                                       | QDialogButtonBox::Save);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addWidget(m_tabwidget);
    mainlayout->addWidget(m_buttonbox);
    setLayout(mainlayout);

    setAttribute(Qt::WA_DeleteOnClose,true);
    connect(m_buttonbox, &QDialogButtonBox::rejected, this, &DialogRx::close);
    connect(m_buttonbox, &QDialogButtonBox::accepted, this, &DialogRx::saveProperties);
//    connect(m_buttonbox, &QDialogButtonBox::accepted, this, &DialogRx::saveToDisk);
    connect(m_buttonbox, &QDialogButtonBox::clicked, this, &DialogRx::buttonBoxClicked);
    connect(m_tabwidget, &QTabWidget::currentChanged, this, &DialogRx::tabOpened);
    update();

//    open();
    show();
}


//void DialogRx::handleButtonClick(self, button)
//{
//    sb = self.buttonBox.standardButton(button)
//    if sb == QtGui.QDialogButtonBox.Apply:
//    print('Apply Clicked')
//        elif sb == QtGui.QDialogButtonBox.Reset:
//    print('Reset Clicked')
//}


DialogRx::~DialogRx()
{
    m_mathematicalproduct->dialogDeleted();
}

QWidget* DialogRx::templatePlot(QCustomPlot *plot, QString title, QString xlabel,
                                QString ylabel, bool xlog, bool ylog)
{
    QWidget *widget = new QWidget();

    plot->xAxis->setLabel(xlabel);
    plot->yAxis->setLabel(ylabel);
    if (xlog) plot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    if (ylog) plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    plot->yAxis->grid()->setSubGridVisible(true);
    plot->xAxis->grid()->setSubGridVisible(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, title, QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(plot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}


QWidget* DialogRx::GeneralTabDialog(){
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

    QGroupBox *phy = new QGroupBox("Physical properties");
    phy->setLayout(phyProperties);

    /* Channel */

    QGroupBox *chBox = new QGroupBox("Channel");
    QGridLayout *chLayout = new QGridLayout(this);

    QLabel *eFieldLabel = new QLabel("Electric filed [V/m]: ",this);
    chLayout->addWidget(eFieldLabel, 0, 0);
    complex<double> eField = m_mathematicalproduct->getEField();
    if (eField.imag() <0){
        m_eField = new QLabel(QString::number(eField.real())
                              +QString::number(eField.imag())
                              +"i", this);
    }
    else {
        m_eField = new QLabel(QString::number(eField.real())
                              +"+"
                              +QString::number(eField.imag())
                              +"i", this);
    }
    chLayout->addWidget(m_eField, 0, 1);

    QLabel *voltageLabel = new QLabel("Induced voltage [V]: ",this);
    chLayout->addWidget(voltageLabel, 1, 0);
    complex<double> voltage = m_mathematicalproduct->getVoltage();
    if (voltage.imag() <0){
        m_indVoltage = new QLabel(QString::number(voltage.real())
                                  +QString::number(voltage.imag())
                                  +"i", this);
    }
    else {
        m_indVoltage = new QLabel(QString::number(voltage.real())
                                  +"+"
                                  +QString::number(voltage.imag())
                                  +"i", this);
    }
    chLayout->addWidget(m_indVoltage, 1, 1);

    QLabel *prxLabel = new QLabel("Received power [dBm]: ",this);
    chLayout->addWidget(prxLabel, 2, 0);
    m_prx = new QLabel(QString::number(m_mathematicalproduct->getPower()), this);
    chLayout->addWidget(m_prx, 2, 1);

    QLabel *dstLabel = new QLabel("Transmitter distance: ", this);
    chLayout->addWidget(dstLabel, 3, 0);

    m_dstnc = new QLabel(QString::number(m_mathematicalproduct->getDstnc()), this);
    chLayout->addWidget(m_dstnc, 3, 1);

    QLabel *dlySprdLabel = new QLabel("Delay Spread [ns]: ", this);
    chLayout->addWidget(dlySprdLabel, 4, 0);

    m_dlySprd = new QLabel(QString::number(m_mathematicalproduct->getDlySprd()) , this);
    chLayout->addWidget(m_dlySprd, 4, 1);

    QLabel *riceFctrLabel = new QLabel("Rice Factor [dB]: ", this);
    chLayout->addWidget(riceFctrLabel, 5, 0);

    m_riceFactor = new QLabel(QString::number(m_mathematicalproduct->getRiceFctr()), this);
    chLayout->addWidget(m_riceFactor, 5, 1);

    QLabel *coherenceBwLabel = new QLabel("Coherence Bandwidth [MHz]: ", this);
    chLayout->addWidget(coherenceBwLabel, 6, 0);

    m_coherenceBw = new QLabel(QString::number(m_mathematicalproduct->getCoherenceBw()), this);
    chLayout->addWidget(m_coherenceBw, 6, 1);

    QLabel *coherenceTmLabel = new QLabel("Coherence Time [\u03bcs]: ", this);
    chLayout->addWidget(coherenceTmLabel, 7, 0);

    m_coherenceTm = new QLabel(QString::number(m_mathematicalproduct->getCoherenceTm()), this);
    chLayout->addWidget(m_coherenceTm, 7, 1);

    QLabel *angSprdLabel = new QLabel("Angular Spread [rad]: ", this);
    chLayout->addWidget(angSprdLabel, 8, 0);

    m_angSpdr = new QLabel(QString::number(m_mathematicalproduct->getAngSprd()), this);
    chLayout->addWidget(m_angSpdr, 8, 1);

    QLabel *dopplerSprdLabel = new QLabel("Doppler Spread [rad/s]: ", this);
    chLayout->addWidget(dopplerSprdLabel, 9, 0);

    m_dopplerSpdr = new QLabel(QString::number(m_mathematicalproduct->getDopplerSprd()), this);
    chLayout->addWidget(m_dopplerSpdr, 9, 1);

    chBox->setLayout(chLayout);

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(geo,0,0);
    firstLayout->addWidget(phy,1,0);
    firstLayout->addWidget(chBox, 2, 0);

    widget->setLayout(firstLayout);

//    setOrientation(m_mathematicalproduct->getOrientation());
//    setSpeed(m_mathematicalproduct->getSpeed());
//    setPosX(m_mathematicalproduct->getPosX());
//    setPosY(m_mathematicalproduct->getPosY());
//    setPower(m_mathematicalproduct->getPower());
//    setEField(m_mathematicalproduct->getEField());
//    setEnable(m_mathematicalproduct->getEnable());
//    setTargetSNR(m_mathematicalproduct->targetSNR());
//    setNoiseFigure(m_mathematicalproduct->noiseFigure());
//    setInterferecenceMargin(m_mathematicalproduct->interFerenceMargin());

    updateGeneralTab();

    return widget;
}

void DialogRx::updateGeneralTab()
{
    m_orientation->setValue(m_mathematicalproduct->getOrientation());
    m_speed->setValue(m_mathematicalproduct->getSpeed());
    m_posx->setValue(m_mathematicalproduct->getPosX());
    m_posy->setValue(m_mathematicalproduct->getPosY());

//    setEnable(m_mathematicalproduct->getEnable());
    m_target_snr->setValue(m_mathematicalproduct->targetSNR());
    m_noise_figure->setValue(m_mathematicalproduct->noiseFigure());
    m_interferencemargin->setValue(m_mathematicalproduct->interFerenceMargin());
    updateChInfo();

}

void DialogRx::updateChInfo()
{
    complex<double> eField = m_mathematicalproduct->getEField();
    if (eField.imag() <0){
        m_eField->setText(QString::number(eField.real())
                          +QString::number(eField.imag())
                          +"i");
    }
    else {
        m_eField->setText(QString::number(eField.real())
                          +"+"
                          +QString::number(eField.imag())
                          +"i");
    }

    complex<double> voltage = m_mathematicalproduct->getVoltage();
    if (voltage.imag() <0){
        m_indVoltage->setText(QString::number(voltage.real())
                              +QString::number(voltage.imag())
                              +"i");
    }
    else {
        m_indVoltage->setText(QString::number(voltage.real())
                              +"+"
                              +QString::number(voltage.imag())
                              +"i");
    }

    m_prx->setText(QString::number(m_mathematicalproduct->getPower()));

    m_dstnc->setText(QString::number(m_mathematicalproduct->getDstnc()));

    m_dlySprd->setText(QString::number(m_mathematicalproduct->getDlySprd()));

    m_riceFactor->setText(QString::number(m_mathematicalproduct->getRiceFctr()));

    m_coherenceBw->setText(QString::number(m_mathematicalproduct->getCoherenceBw()));

    m_coherenceTm->setText(QString::number(m_mathematicalproduct->getCoherenceTm()));

    m_angSpdr->setText(QString::number(m_mathematicalproduct->getAngSprd()));

    m_dopplerSpdr->setText(QString::number(m_mathematicalproduct->getDopplerSprd()));
}

QWidget* DialogRx::PhysicalImpulseResponse(){
    QWidget *widget = new QWidget;
    impulse_plot = new QCustomPlot;


    // Plot physiscal impulse response
    impulse_plot->addGraph();
    impulse_plot->graph(0)->setPen(QPen(Qt::blue));
    impulse_plot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
    impulse_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    impulse_plot->graph(0)->setName("Impulse");

    impulse_plot->addGraph();
    impulse_plot->graph(1)->setPen(QPen(Qt::red));
    impulse_plot->graph(1)->setLineStyle(QCPGraph::lsImpulse);
    impulse_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    impulse_plot->graph(1)->setName("TDL");

    impulse_plot->xAxis->setLabel("\u03C4[ns]");
    impulse_plot->yAxis->setLabel("Normalized induced voltage V_OC");
    impulse_plot->yAxis->grid()->setSubGridVisible(true);
    impulse_plot->xAxis->grid()->setSubGridVisible(true);

    QString title1 = "Normalized induced voltage as impulse response with maximum voltage = " + QString::number(round(m_mathematicalproduct->maxVoltage()*1e6)/1e6);
    QString title2 = "and normalized TDL model under US assumption with maximum TDL voltage = " + QString::number(round(m_mathematicalproduct->maxVoltageTDL()*1e6)/1e6);
    title_impulse = new QCPTextElement(impulse_plot, title1 + QString("\n") + title2, QFont("sans", 12, QFont::Bold));

    updateImpulseResponse();

    impulse_plot->rescaleAxes();
    impulse_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
//    impulse_plot->replot();
    impulse_plot->legend->setVisible(true);
    impulse_plot->plotLayout()->insertRow(0);
    impulse_plot->plotLayout()->addElement(0, 0, title_impulse);
    QPushButton *show_tdl = new QPushButton("Show/Hide TDL");

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(impulse_plot,0,0);
    firstLayout->addWidget(show_tdl,1,0);

    widget->setLayout(firstLayout);

    connect(show_tdl,&QPushButton::clicked,this,&DialogRx::showTDL);

    return widget;
}

void DialogRx::updateImpulseResponse()
{
    h = m_mathematicalproduct->impulse();
    h_tdl = m_mathematicalproduct->impulseTDL();
    tau = m_mathematicalproduct->impulseTau();
    tau_tdl = m_mathematicalproduct->impulseTauTDL();

    impulse_plot->graph(0)->setData(tau, h);
    impulse_plot->graph(1)->setData(tau_tdl, h_tdl);
    QString title1 = "Normalized induced voltage as impulse response with maximum voltage = " + QString::number(round(m_mathematicalproduct->maxVoltage()*1e6)/1e6);
    QString title2 = "and normalized TDL model under US assumption with maximum TDL voltage = " + QString::number(round(m_mathematicalproduct->maxVoltageTDL()*1e6)/1e6);
    title_impulse->setText(title1 + QString("\n") + title2);
    impulse_plot->replot();
}

QWidget* DialogRx::TDLImpulseResponse(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    for(int i = 0; i<h_tdl.size(); i++){
        QCPItemLine *line = new QCPItemLine(customplot);
        line->start->setCoords(tau_tdl[i], h_tdl[i]);  // location of point 1 in plot coordinate
        line->end->setCoords(tau_tdl[i], -700);  // location of point 2 in plot coordinate
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
    customplot->yAxis->setLabel("Normalized TDL impulse response");
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

QWidget* DialogRx::fqResp(){
    QWidget *widget = new QWidget;
    fq_resp_plot = new QCustomPlot;

    vector<double> resp = m_mathematicalproduct->fqResp();
    QVector<double> freqResp = QVector(resp.begin(), resp.end());
    vector<double> f = m_mathematicalproduct->fq();
    QVector<double> freq = QVector(f.begin(), f.end());

    fq_resp_plot->addGraph();
    fq_resp_plot->graph(0)->setData(freq, freqResp);
    fq_resp_plot->graph(0)->setPen(QPen(Qt::blue));
//    fq_resp_plot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
//    fq_resp_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    fq_resp_plot->graph(0)->setName("Impulse");

    fq_resp_plot->xAxis->setLabel("f[Hz]");
    fq_resp_plot->yAxis->setLabel("|V_OC(f)| [dB]");
    fq_resp_plot->yAxis->grid()->setSubGridVisible(true);
    fq_resp_plot->xAxis->grid()->setSubGridVisible(true);

//    updateFqResp();

    fq_resp_plot->rescaleAxes();
    fq_resp_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    fq_resp_plot->legend->setVisible(true);
    fq_resp_plot->plotLayout()->insertRow(0);
    fq_resp_plot->plotLayout()->addElement(0, 0, new QCPTextElement(fq_resp_plot, "Frequency Response", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(fq_resp_plot,0,0);

    widget->setLayout(firstLayout);

    return widget;
}

void DialogRx::updateFqResp()
{
//    fq_resp_plot->graph(0)->data().clear();
    vector<double> f = m_mathematicalproduct->fq();
    QVector<double> freq = QVector(f.begin(), f.end());
    vector<double> resp = m_mathematicalproduct->fqResp();
    QVector<double> freqResp = QVector(resp.begin(), resp.end());
    fq_resp_plot->graph(0)->setData(freq, freqResp);
    fq_resp_plot->replot();
}

QWidget* DialogRx::InterferencePattern()
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
    connect(send_data,&QPushButton::clicked,this,&DialogRx::interferenceActivated);

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
DialogRx::DistributionInterference()
{
    QWidget *widget = new QWidget;
    m_distribution = new QCustomPlot;

    m_distribution->xAxis->setLabel("u");
    m_distribution->yAxis->setLabel("a");
    m_distribution->xAxis->setRange(0, 1);
    m_distribution->yAxis->setRange(0, 0.03);
    m_distribution->yAxis->grid()->setSubGridVisible(true);
    m_distribution->xAxis->grid()->setSubGridVisible(true);
    m_distribution->rescaleAxes();
    m_distribution->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    m_distribution->legend->setVisible(true);

    m_distribution->plotLayout()->insertRow(0);
    m_distribution->plotLayout()->addElement(0, 0, new QCPTextElement(m_distribution, "Angular Distribution", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(m_distribution,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget*
DialogRx::PrxAngularSpctr()
{
    QWidget *widget = new QWidget;
    pas_plot = new QCustomPlot;

    pas = m_mathematicalproduct->prxAngularSpread();
//    angular_distr = m_mathematicalproduct->angularDistr();
    u = m_mathematicalproduct->getu();

    for (int i = 0; i < pas.size(); i++) {
        QCPItemLine *line_impulse = new QCPItemLine(pas_plot);
        line_impulse->start->setCoords(u[i], pas[i]);  // location of point 1 in plot coordinate
        line_impulse->end->setCoords(u[i], -1500);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }

    // Plot power angular spectrum
    pas_plot->addGraph();
    pas_plot->graph(0)->setPen(QPen(Qt::blue));
    pas_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    pas_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    pas_plot->graph(0)->setData(u, pas);
    pas_plot->graph(0)->setName("PAS");

    pas_plot->xAxis->setLabel("u[rad/m]");
    pas_plot->yAxis->setLabel("S(u)[dBm]");
    pas_plot->yAxis->grid()->setSubGridVisible(true);
    pas_plot->xAxis->grid()->setSubGridVisible(true);
    pas_plot->rescaleAxes();
    pas_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    pas_plot->replot();
    pas_plot->legend->setVisible(true);
    pas_plot->plotLayout()->insertRow(0);
    pas_plot->plotLayout()->addElement(0, 0, new QCPTextElement(pas_plot,
                                                                          "Power Angular Density (PAS) and Angular Distribution",
                                                                          QFont("sans", 12, QFont::Bold)));
    QPushButton *show_tdl = new QPushButton("Show/Hide TDL");

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(pas_plot,0,0);
    firstLayout->addWidget(show_tdl,1,0);

    widget->setLayout(firstLayout);

    connect(show_tdl,&QPushButton::clicked,this,&DialogRx::showTDL);
    return widget;
}


void DialogRx::updatePrxAngularSpctr()
{
    pas_plot->clearItems();
    pas = m_mathematicalproduct->prxAngularSpread();
    u = m_mathematicalproduct->getu();
    for (int i = 0; i < pas.size(); i++) {
        QCPItemLine *line_impulse = new QCPItemLine(pas_plot);
        line_impulse->start->setCoords(u[i], pas[i]);  // location of point 1 in plot coordinate
        line_impulse->end->setCoords(u[i], -1500);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }
//    QVector npas = normalise<QVector<double>>(pas, m_mathematicalproduct->getPower());
//    void updatePrxAngularSpctr();
    pas_plot->graph(0)->setData(u, pas);
    pas_plot->replot();
}

QWidget*
DialogRx::AngularDistr()
{
    QWidget *widget = new QWidget;
    angular_distr_plot = new QCustomPlot;

    angular_distr = m_mathematicalproduct->angularDistr();
    u = m_mathematicalproduct->getu();

    for (int i = 0; i < angular_distr.size(); i++) {
        QCPItemLine *line_impulse = new QCPItemLine(angular_distr_plot);
        line_impulse->start->setCoords(u[i], angular_distr[i]);  // location of point 1 in plot coordinate
        line_impulse->end->setCoords(u[i], -1500);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }

    angular_distr_plot->addGraph();
    angular_distr_plot->graph(0)->setPen(QPen(Qt::blue));
    angular_distr_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    angular_distr_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    angular_distr_plot->graph(0)->setData(u, angular_distr);
    angular_distr_plot->graph(0)->setName("Angular Distribution");

    angular_distr_plot->xAxis->setLabel("u");
    angular_distr_plot->yAxis->setLabel("a");
    angular_distr_plot->xAxis->setRange(0, 1);
    angular_distr_plot->yAxis->setRange(0, 0.03);
    angular_distr_plot->yAxis->grid()->setSubGridVisible(true);
    angular_distr_plot->xAxis->grid()->setSubGridVisible(true);
    angular_distr_plot->rescaleAxes();
    angular_distr_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    angular_distr_plot->legend->setVisible(true);

    angular_distr_plot->plotLayout()->insertRow(0);
    angular_distr_plot->plotLayout()->addElement(0, 0, new QCPTextElement(angular_distr_plot, "Angular Distribution", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(angular_distr_plot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget*
DialogRx::PrxDopplerSpctr()
{
    QWidget *widget = new QWidget;
    pds_plot = new QCustomPlot;

    pds = m_mathematicalproduct->prxDopplerSpread();
    doppler_distr = m_mathematicalproduct->dopplerDistr();
    w = m_mathematicalproduct->getw();

    QVector<double> localpds = pds;
    QVector<double> localw = w;

    for (int i = 0; i < pds.size(); i++) {
        QCPItemLine *line_impulse = new QCPItemLine(pds_plot);
        line_impulse->start->setCoords(w[i], pds[i]);  // location of point 1 in plot coordinate
        line_impulse->end->setCoords(w[i], -600);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }

    // Plot physiscal impulse response
    pds_plot->addGraph();
    pds_plot->graph(0)->setPen(QPen(Qt::blue));
    pds_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    pds_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    pds_plot->graph(0)->setData(w, pds);
    pds_plot->graph(0)->setName("PDS");

    pds_plot->xAxis->setLabel("w[rad/s]");
    pds_plot->yAxis->setLabel("S(w)[dB]");
    pds_plot->yAxis->grid()->setSubGridVisible(true);
    pds_plot->xAxis->grid()->setSubGridVisible(true);
    pds_plot->rescaleAxes();
    pds_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    pds_plot->replot();
    pds_plot->legend->setVisible(true);
    pds_plot->plotLayout()->insertRow(0);
    pds_plot->plotLayout()->addElement(0, 0, new QCPTextElement(pds_plot,
                                                                          "Power Doppler Density (PAS) and Doppler Distribution",
                                                                          QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(pds_plot,0,0);

    widget->setLayout(firstLayout);

    return widget;
}

void DialogRx::updatePrxDopplerSpctr()
{
    pds_plot->clearItems();
    pds = m_mathematicalproduct->prxDopplerSpread();
    w = m_mathematicalproduct->getw();
    for (int i = 0; i < pds.size(); i++) {
        QCPItemLine *line_impulse = new QCPItemLine(pds_plot);
        line_impulse->start->setCoords(w[i], pds[i]);  // location of point 1 in plot coordinate
        line_impulse->end->setCoords(w[i], -1500);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }
//    QVector npas = normalise<QVector<double>>(pas, m_mathematicalproduct->getPower());
//    void updatePrxAngularSpctr();
    pds_plot->graph(0)->setData(w, pds);
    pds_plot->replot();
}

QWidget*
DialogRx::DopplerDistr()
{
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    for(int i = 0; i<doppler_distr.size(); i++){
        QCPItemLine *line = new QCPItemLine(customplot);
        line->start->setCoords(w[i], doppler_distr[i]);  // location of point 1 in plot coordinate
        line->end->setCoords(w[i], -600);  // location of point 2 in plot coordinate
        line->setPen(QPen(Qt::red));
    }
    // Plot physiscal impulse response
    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::red));
    customplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customplot->graph(0)->setData(w, doppler_distr);
    customplot->graph(0)->setName("Doppler distribution");

    customplot->xAxis->setLabel("w [rad/s]");
    customplot->yAxis->setLabel("a(w)[dB]");
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->legend->setVisible(true);
    customplot->replot();

    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Doppler distribution", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogRx::DopplerSpectrum(){
    QWidget *widget = new QWidget;
    doppler_spctr_plot = new QCustomPlot;
//    QCustomPlot *customplot = new QCustomPlot;

//    vector<double> dp = m_mathematicalproduct->getDoppler();
//    doppler = QVector(dp.begin(), dp.end());
    doppler = vec2QVec<double>(m_mathematicalproduct->getDoppler());
    vector<double> omg = m_mathematicalproduct->getOmega();
    omega = QVector(omg.begin(), omg.end());

    doppler_spctr_plot->addGraph();
    doppler_spctr_plot->graph(0)->setPen(QPen(Qt::red));
    doppler_spctr_plot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
    doppler_spctr_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    doppler_spctr_plot->graph(0)->setData(omega, doppler);
    doppler_spctr_plot->graph(0)->setName("Doppler spectrum");

    doppler_spctr_plot->xAxis->setLabel("\u03C9[rad/s]");
    doppler_spctr_plot->yAxis->setLabel("a(\u03c9)[dB]");
    doppler_spctr_plot->yAxis->grid()->setSubGridVisible(true);
    doppler_spctr_plot->xAxis->grid()->setSubGridVisible(true);
    doppler_spctr_plot->rescaleAxes();
    doppler_spctr_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    doppler_spctr_plot->replot();

    doppler_spctr_plot->plotLayout()->insertRow(0);
    doppler_spctr_plot->plotLayout()->addElement(0, 0, new QCPTextElement(doppler_spctr_plot, "Dopler spectrum", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(doppler_spctr_plot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

void DialogRx::updateDopplerSpctr()
{
    vector<double> dp = m_mathematicalproduct->getDoppler();
    doppler = QVector(dp.begin(), dp.end());
    vector<double> omg = m_mathematicalproduct->getOmega();
    omega = QVector(omg.begin(), omg.end());
    doppler_spctr_plot->graph(0)->setData(omega, doppler);
    doppler_spctr_plot->replot();
}

QWidget* DialogRx::PDP(){
    QWidget *widget = new QWidget;
    pdp_plot = new QCustomPlot;
    pdp = vec2QVec<double>(m_mathematicalproduct->getPDP());
    tau = m_mathematicalproduct->impulseTau();

    for (int i = 0; i < pdp.size(); i++) {
        QCPItemLine *line_impulse = new QCPItemLine(pdp_plot);
        line_impulse->start->setCoords(tau[i], pdp[i]);  // location of point 1 in plot coordinate
        line_impulse->end->setCoords(tau[i], -600);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }

    pdp_plot->addGraph();
    pdp_plot->graph(0)->setPen(QPen(Qt::blue));
    pdp_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    pdp_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    pdp_plot->graph(0)->setData(tau, pdp);
    pdp_plot->graph(0)->setName("Power Delay Profile");

    pdp_plot->xAxis->setLabel("\u03C4[ns]");
    pdp_plot->yAxis->setLabel("P(\u03C4)[dB]");
    pdp_plot->yAxis->grid()->setSubGridVisible(true);
    pdp_plot->xAxis->grid()->setSubGridVisible(true);
    pdp_plot->rescaleAxes();
    pdp_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    pdp_plot->replot();

    pdp_plot->plotLayout()->insertRow(0);
    pdp_plot->plotLayout()->addElement(0, 0, new QCPTextElement(pdp_plot, "Power delay profile", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(pdp_plot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

void DialogRx::updatePDP()
{
    pdp_plot->clearItems();
    pdp = vec2QVec<double>(m_mathematicalproduct->getPDP());
    tau = m_mathematicalproduct->impulseTau();
    for (int i = 0; i < pdp.size(); i++) {
        QCPItemLine *line_impulse = new QCPItemLine(pdp_plot);
        line_impulse->start->setCoords(tau[i], pdp[i]);  // location of point 1 in plot coordinate
        line_impulse->end->setCoords(tau[i], -600);  // location of point 2 in plot coordinate
        line_impulse->setPen(QPen(Qt::blue));
    }
    pdp_plot->graph(0)->setData(tau, pdp);
    pdp_plot->replot();
}

QWidget *DialogRx::SpcCrltn()
{
    QWidget *widget = new QWidget;
    spc_crltn_plot = new QCustomPlot;

//    pds = m_mathematicalproduct->prxDopplerSpread();
//    doppler_distr = m_mathematicalproduct->dopplerDistr();
//    vector<double> sc = m_mathematicalproduct->spaceCrltn();
//    vector<double> dz = m_mathematicalproduct->deltaZ();
//    QVector<double> deltaZ;
//    QVector<double> spaceCrltn;
//    if (dz.size() >=400) {
//        deltaZ = QVector(dz.begin(),dz.begin() + 400);
//        spaceCrltn = QVector(sc.begin(), sc.begin() + 400);
//    } else {
//        deltaZ = QVector(dz.begin(),dz.end());
//        spaceCrltn = QVector(sc.begin(), sc.end());
//    }


//    QVector<double> localpds = pds;
//    QVector<double> localw = w;

    // Plot physiscal impulse response
    spc_crltn_plot->addGraph();
    spc_crltn_plot->graph(0)->setPen(QPen(Qt::blue));
//    spc_crltn_plot->graph(0)->setData(deltaZ, spaceCrltn);
    spc_crltn_plot->graph(0)->setName("Spatial Correlation");

    spc_crltn_plot->xAxis->setLabel("z");
    spc_crltn_plot->yAxis->setLabel("R");
    spc_crltn_plot->yAxis->grid()->setSubGridVisible(true);
    spc_crltn_plot->xAxis->grid()->setSubGridVisible(true);
    spc_crltn_plot->rescaleAxes();
    spc_crltn_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    spc_crltn_plot->replot();
    spc_crltn_plot->legend->setVisible(true);
    spc_crltn_plot->plotLayout()->insertRow(0);
    spc_crltn_plot->plotLayout()->addElement(0, 0, new QCPTextElement(spc_crltn_plot,
                                                                          "Spatial Correlation",
                                                                          QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(spc_crltn_plot,0,0);

    widget->setLayout(firstLayout);

    return widget;
}

void DialogRx::updateSpcCrltn()
{
    vector<double> sc = m_mathematicalproduct->spaceCrltn();
    vector<double> dz = m_mathematicalproduct->deltaZ();
    if (dz.size() >= 400){
        QVector<double> spaceCrltn;
        QVector<double> deltaZ;
        spaceCrltn = QVector(sc.begin(), sc.begin() + 400);
        deltaZ = QVector(dz.begin(), dz.begin() + 400);
        spc_crltn_plot->graph(0)->setData(deltaZ, spaceCrltn);
        spc_crltn_plot->replot();
    }
}

QWidget *DialogRx::timeCrltn()
{
    QWidget *widget = new QWidget;
    tm_crltn_plot = new QCustomPlot;

//    vector<double> dt = m_mathematicalproduct->deltaZ();
//    QVector<double> deltaT = QVector(dt.begin(), dt.end());
//    vector<double> tc = m_mathematicalproduct->spaceCrltn();
//    QVector<double> timeCrltn = QVector(tc.begin(), tc.end());

    // Plot physiscal impulse response
    tm_crltn_plot->addGraph();
    tm_crltn_plot->graph(0)->setPen(QPen(Qt::blue));
//    tm_crltn_plot->graph(0)->setData(deltaT, timeCrltn);
    tm_crltn_plot->graph(0)->setName("Time Correlation");

    tm_crltn_plot->xAxis->setLabel("t");
    tm_crltn_plot->yAxis->setLabel("R");
    tm_crltn_plot->yAxis->grid()->setSubGridVisible(true);
    tm_crltn_plot->xAxis->grid()->setSubGridVisible(true);
    tm_crltn_plot->rescaleAxes();
    tm_crltn_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    tm_crltn_plot->replot();
    tm_crltn_plot->legend->setVisible(true);
    tm_crltn_plot->plotLayout()->insertRow(0);
    tm_crltn_plot->plotLayout()->addElement(0, 0, new QCPTextElement(tm_crltn_plot,
                                                                          "Spatial Correlation",
                                                                          QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(tm_crltn_plot,0,0);

    widget->setLayout(firstLayout);

    return widget;
}

void DialogRx::updateTimeCrltn()
{
    vector<double> tc = m_mathematicalproduct->timeCrltn();
    QVector<double> timeCrltn = QVector(tc.begin(), tc.end());
    vector<double> dt = m_mathematicalproduct->timeCrltnT();
    QVector<double> deltaT = QVector(dt.begin(), dt.end());
    tm_crltn_plot->graph(0)->setData(deltaT, timeCrltn);
    tm_crltn_plot->replot();
}

void DialogRx::changeGraph(){
}

void
DialogRx::setInterferencePattern(vector<double> impulse_r, double min, double max)
{
    m_interferencepattern->enableImpulseInterference(impulse_r, min, max);
}

void
DialogRx::setDistributionInterference(map<double,double> impulse,QVector<double> rice_distribution)
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

void DialogRx::setEnable(bool enable){
    this->enable = enable;
    m_posx->setEnabled(this->enable);
    m_posy->setEnabled(this->enable);
}

void DialogRx::newProperties(){
    m_mathematicalproduct->setSpeed(m_speed->value());
    m_mathematicalproduct->setOrientation(m_orientation->value());
    int posx = m_posx->value();
    int posy = m_posy->value();
    m_mathematicalproduct->setPosY(posy);
    m_mathematicalproduct->setPosX(posx);
    m_mathematicalproduct->setTargetSNR(m_target_snr->value());
    m_mathematicalproduct->setNoiseFigure(m_noise_figure->value());
    m_mathematicalproduct->setInterferecenceMargin(m_interferencemargin->value());
    m_mathematicalproduct->newProperties();
    close();
}


void DialogRx::buttonBoxClicked(QAbstractButton *button)
{
    if (button->text() == "OK") {

        saveProperties();

    } else if (button->text() == "Save") {

        saveToDisk();

    }
}


void DialogRx::saveProperties(){
    newProperties();
}

void DialogRx::saveToDisk()
{

    QString fichier = QFileDialog::getSaveFileName(this, "Save file", QString(), "Table (*.csv)");
    emit save(fichier.toStdString());

}

void DialogRx::showTDL(){
    show_tdl = !show_tdl;
    if (show_tdl){
        for (int i=0; i<h_tdl.size();i++){
            QCPItemLine *line_tdl = new QCPItemLine(impulse_plot);
            impulse_tdl.push_back(line_tdl);
            line_tdl->start->setCoords(tau_tdl[i], h_tdl[i]);  // location of point 1 in plot coordinate
            line_tdl->end->setCoords(tau_tdl[i], -700);  // location of point 2 in plot coordinate
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

void DialogRx::update()
{
    switch (idxTab) {
    case 0:
        updateGeneralTab();
        break;
    case 1:
        updateImpulseResponse();
        break;
    case 2:
        updateFqResp();
        break;
    case 3:
        break;
    case 4:
        updatePrxAngularSpctr();
        break;
    case 5:
        updatePrxDopplerSpctr();
        break;
    case 6:
        updateSpcCrltn();
        break;
    case 7:
        updateTimeCrltn();
        break;
    case 8:
        updatePDP();
        break;
    default:
        break;
    }
}

void DialogRx::tabOpened(int index)
{
    idxTab = index;

    switch (idxTab) {
    case 0:
        updateGeneralTab();
        break;
    case 1:
        updateImpulseResponse();
        impulse_plot->graph(0)->rescaleAxes();
        break;
    case 2:
        updateFqResp();
        fq_resp_plot->graph(0)->rescaleAxes();
        break;
    case 3:
        break;
    case 4:
        updatePrxAngularSpctr();
        pas_plot->graph(0)->rescaleAxes();
        break;
    case 5:
        updatePrxDopplerSpctr();
        pds_plot->graph(0)->rescaleAxes();
        break;
    case 6:
        updateSpcCrltn();
        spc_crltn_plot->graph(0)->rescaleAxes();
        break;
    case 7:
        updateTimeCrltn();
        tm_crltn_plot->graph(0)->rescaleAxes();
        break;
    case 8:
        updatePDP();
        pdp_plot->graph(0)->rescaleAxes();
        break;
    default:
        break;
    }
}
