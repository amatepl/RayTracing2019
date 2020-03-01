#include "dialogreceiverproduct.h"

DialogReceiverProduct::DialogReceiverProduct(ReceiverProduct *graphic,DialogFactory* dialogfactory)
{
    m_dialogfactory = dialogfactory;
    createDialog();
    setPosX(graphic->getPosX());
    setPosY(graphic->getPosY());
    setFrequency(graphic->getFrequency());
    setAttribute(Qt::WA_DeleteOnClose,true);
    exec();
}

DialogReceiverProduct::~DialogReceiverProduct(){

}

void DialogReceiverProduct::createDialog(){
    setWindowTitle("Receiver properties: ");
    setWindowIcon(QIcon(GraphicsReceiverProduct::getImage()));
    QPushButton *save = new QPushButton("Save",this);
    QPushButton *cancel = new QPushButton("Cancel",this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(save);
    buttonLayout->addWidget(cancel);
    buttonLayout->setAlignment(Qt::AlignRight);

    m_posx = new QSpinBox(this);
    m_posy = new QSpinBox(this);
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

    m_power = new QLineEdit("Received power [dB]: ", this);
    m_efield = new QLineEdit("Electric fiedl [V/m]: ", this);

    QFormLayout *geoProperties = new QFormLayout(this);
    geoProperties->addRow("X center: ",m_posx);
    geoProperties->addRow("Y center: ",m_posy);

    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QFormLayout *phyProperties = new QFormLayout(this);
    phyProperties->addRow("Frequency: ",frequency);
    phyProperties->addRow(m_power);
    phyProperties->addRow(m_efield);

    QGroupBox *phy = new QGroupBox("Physical properties");
    phy->setLayout(phyProperties);

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(geo,0,0);
    firstLayout->addWidget(phy,1,0);
    firstLayout->addLayout(buttonLayout,2,0);

    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(newProperties()));
}

int DialogReceiverProduct::getPosX(){
    return m_posx->value();
}

int DialogReceiverProduct::getPosY(){
    return m_posy->value();
}

unsigned long DialogReceiverProduct::getFrequency(){
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

double DialogReceiverProduct::getPower(){

}

void DialogReceiverProduct::setPosX(int posX){
    m_posx->setValue(posX);
}

void DialogReceiverProduct::setPosY(int posY){
    m_posy->setValue(posY);
}

void DialogReceiverProduct::setFrequency(unsigned long frequency){
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

void DialogReceiverProduct::newProperties(){
    m_dialogfactory->receiveReceiverProduct(this);
    close();
}
