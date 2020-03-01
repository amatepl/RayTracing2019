#include "dialogtransmitterproduct.h"

DialogTransmitterProduct::DialogTransmitterProduct(TransmitterProduct *graphic,DialogFactory* dialogfactory)
{
    m_dialogfactory = dialogfactory;
    createDialog();
    setPosX(graphic->getPosX());
    setPosY(graphic->getPosY());
    setPower(graphic->getPower());
    setFrequency(graphic->getFrequency());
    setOrientation(graphic->getOrientation());
    setModel(dipole);
    setAttribute(Qt::WA_DeleteOnClose,true);
    exec();
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

    m_row = new QSpinBox(this);
    m_column = new QSpinBox(this);
    m_row->setRange(1,8);
    m_column->setRange(1,8);
    m_row->setAccelerated(true);
    m_column->setAccelerated(true);
    m_antennaDistance = new QDoubleSpinBox(this);
    m_antennaDistance->setRange(0.05,20.0);
    m_antennaDistance->setAccelerated(true);

    m_posx = new QSpinBox(this);
    m_posy = new QSpinBox(this);
    m_orientation = new QDoubleSpinBox(this);
    m_orientation->setRange(-360,360);
    m_posx->setRange(0,5000);
    m_posx->setAccelerated(true);
    m_posy->setRange(0,5000);
    m_posy->setAccelerated(true);

    m_frequency = new QDoubleSpinBox(this);
    m_frequency->setRange(0.00,999.00);
    m_frequency->setAccelerated(true);

    m_frequencyorder = new QComboBox(this);
    m_frequencyorder->addItem("kHz");
    m_frequencyorder->addItem("MHz");
    m_frequencyorder->addItem("GHz");

    QHBoxLayout *frequency = new QHBoxLayout();
    frequency->addWidget(m_frequency);

    frequency->addWidget(m_frequencyorder);

    m_power = new QDoubleSpinBox(this);
    m_power->setRange(0.0,100.0);
    m_power->setAccelerated(true);

    QFormLayout *modelProperties = new QFormLayout(this);
    modelProperties->addRow("Antenna model: ",m_modelBox);
    modelProperties->addRow("number of row antenna: ",m_row);
    modelProperties->addRow("number of column antenna: ",m_column);
    QString distance = "Distance relative to ";
    distance.append(QChar(0x03BB));
    modelProperties->addRow(distance.append(" :"),m_antennaDistance);

    QGroupBox *model = new QGroupBox("Model antenna");
    model->setLayout(modelProperties);

    QFormLayout *geoProperties = new QFormLayout(this);
    geoProperties->addRow("Orientation: ",m_orientation);
    geoProperties->addRow("X center: ",m_posx);
    geoProperties->addRow("Y center: ",m_posy);

    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QFormLayout *phyProperties = new QFormLayout(this);
    phyProperties->addRow("Frequency: ",frequency);
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
    connect(save,SIGNAL(clicked()),this,SLOT(newProperties()));
    connect(plot,SIGNAL(clicked()),this,SLOT(openPlot()));
    connect(m_modelBox,SIGNAL(activated(QString)),this,SLOT(changeModel(QString)));

}

int DialogTransmitterProduct::getPosX(){
    return m_posx->value();
}

int DialogTransmitterProduct::getPosY(){
    return m_posy->value();
}

double DialogTransmitterProduct::getOrientation(){
    return m_orientation->value();
}

unsigned long DialogTransmitterProduct::getFrequency(){
    QString text = m_frequencyorder->currentText();
    if (text == "kHz"){
        return unsigned(long(m_frequency->value()*1e3));
    }
    else if (text == "MHz"){
        return unsigned(long(m_frequency->value()*1e6));
    }
    else {
        return unsigned(long(m_frequency->value()*1e9));
    }
}

double DialogTransmitterProduct::getPower(){
    return m_power->value();
}

int DialogTransmitterProduct::getRow(){
    return m_row->value();
}

int DialogTransmitterProduct::getColumn() {
    return m_column->value();
}
double DialogTransmitterProduct::getAntennaDistance() {
    return m_antennaDistance->value();
}
int DialogTransmitterProduct::getModel() {

}

void DialogTransmitterProduct::setPosX(int posX){
    m_posx->setValue(posX);
}

void DialogTransmitterProduct::setPosY(int posY){
    m_posy->setValue(posY);
}

void DialogTransmitterProduct::setOrientation(double orientation){
    m_orientation->setValue(orientation);
}

void DialogTransmitterProduct::setPower(double power){
    m_power->setValue(power);
}

void DialogTransmitterProduct::setFrequency(unsigned long frequency){
    if (frequency/1e3 <= 999){
        m_frequency->setValue(int(frequency/1e3));
        m_frequencyorder->setCurrentText("kHz");
    }
    else if (frequency/1e6 <= 999){
        m_frequency->setValue(int(frequency/1e6));
        m_frequencyorder->setCurrentText("MHz");
    }
    else{
        m_frequency->setValue(int(frequency/1e9));
        m_frequencyorder->setCurrentText("GHz");
    }
}

void DialogTransmitterProduct::setRow(int row){

}

void DialogTransmitterProduct::setColumn(int column) {

}

void DialogTransmitterProduct::setAntennaDistance(double distance) {

}

void  DialogTransmitterProduct::setModel(Model model) {
    m_model = model;
    if (model == dipole){
        m_modelBox->setCurrentText("Half-wave dipole antenna");
        setRow(1);
        setColumn(1);
        setAntennaDistance(0.05);
        m_row->setEnabled(false);
        m_column->setEnabled(false);
        m_antennaDistance->setEnabled(false);
    }
    else if (model == array) {
        m_modelBox->setCurrentText("Array dipole antenna");
        m_row->setEnabled(true);
        m_column->setEnabled(true);
        m_antennaDistance->setEnabled(true);
    }
}

void DialogTransmitterProduct::attachObserver(DialogObserver *dialogobserver){
    m_dialogobserver.push_back(dialogobserver);
}

void DialogTransmitterProduct::detachObserver(DialogObserver *dialogobserver){
    unsigned long long i = 0;
    for (m_dialogobserveriterator = m_dialogobserver.begin();
         m_dialogobserveriterator != m_dialogobserver.end();
         ++m_dialogobserveriterator){
        if (m_dialogobserver.at(i) == dialogobserver){
            m_dialogobserver.erase(m_dialogobserveriterator);
        }
        i++;
    }
}

void DialogTransmitterProduct::notify(){
    for (unsigned long long i=0;i<m_dialogobserver.size();i++){
        m_dialogobserver.at(i)->update();
    }
}

void DialogTransmitterProduct::newProperties(){
    m_dialogfactory->receiveTransmitterProduct(this);
    close();
}

void DialogTransmitterProduct::openPlot(){
    DialogObserver *pattern = new PatternWindow(this);
    attachObserver(pattern);
    notify();
}

void DialogTransmitterProduct::changeModel(QString model)
{
    if (model == "Half-wave dipole antenna")setModel(dipole);
    else if (model == "Array dipole antenna")setModel(array);
}
