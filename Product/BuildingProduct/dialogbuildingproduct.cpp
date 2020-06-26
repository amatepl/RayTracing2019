#include "dialogbuildingproduct.h"

DialogBuildingProduct::DialogBuildingProduct(BuildingProduct* mathematicalproduct):
    m_mathematicalproduct(mathematicalproduct)
{
    createDialog();
    setPosX(mathematicalproduct->getPosX());
    setPosY(mathematicalproduct->getPosY());
    setModel(mathematicalproduct->getModel());
    setExtremities(mathematicalproduct->getExtremities());
    writeExtremities();
    setAttribute(Qt::WA_DeleteOnClose,true);
    exec();
}

DialogBuildingProduct::~DialogBuildingProduct(){

}

void DialogBuildingProduct::createDialog(){
    setWindowTitle("Building properties: ");
    setWindowIcon(QIcon(GraphicsBuildingProduct::getImage()));
    QPushButton *save = new QPushButton("Save",this);
    QPushButton *cancel = new QPushButton("Cancel",this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(save);
    buttonLayout->addWidget(cancel);
    buttonLayout->setAlignment(Qt::AlignRight);

    m_modelBox = new QComboBox(this);
    m_modelBox->addItem("Brick");
    m_modelBox->addItem("Concrete");
    m_modelBox->addItem("Custom");

    m_conductivity = new QDoubleSpinBox;
    m_conductivity->setDecimals(3);
    m_permittivity = new QDoubleSpinBox;
    m_permittivity->setDecimals(3);

    m_posx = new QSpinBox(this);
    m_posy = new QSpinBox(this);
    m_pointX = new QSpinBox(this);
    m_pointY = new QSpinBox(this);
    m_posx->setRange(0,5000);
    m_posx->setAccelerated(true);
    m_posy->setRange(0,5000);
    m_posy->setAccelerated(true);
    m_pointX->setRange(0,5000);
    m_pointX->setAccelerated(true);
    m_pointY->setRange(0,5000);
    m_pointY->setAccelerated(true);


    QFormLayout *modelProperties = new QFormLayout(this);
    modelProperties->addRow("Building type: ",m_modelBox);
    modelProperties->addRow("Relative permittivity: ",m_permittivity);
    modelProperties->addRow("Electrical conductivity [S/m]: ",m_conductivity);

    QFormLayout *pointX = new QFormLayout(this);
    pointX->addRow("X: ", m_pointX);

    QFormLayout *pointY = new QFormLayout(this);
    pointY->addRow("Y: ", m_pointY);

    QPushButton *add = new QPushButton("Add",this);

    QPushButton *del = new QPushButton("Remove",this);

    QHBoxLayout *buttonView = new QHBoxLayout;
    buttonView->addWidget(add);
    buttonView->addWidget(del);
    buttonView->setAlignment(Qt::AlignRight);

    QHBoxLayout *points = new QHBoxLayout(this);
    points->addItem(pointX);
    points->addItem(pointY);
    points->addItem(buttonView);

    m_extremitiesViewer = new QTextEdit(this);

    QFormLayout *geoProperties = new QFormLayout(this);
    geoProperties->addRow("Position X: ",m_posx);
    geoProperties->addRow("Position Y: ",m_posy);
    geoProperties->addRow("New point: ",points);
    geoProperties->addRow(m_extremitiesViewer);

    QGroupBox *model = new QGroupBox("Bulding model");
    model->setLayout(modelProperties);

    QGroupBox *geo = new QGroupBox("Geometry properties");
    geo->setLayout(geoProperties);

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(model,0,0);
    firstLayout->addWidget(geo,1,0);
    firstLayout->addLayout(buttonLayout,2,0);

    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveProperties()));
    connect(m_modelBox,SIGNAL(activated(QString)),this,SLOT(changeModel(QString)));
    connect(add,SIGNAL(clicked()),this,SLOT(addExtremities()));
    connect(del,SIGNAL(clicked()),this,SLOT(removeExtremities()));

}

int DialogBuildingProduct::getPosX(){
    return m_posx->value();
}

int DialogBuildingProduct::getPosY(){
    return m_posy->value();
}

double DialogBuildingProduct::getConductivity(){
    return m_conductivity->value();
}

double DialogBuildingProduct::getPermittivity(){
    return m_permittivity->value();
}

QVector<QPointF> DialogBuildingProduct::getExtremities(){
    return m_extremities;
}

void DialogBuildingProduct::setPosX(int posX){
    m_posx->setValue(posX);
}

void DialogBuildingProduct::setPosY(int posY){
    m_posy->setValue(posY);
}

void DialogBuildingProduct::setConductivity(double sigma){
    m_conductivity->setValue(sigma);
}

void DialogBuildingProduct::setPermittivity(double eps){
    m_permittivity->setValue(eps);
}


void  DialogBuildingProduct::setModel(std::string model) {
    m_model = model;
    if (model == "brick"){
        m_modelBox->setCurrentText("Brick");
        m_conductivity->setValue(0.0014);
        m_permittivity->setValue(4.6);
        m_conductivity->setEnabled(false);
        m_permittivity->setEnabled(false);
    }
    else if(model == "concrete") {
        m_modelBox->setCurrentText("Concrete");
        m_conductivity->setValue(0.014);
        m_permittivity->setValue(5.0);
        m_conductivity->setEnabled(false);
        m_permittivity->setEnabled(false);
    }
    else{
        m_modelBox->setCurrentText("Custom");
        m_conductivity->setValue(m_mathematicalproduct->getConductivity());
        m_permittivity->setValue(m_mathematicalproduct->getPermittivity());
        m_conductivity->setEnabled(true);
        m_permittivity->setEnabled(true);
    }

}

void DialogBuildingProduct::setExtremities(QVector<QPointF> extremities){
    m_extremities = extremities;
}

void DialogBuildingProduct::writeExtremities(){
    QString newExtremities;
    for (int i = 0; i<m_extremities.size();i++){
        newExtremities.append("(");
        newExtremities.append(QString::number(m_extremities.at(i).x()-getPosX()));
        newExtremities.append(",");
        newExtremities.append(QString::number(m_extremities.at(i).y()-getPosY()));
        newExtremities.append(") \n");
    }
    m_extremitiesViewer->setPlainText(newExtremities);
}
void DialogBuildingProduct::newProperties(){
    m_mathematicalproduct->setPosX(m_posx->value());
    m_mathematicalproduct->setPosY(m_posy->value());
    m_mathematicalproduct->setExtremities(m_extremities);
    m_mathematicalproduct->setModel(m_model);
    m_mathematicalproduct->setConductivity(m_conductivity->value());
    m_mathematicalproduct->setPermittivity(m_permittivity->value());
    m_mathematicalproduct->newProperties();
    close();
}

void DialogBuildingProduct::saveProperties(){
    newProperties();
}
void DialogBuildingProduct::changeModel(QString model)
{
    if (model == "Brick")setModel("brick");
    else if (model == "Concrete")setModel("concrete");
    else if (model == "Custom")setModel("custom");
}

void DialogBuildingProduct::addExtremities(){
    m_extremities.append(QPointF(m_pointX->value() + getPosX(),m_pointY->value() + getPosY()));
    writeExtremities();
}

void DialogBuildingProduct::removeExtremities(){
    m_extremities.removeLast();
    writeExtremities();
}
