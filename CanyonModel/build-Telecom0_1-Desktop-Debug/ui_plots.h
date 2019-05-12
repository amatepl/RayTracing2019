/********************************************************************************
** Form generated from reading UI file 'plots.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTS_H
#define UI_PLOTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_plots
{
public:
    QVBoxLayout *verticalLayout;
    QCustomPlot *customPlot;

    void setupUi(QDialog *plots)
    {
        if (plots->objectName().isEmpty())
            plots->setObjectName(QStringLiteral("plots"));
        plots->resize(521, 367);
        verticalLayout = new QVBoxLayout(plots);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        customPlot = new QCustomPlot(plots);
        customPlot->setObjectName(QStringLiteral("customPlot"));

        verticalLayout->addWidget(customPlot);


        retranslateUi(plots);

        QMetaObject::connectSlotsByName(plots);
    } // setupUi

    void retranslateUi(QDialog *plots)
    {
        plots->setWindowTitle(QApplication::translate("plots", "Plot", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class plots: public Ui_plots {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTS_H
