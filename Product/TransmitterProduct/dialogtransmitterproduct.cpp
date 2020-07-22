#include "dialogtransmitterproduct.h"

DialogTransmitterProduct::DialogTransmitterProduct(TransmitterProduct *mathematicalproduct):m_mathematicalproduct(mathematicalproduct)
{
    createDialog();
    setPosX(m_mathematicalproduct->getPosX());
    setPosY(m_mathematicalproduct->getPosY());
    setPower(m_mathematicalproduct->getPower());
    setFrequency(m_mathematicalproduct->getFrequency());
    setBandwidth(m_mathematicalproduct->getBandwidth());
    setOrientation(m_mathematicalproduct->getOrientation());
    setPrincipalOrientation(m_mathematicalproduct->principalOrientation());
    setKind(m_mathematicalproduct->getKind());
    setRow(m_mathematicalproduct->getRow());
    setColumn(m_mathematicalproduct->getColumn());
    setAttribute(Qt::WA_DeleteOnClose,true);
    open();
}

DialogTransmitterProduct::~DialogTransmitterProduct(){

}

void DialogTransmitterProduct::createDialog(){
    setWindowTitle("Transmitter properties: ");
    setWindowIcon(QIcon(GraphicsTransmitterProduct::getImage()));
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

    QHBoxLayout *frequency = new QHBoxLayout();
    frequency->addWidget(m_frequencyValue);
    frequency->addWidget(m_frequencyorder);

    QHBoxLayout *bandwidth = new QHBoxLayout();
    bandwidth->addWidget(m_bwvalue);
    bandwidth->addWidget(m_bworder);

    m_power = new QDoubleSpinBox(this);
    m_power->setRange(0.0,100.0);
    m_power->setAccelerated(true);

    QFormLayout *modelProperties = new QFormLayout(this);
    modelProperties->addRow("Antenna model: ",m_modelBox);
    modelProperties->addRow("number of row antenna: ",m_rowBox);
    modelProperties->addRow("number of column antenna: ",m_columnBox);
    QString distance = "Distance relative to ";
    distance.append(QChar(0x03BB));

    QGroupBox *model = new QGroupBox("Model antenna");
    model->setLayout(modelProperties);

    QFormLayout *geoProperties = new QFormLayout(this);
    geoProperties->addRow("Orientation: ",m_orientationValue);
    geoProperties->addRow("Principal orientation: ", m_pr_orientationValue);
    geoProperties->addRow("X center: ",m_posx);
    geoProperties->addRow("Y center: ",m_posy);

    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QFormLayout *phyProperties = new QFormLayout(this);
    phyProperties->addRow("Frequency: ",frequency);
    phyProperties->addRow("Bandwidth: ",bandwidth);
    phyProperties->addRow("Power: ",m_power);

    QGroupBox *phy = new QGroupBox("Physical properties");
    phy->setLayout(phyProperties);

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(model,0,0);
    firstLayout->addWidget(geo,1,0);
    firstLayout->addWidget(phy,2,0);
    firstLayout->addLayout(buttonLayout,3,0);

    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveProperties()));
    connect(plot,SIGNAL(clicked()),this,SLOT(openPlot()));
    connect(m_modelBox,SIGNAL(activated(QString)),this,SLOT(changeModel(QString)));

}

unsigned long DialogTransmitterProduct::getFrequency(){
    QString text = m_frequencyorder->currentText();
    if (text == "kHz"){
        m_frequency = m_frequencyValue->value()*1.0e3;
    }
    else if (text == "MHz"){
        m_frequency = m_frequencyValue->value()*1.0e6;
    }
    else {
        m_frequency = m_frequencyValue->value()*1.0e9;
    }
    return m_frequency;
}

double DialogTransmitterProduct::getOrientation(){
    m_orientation = m_orientationValue->value();
    return m_orientation;
}

unsigned long DialogTransmitterProduct::getBandwidth(){
    QString text = m_bworder->currentText();
    if (text == "kHz"){
        m_bandwidth = unsigned(long(m_bwvalue->value()*1e3));
    }
    else if (text == "MHz"){
        m_bandwidth = unsigned(long(m_bwvalue->value()*1e6));
    }
    else {
        m_bandwidth = unsigned(long(m_bwvalue->value()*1e9));
    }
    return m_bandwidth;
}

char DialogTransmitterProduct::principalOrientation(){
    m_pr_orientation = m_pr_orientationValue->value();
    return m_pr_orientation;
}

void DialogTransmitterProduct::setFrequency(unsigned long frequency){
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
    m_frequency = frequency;
}

void DialogTransmitterProduct::setBandwidth(unsigned long bandwidth){
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
    m_bandwidth = bandwidth;
}

void DialogTransmitterProduct::setOrientation(double orientation){
    m_orientation = orientation;
    m_orientationValue->setValue(m_orientation);
}

void DialogTransmitterProduct::setPrincipalOrientation(char orientation){
    m_pr_orientation = orientation;
    m_pr_orientationValue->setValue(m_pr_orientation);
}

void  DialogTransmitterProduct::setKind(Kind kind) {
    m_kind = kind;
    if (kind == dipole){
        m_modelBox->setCurrentText("Half-wave dipole antenna");
        setRow(1);
        setColumn(1);
        m_rowBox->setEnabled(false);
        m_columnBox->setEnabled(false);
    }
    else if (kind == dipolereflector){
        m_modelBox->setCurrentText("Half-wave dipole antenna with reflector");
        setRow(1);
        setColumn(1);
        m_rowBox->setEnabled(false);
        m_columnBox->setEnabled(false);
    }
    else if (kind == array) {
        m_modelBox->setCurrentText("Array dipole antenna");
        m_rowBox->setEnabled(true);
        m_columnBox->setEnabled(true);
    }
    else if (kind == arrayreflector) {
        m_modelBox->setCurrentText("Array dipole antenna with reflector");
        m_rowBox->setEnabled(true);
        m_columnBox->setEnabled(true);
    }
}

void DialogTransmitterProduct::newProperties(){
    m_mathematicalproduct->setRow(getRow());
    m_mathematicalproduct->setColumn(getColumn());
    m_mathematicalproduct->setKind(getKind());
    m_mathematicalproduct->setFrequency(getFrequency());
    m_mathematicalproduct->setBandwidth(getBandwidth());
    m_mathematicalproduct->setPower(getPower());
    m_mathematicalproduct->setPrincipalOrientation(principalOrientation());
    m_mathematicalproduct->newProperties(QPointF(getPosX(),getPosY()),getOrientation());
}

void DialogTransmitterProduct::saveProperties(){
    newProperties();
    close();
}

void DialogTransmitterProduct::openPlot(){
    getFrequency();
    m_row = getRow();
    m_column = getColumn();
    m_orientation = getOrientation();
    m_pr_orientation = principalOrientation();
    new PatternWindow(this);
}

void DialogTransmitterProduct::changeModel(QString model)
{
    if (model == "Half-wave dipole antenna")setKind(dipole);
    else if (model == "Array dipole antenna")setKind(array);
    else if (model == "Half-wave dipole antenna with reflector")setKind(dipolereflector);
    else if (model == "Array dipole antenna with reflector")setKind(arrayreflector);
}
