#ifndef PATTERNWINDOW_H
#define PATTERNWINDOW_H


#include "surface3d.h"

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

#include "Observer/dialogobserver.h"
#include "Product/TransmitterProduct/dialogtransmitterproduct.h"

using namespace std;


class DialogTransmitterProduct;

class PatternWindow : public DialogObserver
{
public:
    PatternWindow(DialogTransmitterProduct *dialog);
    ~PatternWindow() override;

    void update() override;

private:
    DialogTransmitterProduct *m_dialog;
};

#endif // PATTERNWINDOW_H
