#include "dialogtx.h"

DialogTx::DialogTx(TxInterface *mathematicalproduct):m_tx(mathematicalproduct)
{
    m_tabwidget = new QTabWidget;
    /* Gneral options */
//    createDialog();
    m_tabwidget->addTab(createDialog(), tr("General"));
    updateGeneralTab();
    /* Path Loss*/
    m_tabwidget->addTab( createPathLossTab(), tr("Path Loss"));
    /* Shadowing */
    //    m_tabwidget->addTab( create , tr("Shadownig"));
//    m_tabwidget->addTab(templatePlot(m_shadowingPlot,"Shadowing around transmitter at a reference distance",
//                                     "Angle [rad]", "P [dBm]"), tr("Shadowing"));
    m_tabwidget->addTab(createShadowingTab(), tr("Shadowing"));
    /* Cell Range */
    m_tabwidget->addTab(createCellRangeTab(), tr("Cell range"));

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addWidget(m_tabwidget);
    setLayout(mainlayout);
    open();
}

DialogTx::~DialogTx(){
}

QWidget* DialogTx::templatePlot(QCustomPlot *plot,
                                             QString title,
                                             QString xlabel,
                                             QString ylabel,
                                             bool xlog,
                                             bool ylog)
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

QWidget *DialogTx::createDialog(){
    QWidget *widget = new QWidget(this);
    setWindowTitle("Transmitter properties: ");
    setWindowIcon(QIcon(GraphicsTx::getImage()));
    QPushButton *save = new QPushButton("Save",this);
    QPushButton *cancel = new QPushButton("Cancel",this);
    QPushButton *plot = new QPushButton("Plot gain",this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(plot);
    buttonLayout->addWidget(save);
    buttonLayout->addWidget(cancel);
    buttonLayout->setAlignment(Qt::AlignRight);

    m_modelBox = new QComboBox(this);
    m_modelBox->addItem("Half-wave dipole antenna");
    m_modelBox->addItem("Array dipole antenna");
    m_modelBox->addItem("Half-wave dipole antenna with reflector");
    m_modelBox->addItem("Array dipole antenna with reflector");

    m_rowBox = new QSpinBox(this);
    m_columnBox = new QSpinBox(this);
    m_rowBox->setRange(1,8);
    m_columnBox->setRange(1,8);
    m_rowBox->setAccelerated(true);
    m_columnBox->setAccelerated(true);

    m_posx = new QSpinBox(this);
    m_posy = new QSpinBox(this);
    m_orientationValue = new QDoubleSpinBox(this);
    m_orientationValue->setRange(-360,360);
    m_pr_orientationValue = new QSpinBox(this);
    m_pr_orientationValue->setRange(-5,5);
    m_posx->setRange(0,5000);
    m_posx->setAccelerated(true);
    m_posy->setRange(0,5000);
    m_posy->setAccelerated(true);

    m_frequencyValue = new QDoubleSpinBox(this);
    m_frequencyValue->setRange(0.00,999.00);
    m_frequencyValue->setAccelerated(true);
    m_bwvalue = new QDoubleSpinBox(this);
    m_bwvalue->setRange(0.00,999.00);
    m_bwvalue->setAccelerated(true);

    m_frequencyorder = new QComboBox(this);
    m_frequencyorder->addItem("kHz");
    m_frequencyorder->addItem("MHz");
    m_frequencyorder->addItem("GHz");
    m_bworder = new QComboBox(this);
    m_bworder->addItem("kHz");
    m_bworder->addItem("MHz");
    m_bworder->addItem("GHz");

    QHBoxLayout *frequency = new QHBoxLayout;
    frequency->addWidget(m_frequencyValue);
    frequency->addWidget(m_frequencyorder);

    QHBoxLayout *bandwidth = new QHBoxLayout;
    bandwidth->addWidget(m_bwvalue);
    bandwidth->addWidget(m_bworder);

    m_power = new QDoubleSpinBox(this);
    m_power->setRange(0.0,100.0);
    m_power->setAccelerated(true);

    QFormLayout *modelProperties = new QFormLayout;
    modelProperties->addRow("Antenna model: ",m_modelBox);
    modelProperties->addRow("number of row antenna: ",m_rowBox);
    modelProperties->addRow("number of column antenna: ",m_columnBox);
    QString distance = "Distance relative to ";
    distance.append(QChar(0x03BB));

    QGroupBox *model = new QGroupBox("Model antenna", this);
    model->setLayout(modelProperties);

    QFormLayout *geoProperties = new QFormLayout;
    geoProperties->addRow("Orientation: ",m_orientationValue);
    geoProperties->addRow("Principal orientation: ", m_pr_orientationValue);
    geoProperties->addRow("X center: ",m_posx);
    geoProperties->addRow("Y center: ",m_posy);

    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QFormLayout *phyProperties = new QFormLayout;
    phyProperties->addRow("Frequency: ",frequency);
    phyProperties->addRow("Bandwidth: ",bandwidth);
    phyProperties->addRow("Power: ",m_power);

    QGroupBox *phy = new QGroupBox("Physical properties");
    phy->setLayout(phyProperties);

    QGridLayout *firstLayout = new QGridLayout(widget);
    firstLayout->addWidget(model,0,0);
    firstLayout->addWidget(geo,1,0);
    firstLayout->addWidget(phy,2,0);
    firstLayout->addLayout(buttonLayout,3,0);

    widget->setLayout(firstLayout);
//    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveProperties()));
    connect(plot,SIGNAL(clicked()),this,SLOT(openPlot()));
    connect(m_modelBox,SIGNAL(activated(QString)),this,SLOT(changeModel(QString)));

    return widget;
}

void DialogTx::updateGeneralTab()
{
    setPosX(m_tx->getPosX());
    setPosY(m_tx->getPosY());
    setPower(m_tx->getPower());
    setFrequency(m_tx->getFrequency());
    setBandwidth(m_tx->getBandwidth());
    setOrientation(m_tx->getOrientation());
    setPrincipalOrientation(m_tx->principalOrientation());
//    setKind(m_tx->getKind());
//    setRow(m_tx->getRow());
//    setColumn(m_tx->getColumn());
    setAttribute(Qt::WA_DeleteOnClose,true);

}

QWidget *DialogTx::createPathLossTab()
{
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    m_tx->notifyObserversPathLoss();

    vector <double> dpl = m_tx->distancePathLoss();
    D = QVector<double>(dpl.begin(),dpl.end());

    vector<double> prx = m_tx->powerPathLoss();
    Prx = QVector<double>(prx.begin(), prx.end());

    vector<double> pl = m_tx->linearPathLoss();
    path_loss = QVector<double>(pl.begin(), pl.end());

    vector<double> fl = m_tx->friisLoss();
    friis_loss = QVector<double>(fl.begin(), fl.end());

    double n = m_tx->pathLossExponent();
    fading_variability = m_tx->fadingVariability();

    QVector<double> logD(D.size());
    for (int i = 0; i < D.size(); i++){
        logD[i] = log10(D[i]);
    }

    QCPGraph *path_loss_graph = new QCPGraph(customplot->xAxis, customplot->yAxis);

    path_loss_graph->setPen(QColor(Qt::blue));
    path_loss_graph->setName("Power received");
    path_loss_graph->setLineStyle(QCPGraph::lsLine);
    path_loss_graph->setData(logD, Prx);

    customplot->addGraph();
    customplot->graph(1)->setPen(QPen(Qt::red));
    customplot->graph(1)->setData(logD, path_loss);
    customplot->graph(1)->setName("Path Loss");

    customplot->addGraph();
    customplot->graph(2)->setPen(QPen(Qt::darkGreen));
    customplot->graph(2)->setData(logD, friis_loss);
    customplot->graph(2)->setName("Free propagation loss");

    customplot->xAxis->setLabel("Distance log(d/1m)]");
    customplot->yAxis->setLabel("Prx[dbm]");
    //customplot->xAxis->setScaleType(QCPAxis::stLogarithmic);
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

void DialogTx::updatePathLossTab()
{

}

QWidget *DialogTx::createShadowingTab()
{
    m_shadowingPlot = new QCustomPlot();
    shadowing(m_tx->notifyObserversShadowing());
    return templatePlot(m_shadowingPlot,"Shadowing around transmitter at a reference distance",
                 "Angle [rad]", "P [dBm]");
}

void DialogTx::updateShadowingTab()
{

}

void DialogTx::shadowing(map<double, double> shadow)
{
    QVector<double> angle;
    QVector<double> power;
    for (auto &sha: shadow){
        angle.push_back(sha.first);
        power.push_back(sha.second);
    }
    const auto mean = std::accumulate(power.begin(), power.end(), .0) / power.size();
    QVector<double> mean_vector(power.size(),mean);

    m_shadowingPlot->addGraph();
    m_shadowingPlot->graph(0)->setPen(QPen(Qt::blue));
    m_shadowingPlot->graph(0)->setData(angle, power);
    m_shadowingPlot->graph(0)->setName("Shadowing power");

    m_shadowingPlot->addGraph();
    m_shadowingPlot->graph(1)->setPen(QPen(Qt::red));
    m_shadowingPlot->graph(1)->setData(angle, mean_vector);
    m_shadowingPlot->graph(1)->setName("<Prx(d)>");

    m_shadowingPlot->rescaleAxes();
    m_shadowingPlot->replot();
    m_shadowingPlot->xAxis->setTicker(QSharedPointer<QCPAxisTickerPi>(new QCPAxisTickerPi));
    m_shadowingPlot->legend->setVisible(true);
}

QWidget *DialogTx::createCellRangeTab()
{
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;
    m_tx->cellRange();

    min_prx = m_tx->minPower();

    vector<double> proba = m_tx->probabilityConnection();
    probability = QVector<double>(proba.begin(), proba.end());

    vector<double> cr = m_tx->cellRangeConnection();
    cell_range = QVector<double>(cr.begin(), cr.end());

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

unsigned long DialogTx::getFrequency(){
//    QString text = m_frequencyorder->currentText();
//    if (text == "kHz"){
//        m_frequency = m_frequencyValue->value()*1.0e3;
//    }
//    else if (text == "MHz"){
//        m_frequency = m_frequencyValue->value()*1.0e6;
//    }
//    else {
//        m_frequency = m_frequencyValue->value()*1.0e9;
//    }
//    return m_frequency;
}

double DialogTx::getOrientation(){
//    m_orientation = m_orientationValue->value();
//    return m_orientation;
}

unsigned long DialogTx::getBandwidth(){
    QString text = m_bworder->currentText();
//    if (text == "kHz"){
//        m_bandwidth = unsigned(long(m_bwvalue->value()*1e3));
//    }
//    else if (text == "MHz"){
//        m_bandwidth = unsigned(long(m_bwvalue->value()*1e6));
//    }
//    else {
//        m_bandwidth = unsigned(long(m_bwvalue->value()*1e9));
//    }
//    return m_bandwidth;
}

char DialogTx::principalOrientation(){
//    m_pr_orientation = m_pr_orientationValue->value();
//    return m_pr_orientation;
}

void DialogTx::setFrequency(unsigned long frequency){
    if (frequency/1e3 <= 999.0){
        m_frequencyValue->setValue(frequency/1e3);
        m_frequencyorder->setCurrentText("kHz");
    }
    else if (frequency/1e6 <= 999.0){
        m_frequencyValue->setValue(frequency/1e6);
        m_frequencyorder->setCurrentText("MHz");
    }
    else{
        m_frequencyValue->setValue(frequency/1e9);
        m_frequencyorder->setCurrentText("GHz");
    }
}

void DialogTx::setBandwidth(unsigned long bandwidth){
    if (bandwidth/1e3 <= 999){
        m_bwvalue->setValue(bandwidth/1e3);
        m_bworder->setCurrentText("kHz");
    }
    else if (bandwidth/1e6 <= 999){
        m_bwvalue->setValue(bandwidth/1e6);
        m_bworder->setCurrentText("MHz");
    }
    else{
        m_bwvalue->setValue(bandwidth/1e9);
        m_bworder->setCurrentText("GHz");
    }
}

void DialogTx::setOrientation(double orientation){
    m_orientationValue->setValue(orientation);
}

void DialogTx::setPrincipalOrientation(char orientation){
    m_pr_orientationValue->setValue(orientation);
}

//void  DialogTx::setKind(Kind kind) {
//    m_kind = kind;
//    if (kind == dipole){
//        m_modelBox->setCurrentText("Half-wave dipole antenna");
//        setRow(1);
//        setColumn(1);
//        m_rowBox->setEnabled(false);
//        m_columnBox->setEnabled(false);
//    }
//    else if (kind == dipolereflector){
//        m_modelBox->setCurrentText("Half-wave dipole antenna with reflector");
//        setRow(1);
//        setColumn(1);
//        m_rowBox->setEnabled(false);
//        m_columnBox->setEnabled(false);
//    }
//    else if (kind == array) {
//        m_modelBox->setCurrentText("Array dipole antenna");
//        m_rowBox->setEnabled(true);
//        m_columnBox->setEnabled(true);
//    }
//    else if (kind == arrayreflector) {
//        m_modelBox->setCurrentText("Array dipole antenna with reflector");
//        m_rowBox->setEnabled(true);
//        m_columnBox->setEnabled(true);
//    }
//}

void DialogTx::setTxType(ph::TxType type)
{
    if (type == ph::TxType::dipole){
        m_modelBox->setCurrentText("Half-wave dipole antenna");
        m_rowBox->setEnabled(false);
        m_columnBox->setEnabled(false);
    }
    else if (type == ph::TxType::dipoleRefl){
        m_modelBox->setCurrentText("Half-wave dipole antenna with reflector");
        m_rowBox->setEnabled(false);
        m_columnBox->setEnabled(false);
    }
    else if (type == ph::TxType::array) {
        m_modelBox->setCurrentText("Array dipole antenna");
        m_rowBox->setEnabled(true);
        m_columnBox->setEnabled(true);
    }
    else if (type == ph::TxType::arrayRefl) {
        m_modelBox->setCurrentText("Array dipole antenna with reflector");
        m_rowBox->setEnabled(true);
        m_columnBox->setEnabled(true);
        }
}

void DialogTx::newProperties(){
    m_tx->setRow(getRow());
    m_tx->setColumn(getColumn());
//    m_tx->setKind(getKind());
    m_tx->setFrequency(getFrequency());
    m_tx->setBandwidth(getBandwidth());
    m_tx->setPower(getPower());
    m_tx->setPrincipalOrientation(principalOrientation());
    m_tx->newProperties(QPointF(getPosX(),getPosY()),getOrientation());
}

void DialogTx::saveProperties(){
    newProperties();
    close();
}

void DialogTx::openPlot(){
    getFrequency();
//    m_row = getRow();
//    m_column = getColumn();
//    m_orientation = getOrientation();
//    m_pr_orientation = principalOrientation();
//    new PatternWindow(this);
}

void DialogTx::changeModel(QString model)
{
//    if (model == "Half-wave dipole antenna")setKind(dipole);
//    else if (model == "Array dipole antenna")setKind(array);
//    else if (model == "Half-wave dipole antenna with reflector")setKind(dipolereflector);
//    else if (model == "Array dipole antenna with reflector")setKind(arrayreflector);
}
