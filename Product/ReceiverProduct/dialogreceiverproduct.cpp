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
    exec();
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

    customplot->xAxis->setLabel("\u03C4[ns]");
    customplot->yAxis->setLabel("h(\u03C4)[dB]");
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->rescaleAxes();
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, new QCPTextElement(customplot, "Physical impulse response", QFont("sans", 12, QFont::Bold)));

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(customplot,0,0);

    widget->setLayout(firstLayout);
    return widget;
}

QWidget* DialogReceiverProduct::TDLImpulseResponse(){
    QWidget *widget = new QWidget;
    QCustomPlot *customplot = new QCustomPlot;

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
