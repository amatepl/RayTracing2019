#include "dialog/walldialog.h"

WallDialog::WallDialog()
{
    setWindowTitle("Wall properties");
    setWindowIcon(QIcon(WallView::image()));
    QPushButton *save = new QPushButton("Save");
    QPushButton *cancel = new QPushButton("Cancel");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(save);
    buttonLayout->addWidget(cancel);
    buttonLayout->setAlignment(Qt::AlignRight);

    wallTypeBox = new QComboBox;
    wallTypeBox->addItem("None");
    wallTypeBox->addItem("Brick");
    wallTypeBox->addItem("Concrete");
    QVBoxLayout *typeLayout = new QVBoxLayout;
    typeLayout->addWidget(wallTypeBox);
    QGroupBox *typeBox = new QGroupBox("Wall type: ");
    typeBox->setLayout(typeLayout);

    posX1Box = new QSpinBox;
    posX1Box->setMaximum(5000);
    posY1Box = new QSpinBox;
    posY1Box->setMaximum(5000);
    posX2Box = new QSpinBox;
    posX2Box->setMaximum(5000);
    posY2Box = new QSpinBox;
    posY2Box->setMaximum(5000);
    conductivityBox = new QDoubleSpinBox;
    conductivityBox->setDecimals(3);
    permittivityBox = new QDoubleSpinBox;
    permittivityBox->setDecimals(3);

    QFormLayout *wallForm1 = new QFormLayout;
    wallForm1->addRow("Position x1 of the wall: ",posX1Box);
    wallForm1->addRow("Position y1 of the wall: ",posY1Box);
    wallForm1->addRow("Position x2 of the wall: ",posX2Box);
    wallForm1->addRow("Position y2 of the wall: ",posY2Box);

    QFormLayout *wallForm2 = new QFormLayout;
    wallForm2->addRow("Relative permittivity of the wall: ",permittivityBox);
    wallForm2->addRow("Electrical conductivity [S/m]: ",conductivityBox);

    QHBoxLayout *wallFormLayout = new QHBoxLayout;
    wallFormLayout->addLayout(wallForm1);
    wallFormLayout->addLayout(wallForm2);

    QGroupBox *properties = new QGroupBox("Wall properties: ");
    properties->setLayout(wallFormLayout);

    QVBoxLayout *firstLayout = new QVBoxLayout;
    firstLayout->addWidget(typeBox);
    firstLayout->addWidget(properties);
    firstLayout->addLayout(buttonLayout);

    setLayout(firstLayout);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveProperties()));
    connect(wallTypeBox,SIGNAL(activated(QString)),this,SLOT(changeType(QString)));
}

WallDialog::~WallDialog()
{
    cout << "Wall dialog has been removed" << endl;
}

map<string,int>* WallDialog::getIntValues()
{
    map<string,int>* intProperties = new map<string,int>;
    (*intProperties)["x1"] = posX1Box->value();
    (*intProperties)["y1"] = posY1Box->value();
    (*intProperties)["x2"] = posX2Box->value();
    (*intProperties)["y2"] = posY2Box->value();
    QString type = wallTypeBox->currentText();
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

void WallDialog::setIntValues(map<string,int>* values)
{
    posX1Box->setValue((*values)["x1"]);
    posY1Box->setValue((*values)["y1"]);
    posX2Box->setValue((*values)["x2"]);
    posY2Box->setValue((*values)["y2"]);
    int type = (*values)["type"];
    if(type == 1){
        wallTypeBox->setCurrentText("Concrete");
    }
    else if (type == 2){
        wallTypeBox->setCurrentText("Brick");
    }
    else {
        wallTypeBox->setCurrentText("None");
    }
}

map<string,double>* WallDialog::getDoubleValues()
{
    map<string,double>* doubleProperties = new map<string,double>;
    (*doubleProperties)["relative permittivity"] = permittivityBox->value();
    (*doubleProperties)["conductivity"] = conductivityBox->value();
    return doubleProperties;
}

void WallDialog::setDoubleValues(map<string,double>* values)
{
    permittivityBox->setValue((*values)["relative permittivity"]);
    conductivityBox->setValue((*values)["conductivity"]);
}

void WallDialog::saveProperties(){
    this->close();
    emit propertiesChanged(getIntValues(),getDoubleValues());
}

void WallDialog::changeType(QString walltype)
{
    if (walltype == "Concrete"){
        conductivityBox->setValue(0.014);
        permittivityBox->setValue(5.0);
        conductivityBox->setEnabled(false);
        permittivityBox->setEnabled(false);
    }
    else if (walltype == "Brick"){
        conductivityBox->setValue(0.0014);
        permittivityBox->setValue(4.6);
        conductivityBox->setEnabled(false);
        permittivityBox->setEnabled(false);
    }
    else if (walltype == "None") {
        conductivityBox->setEnabled(true);
        permittivityBox->setEnabled(true);
   }
}
