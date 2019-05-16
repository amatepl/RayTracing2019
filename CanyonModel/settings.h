#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT


public:
    explicit settings(QWidget *parent = 0);
    ~settings();

    void writeSettings();
    void readSettings();


private slots:

    // Listeners
    void on_resetDefaultsButton_clicked();
    void on_applyChangesButton_clicked();

private:
    Ui::settings *ui;

    // File gestion methods

    void updateSettings();
    void setToDefault();

    // Parameters

    int wallType;
    int amountReflect;
    double wallThick;
    int square_size;
    double emettorPower;
    double speed;

    // tools
    string toStringInt(int input);
    string toStringDoub(double input);
    string toStringBool(bool input);
};

#endif // SETTINGS_H
