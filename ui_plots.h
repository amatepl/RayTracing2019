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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_plots
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QVBoxLayout *verticalLayout;
    QCustomPlot *customPlot_1;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QCustomPlot *customPlot_2;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *customPlot_3;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_5;
    QCustomPlot *customPlot_4;
    QWidget *tab;
    QVBoxLayout *verticalLayout_6;
    QCustomPlot *customPlot_5;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_7;
    QCustomPlot *customPlot_6;
    QVBoxLayout *verticalLayout_8;
    QCustomPlot *customPlot_7;
    QWidget *tab_7;

    void setupUi(QDialog *plots)
    {
        if (plots->objectName().isEmpty())
            plots->setObjectName(QStringLiteral("plots"));
        plots->resize(653, 474);
        verticalLayout_2 = new QVBoxLayout(plots);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(plots);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        verticalLayout = new QVBoxLayout(tab_1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        customPlot_1 = new QCustomPlot(tab_1);
        customPlot_1->setObjectName(QStringLiteral("customPlot_1"));

        verticalLayout->addWidget(customPlot_1);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        customPlot_2 = new QCustomPlot(tab_2);
        customPlot_2->setObjectName(QStringLiteral("customPlot_2"));

        verticalLayout_4->addWidget(customPlot_2);

        tabWidget->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        verticalLayout_3 = new QVBoxLayout(tab_6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        customPlot_3 = new QCustomPlot(tab_6);
        customPlot_3->setObjectName(QStringLiteral("customPlot_3"));

        verticalLayout_3->addWidget(customPlot_3);

        tabWidget->addTab(tab_6, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_5 = new QVBoxLayout(tab_5);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        customPlot_4 = new QCustomPlot(tab_5);
        customPlot_4->setObjectName(QStringLiteral("customPlot_4"));

        verticalLayout_5->addWidget(customPlot_4);

        tabWidget->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_6 = new QVBoxLayout(tab);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        customPlot_5 = new QCustomPlot(tab);
        customPlot_5->setObjectName(QStringLiteral("customPlot_5"));

        verticalLayout_6->addWidget(customPlot_5);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_7 = new QVBoxLayout(tab_3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        customPlot_6 = new QCustomPlot(tab_3);
        customPlot_6->setObjectName(QStringLiteral("customPlot_6"));

        verticalLayout_7->addWidget(customPlot_6);

//        tabWidget->addTab(tab_7, QString());
//        tab_7 = new QWidget();
//        tab_7->setObjectName(QStringLiteral("tab_7"));
//        verticalLayout_8 = new QVBoxLayout(tab_7);
//        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
//        customPlot_7 = new QCustomPlot(tab_7);
//        customPlot_7->setObjectName(QStringLiteral("customPlot_7"));

//        verticalLayout_8->addWidget(customPlot_7);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(plots);

        tabWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(plots);
    } // setupUi

    void retranslateUi(QDialog *plots)
    {
        plots->setWindowTitle(QApplication::translate("plots", "Plot", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("plots", "Map", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("plots", "Model", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("plots", "Cell Range", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("plots", "Physical Impulse Response", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("plots", "h_l vs BW", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("plots", "US TDL", Q_NULLPTR));
//	tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("plots", "Doppler Spectrum", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class plots: public Ui_plots {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTS_H
