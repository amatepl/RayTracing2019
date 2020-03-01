#include "dialogtreeproduct.h"

DialogTreeProduct::DialogTreeProduct(TreeProduct *graphic, DialogFactory* factory):
    m_dialogfactory(factory)
{
    createDialog();
    setPosX(graphic->getPosX());
    setPosY(graphic->getPosY());
    setAttribute(Qt::WA_DeleteOnClose,true);
    exec();
}

DialogTreeProduct::~DialogTreeProduct(){

}

void DialogTreeProduct::createDialog(){
    setWindowTitle("Tree properties: ");
    setWindowIcon(QIcon(GraphicsTreeProduct::getImage()));
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

    QFormLayout *geoProperties = new QFormLayout(this);
    geoProperties->addRow("X center: ",m_posx);
    geoProperties->addRow("Y center: ",m_posy);

    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(geo,0,0);
    firstLayout->addLayout(buttonLayout,1,0);

    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(newProperties()));
}

int DialogTreeProduct::getPosX(){
    return m_posx->value();
}

int DialogTreeProduct::getPosY(){
    return m_posy->value();
}

void DialogTreeProduct::setPosX(int posX){
    m_posx->setValue(posX);
}

void DialogTreeProduct::setPosY(int posY){
    m_posy->setValue(posY);
}

void DialogTreeProduct::newProperties(){
    m_dialogfactory->receiveTreeProduct(this);
    close();
}
