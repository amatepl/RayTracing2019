#include "dialog/antennadialog.h"

AntennaDialog::AntennaDialog()
{
    setWindowTitle("Antenna properties: ");
    setWindowIcon(QIcon(AntennaView::image()));
    QPushButton *save = new QPushButton("Save",this);
    QPushButton *cancel = new QPushButton("Cancel",this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(save);
    buttonLayout->addWidget(cancel);
    buttonLayout->setAlignment(Qt::AlignRight);

    angleSpinBox = new QSpinBox(this);
    posX = new QSpinBox(this);
    posY = new QSpinBox(this);
    angleSpinBox->setRange(-360,360);
    posX->setRange(0,5000);
    posY->setRange(0,5000);

    QFormLayout *geoProperties = new QFormLayout(this);
    geoProperties->addRow("Angle: ",angleSpinBox);
    geoProperties->addRow("X center: ",posX);
    geoProperties->addRow("Y center: ",posY);

    QGroupBox *properties = new QGroupBox("Geometry properties");
    properties->setLayout(geoProperties);

    QVBoxLayout *firstLayout = new QVBoxLayout;
    firstLayout->addWidget(properties);
    firstLayout->addLayout(buttonLayout);

    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveProperties()));
}

AntennaDialog::~AntennaDialog()
{
    cout << "Antenna dialog has been removed" << endl;
}

map<string,int>* AntennaDialog::getIntValues(){
    map<string,int>* intProperties = new map<string,int>;
    (*intProperties)["orientation"] = angleSpinBox->value();
    (*intProperties)["x center"] = posX->value();
    (*intProperties)["y center"] = posY->value();
    return intProperties;
}

void AntennaDialog::setIntValues(map<string,int>* values){
    angleSpinBox->setValue((*values)["orientation"]);
    posX->setValue((*values)["x center"]);
    posY->setValue((*values)["y center"]);
}

map<string,double>* AntennaDialog::getDoubleValues()
{

}

void AntennaDialog::setDoubleValues(map<string,double>* values)
{

}


void AntennaDialog::saveProperties(){
    this->close();
    emit propertiesChanged(getIntValues(),getDoubleValues());
}
