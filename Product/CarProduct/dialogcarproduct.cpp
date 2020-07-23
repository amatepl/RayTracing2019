#include "dialogcarproduct.h"

DialogCarProduct::DialogCarProduct(CarProduct* mathematicalproduct){
    m_mathematicalproduct = mathematicalproduct;
    createDialog();
    setPosX(m_mathematicalproduct->getPosX());
    setPosY(m_mathematicalproduct->getPosY());
    setOrientation(m_mathematicalproduct->getOrientation());
    setSpeed(m_mathematicalproduct->getSpeed());
    setAttribute(Qt::WA_DeleteOnClose,true);
    exec();
}

DialogCarProduct::~DialogCarProduct(){

}

void DialogCarProduct::createDialog(){
    setWindowTitle("Car properties: ");
    setWindowIcon(QIcon(GraphicsCarProduct::getImage()));
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

    m_orientation = new QDoubleSpinBox(this);
    m_orientation->setRange(0.00,360.00);
    m_speed = new QDoubleSpinBox(this);
    m_speed->setRange(0.00,50.00);

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

    geoProperties->addRow("Orientation: ",orientation);
    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QFormLayout *phyProperties = new QFormLayout(this);
    phyProperties->addRow("Speed [km/h]: ",m_speed);

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

int DialogCarProduct::getPosX(){
    return m_posx->value();
}

int DialogCarProduct::getPosY(){
    return m_posy->value();
}

double DialogCarProduct::getOrientation(){
    return m_orientation->value();
}

double DialogCarProduct::getSpeed(){
    return m_speed->value();
}

void DialogCarProduct::setPosX(int posX){
    m_posx->setValue(posX);
}

void DialogCarProduct::setPosY(int posY){
    m_posy->setValue(posY);
}

void DialogCarProduct::setOrientation(double orientation){
    m_orientation->setValue(orientation);
}

void DialogCarProduct::setSpeed(double speed){
    m_speed->setValue(speed);
}

void DialogCarProduct::saveProperties(){
    newProperties();
}
void DialogCarProduct::newProperties(){
    m_mathematicalproduct->setPosX(m_posx->value());
    m_mathematicalproduct->setPosY(m_posy->value());
    m_mathematicalproduct->setOrientation(m_orientation->value());
    m_mathematicalproduct->setSpeed(m_speed->value());
    m_mathematicalproduct->newProperties();
    close();
}

