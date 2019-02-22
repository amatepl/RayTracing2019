#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    readSettings();

}

settings::~settings()
{
    delete ui;
}


void settings::writeSettings(){

    /*
     * Takes the info from the settings window and write it into a textfile, easily readable by the rest of the program
     */


    ofstream settingsData;
    settingsData.open("settings.txt");

    settingsData << toStringInt(wallType) + "\n";
    settingsData << toStringInt(amountReflect) + "\n";
    settingsData << toStringDoub(wallThick) + "\n";
    settingsData << toStringInt(discret) + "\n";
    settingsData << toStringDoub(emettorPower) + "\n";
    settingsData << toStringBool(diffractOnBool) + "\n";

    settingsData.close();
}

void settings::readSettings(){

    ifstream settingsData;
    settingsData.open("settings.txt");

    string line;
    int count =0;
    if (settingsData.is_open())
    {
      while (getline(settingsData,line) )
      {
          if(count == 0){
              wallType = stoi(line);
          }else if(count == 1){
              amountReflect = stoi(line);
          }else if(count == 2){
              wallThick = stod(line);
          }else if(count == 3){
              discret = stoi(line);
          }else if(count == 4){
              emettorPower = stod(line);
          }else if(count == 5){
              if(line == "true"){diffractOnBool = true;}else{
                  diffractOnBool = false;
              }
          }
          count++;
      }
      settingsData.close();
    }
    updateSettings();
}

void settings::updateSettings(){

    /*
     * Takes the current settings and displays it on the menu
     */

    ui->powerSpinBox->setValue(emettorPower);
    ui->wallThickSpinBox->setValue(wallThick);
    ui->reboundSpin->setValue(amountReflect);
    ui->discretSubBox->setValue(discret);
    ui->typeComboBox->setCurrentIndex(wallType); //0 index = Concrete Wall
    ui->diffractBox->setTristate(diffractOnBool);
}


void settings::setToDefault(){

    /* The defaults settings are :
     * Brick wall
     * 50cm thickness
     * Three reflections max
     * 20x20 discretisation of the area
     */

    wallType = 0;
    amountReflect = 2;
    wallThick = 50;  //Cm
    discret = 50;
    emettorPower = 20; //dBm
    diffractOnBool = false;

    updateSettings();
    writeSettings();

}

// --> Events listeners

void settings::on_resetDefaultsButton_clicked(){
    setToDefault();
}

void settings::on_applyChangesButton_clicked(){

    wallType = ui->typeComboBox->currentIndex();   // 0 == CONCRETE, 1 == BRICK WALL, 2 == SEPARATORS
    amountReflect = ui->reboundSpin->value();
    wallThick = ui->wallThickSpinBox->value();  //Cm
    discret = ui->discretSubBox->value();
    emettorPower = ui->powerSpinBox->value(); //dBm
    diffractOnBool = ui->diffractBox->checkState();

    updateSettings();
    writeSettings();
}
// Tools


string settings::toStringInt(int input){
    string results;
    ostringstream convert;
    convert << input;
    return convert.str();
}

string settings::toStringDoub(double input){
    string results;
    ostringstream convert;
    convert << input;
    return convert.str();
}

string settings::toStringBool(bool input){
    if(input == false){
        return "false";
    }else{return "true";}
}
