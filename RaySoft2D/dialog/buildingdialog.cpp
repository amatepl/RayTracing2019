#include "dialog/buildingdialog.h"

BuildingDialog::BuildingDialog()
{
    setWindowTitle("Building properties");
    setWindowIcon(QIcon(BuildingView::image()));
    QPushButton *save = new QPushButton("Save");
    QPushButton *cancel = new QPushButton("Cancel");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(save);
    buttonLayout->addWidget(cancel);
    buttonLayout->setAlignment(Qt::AlignRight);

    buildingTypeBox = new QComboBox;
    buildingTypeBox->addItem("None");
    buildingTypeBox->addItem("Brick");
    buildingTypeBox->addItem("Concrete");
    QVBoxLayout *typeLayout = new QVBoxLayout;
    typeLayout->addWidget(buildingTypeBox);
    QGroupBox *typeBox = new QGroupBox("Building type: ");
    typeBox->setLayout(typeLayout);

    posXBox = new QSpinBox;
    posXBox->setMaximum(5000);
    posYBox = new QSpinBox;
    posYBox->setMaximum(5000);
    heightBox = new QSpinBox;
    heightBox->setMaximum(5000);
    widthBox = new QSpinBox;
    widthBox->setMaximum(5000);
    conductivityBox = new QDoubleSpinBox;
    conductivityBox->setDecimals(3);
    permittivityBox = new QDoubleSpinBox;
    permittivityBox->setDecimals(3);
    orientation = new QSpinBox;
    orientation->setRange(0,360);

    QFormLayout *buildingForm1 = new QFormLayout;
    buildingForm1->addRow("Position x of the top left corner: ",posXBox);
    buildingForm1->addRow("Position y of the top left corner: ",posYBox);
    buildingForm1->addRow("Height of the Building [m]: ",heightBox);
    buildingForm1->addRow("Width of the Building [m]: ",widthBox);

    QFormLayout *buildingForm2 = new QFormLayout;
    buildingForm2->addRow("Relative permittivity of the wall: ",permittivityBox);
    buildingForm2->addRow("Electrical conductivity [S/m]: ",conductivityBox);
    buildingForm2->addRow("Orientation of the building [°] (horological sense): ",orientation);

    QHBoxLayout *buildingFormLayout = new QHBoxLayout;
    buildingFormLayout->addLayout(buildingForm1);
    buildingFormLayout->addLayout(buildingForm2);

    QGroupBox *properties = new QGroupBox("Building properties: ");
    properties->setLayout(buildingFormLayout);



    QVBoxLayout *firstLayout = new QVBoxLayout;
    firstLayout->addWidget(typeBox);
    firstLayout->addWidget(properties);
    firstLayout->addLayout(buttonLayout);

    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveProperties()));
    connect(buildingTypeBox,SIGNAL(activated(QString)),this,SLOT(changeType(QString)));
}

BuildingDialog::~BuildingDialog()
{
    cout << "Building dialog has been removed" << endl;
}

map<string,int>* BuildingDialog::getIntValues()
{
    map<string,int>* intProperties = new map<string,int>;
    (*intProperties)["orientation"] = orientation->value();
    (*intProperties)["top left x"] = posXBox->value();
    (*intProperties)["top left y"] = posYBox->value();
    (*intProperties)["height"] = heightBox->value();
    (*intProperties)["width"] = widthBox->value();
    QString type = buildingTypeBox->currentText();
    if (type == "Concrete"){
        (*intProperties)["type"] = 1;
    }
    else if (type == "Brick"){
        (*intProperties)["type"] = 2;
    }
    else {
        (*intProperties)["type"] = 3;
    }
    return intProperties;
}

void BuildingDialog::setIntValues(map<string,int>* values)
{
    orientation->setValue((*values)["orientation"]);
    posXBox->setValue((*values)["top left x"]);
    posYBox->setValue((*values)["top left y"]);
    heightBox->setValue((*values)["height"]);
    widthBox->setValue((*values)["width"]);
    int type = (*values)["type"];
    if(type == 1){
        buildingTypeBox->setCurrentText("Concrete");
        conductivityBox->setEnabled(false);
        permittivityBox->setEnabled(false);
    }
    else if (type == 2){
        buildingTypeBox->setCurrentText("Brick");
        conductivityBox->setEnabled(false);
        permittivityBox->setEnabled(false);
    }
    else {
        buildingTypeBox->setCurrentText("None");
    }
}

map<string,double>* BuildingDialog::getDoubleValues()
{
    map<string,double>* doubleProperties = new map<string,double>;
    (*doubleProperties)["relative permittivity"] = permittivityBox->value();
    (*doubleProperties)["conductivity"] = conductivityBox->value();
    return doubleProperties;
}

void BuildingDialog::setDoubleValues(map<string,double>* values)
{
    permittivityBox->setValue((*values)["relative permittivity"]);
    conductivityBox->setValue((*values)["conductivity"]);
}

void BuildingDialog::saveProperties(){
    this->close();
    emit propertiesChanged(getIntValues(),getDoubleValues());
}

void BuildingDialog::changeType(QString buildingtype)
{
    if (buildingtype == "Concrete"){
        conductivityBox->setValue(0.014);
        permittivityBox->setValue(5.0);
        conductivityBox->setEnabled(false);
        permittivityBox->setEnabled(false);
    }
    else if (buildingtype == "Brick"){
        conductivityBox->setValue(0.0014);
        permittivityBox->setValue(4.6);
        conductivityBox->setEnabled(false);
        permittivityBox->setEnabled(false);
    }
    else if (buildingtype == "None") {
        conductivityBox->setEnabled(true);
        permittivityBox->setEnabled(true);
   }
}
