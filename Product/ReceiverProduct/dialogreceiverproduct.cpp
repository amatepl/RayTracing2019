#include "dialogreceiverproduct.h"

DialogReceiverProduct::DialogReceiverProduct(ReceiverProduct *mathematicalproduct):
    m_mathematicalproduct(mathematicalproduct)
{
    createDialog();
    setPosX(m_mathematicalproduct->getPosX());
    setPosY(m_mathematicalproduct->getPosY());
    setPower(m_mathematicalproduct->getPower());
    setEField(m_mathematicalproduct->getEField());
    setEnable(m_mathematicalproduct->getEnable());
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
    firstLayout->addLayout(buttonLayout,2,0);

    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveProperties()));
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
