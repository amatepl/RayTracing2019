#ifndef PATTERNWINDOW_H
#define PATTERNWINDOW_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QScreen>

#include <QProcess>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <iostream>
#include <fstream>

#include "surface3d.h"

#include "Product/TransmitterProduct/transmitterproduct.h"

using namespace std;

class PatternWindow
{
public:
    PatternWindow(TransmitterProduct *dialog);
    ~PatternWindow();

private:
    TransmitterProduct *m_dialog;
};

#endif // PATTERNWINDOW_H
