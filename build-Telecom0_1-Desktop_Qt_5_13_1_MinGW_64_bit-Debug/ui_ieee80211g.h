/********************************************************************************
** Form generated from reading UI file 'ieee80211g.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IEEE80211G_H
#define UI_IEEE80211G_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IEEE80211g
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *spinBoxPosX;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QSpinBox *spinBoxPosY;
    QHBoxLayout *horizontalLayout;
    QCommandLinkButton *commandLinkButton;
    QToolButton *antena;
    QToolButton *receiver;
    QToolButton *settingsButton;
    QToolButton *helpButton;
    QGraphicsView *graphicsView;
    QPushButton *generateCoveragePushButton;
    QDoubleSpinBox *spinBoxResult;
    QLabel *label_5;
    QTextBrowser *textBrowser_2;
    QLabel *Prx;
    QLabel *DelaySpread;
    QLabel *RiceFactor;
    QToolButton *plotButton;
    QLabel *Distance;
    QLabel *label_6;
    QLabel *commerceUp;
    QLabel *deuxEg;
    QLabel *spa;
    QLabel *commerceDown;
    QLabel *indu;
    QLabel *label_3;
    QDoubleSpinBox *powerResultSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *binaryResultsSpinBox;
    QPushButton *clearWorkspaceButton;
    QTextBrowser *textBrowser;
    QLabel *SNR;
    QLabel *Ptx;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IEEE80211g)
    {
        if (IEEE80211g->objectName().isEmpty())
            IEEE80211g->setObjectName(QString::fromUtf8("IEEE80211g"));
        IEEE80211g->resize(1281, 707);
        centralWidget = new QWidget(IEEE80211g);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 0, 1011, 581));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        spinBoxPosX = new QSpinBox(layoutWidget);
        spinBoxPosX->setObjectName(QString::fromUtf8("spinBoxPosX"));
        spinBoxPosX->setMinimum(-999);
        spinBoxPosX->setMaximum(999);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxPosX);


        horizontalLayout_2->addLayout(formLayout);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        spinBoxPosY = new QSpinBox(layoutWidget);
        spinBoxPosY->setObjectName(QString::fromUtf8("spinBoxPosY"));
        spinBoxPosY->setMinimum(-999);
        spinBoxPosY->setMaximum(999);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinBoxPosY);


        horizontalLayout_2->addLayout(formLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        commandLinkButton = new QCommandLinkButton(layoutWidget);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));

        horizontalLayout->addWidget(commandLinkButton);

        antena = new QToolButton(layoutWidget);
        antena->setObjectName(QString::fromUtf8("antena"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/path4136.png"), QSize(), QIcon::Normal, QIcon::Off);
        antena->setIcon(icon);

        horizontalLayout->addWidget(antena);

        receiver = new QToolButton(layoutWidget);
        receiver->setObjectName(QString::fromUtf8("receiver"));

        horizontalLayout->addWidget(receiver);

        settingsButton = new QToolButton(layoutWidget);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));

        horizontalLayout->addWidget(settingsButton);

        helpButton = new QToolButton(layoutWidget);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));

        horizontalLayout->addWidget(helpButton);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        graphicsView = new QGraphicsView(layoutWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setMouseTracking(true);
        graphicsView->setSceneRect(QRectF(0, 0, 969, 505));

        verticalLayout->addWidget(graphicsView);

        generateCoveragePushButton = new QPushButton(centralWidget);
        generateCoveragePushButton->setObjectName(QString::fromUtf8("generateCoveragePushButton"));
        generateCoveragePushButton->setGeometry(QRect(1070, 540, 181, 31));
        spinBoxResult = new QDoubleSpinBox(centralWidget);
        spinBoxResult->setObjectName(QString::fromUtf8("spinBoxResult"));
        spinBoxResult->setGeometry(QRect(20, 610, 1009, 26));
        spinBoxResult->setMaximum(999.990000000000009);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 590, 1009, 17));
        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(1050, 340, 221, 191));
        Prx = new QLabel(centralWidget);
        Prx->setObjectName(QString::fromUtf8("Prx"));
        Prx->setGeometry(QRect(1060, 380, 161, 16));
        DelaySpread = new QLabel(centralWidget);
        DelaySpread->setObjectName(QString::fromUtf8("DelaySpread"));
        DelaySpread->setGeometry(QRect(1060, 470, 191, 20));
        RiceFactor = new QLabel(centralWidget);
        RiceFactor->setObjectName(QString::fromUtf8("RiceFactor"));
        RiceFactor->setGeometry(QRect(1060, 500, 201, 21));
        plotButton = new QToolButton(centralWidget);
        plotButton->setObjectName(QString::fromUtf8("plotButton"));
        plotButton->setGeometry(QRect(1070, 590, 181, 31));
        Distance = new QLabel(centralWidget);
        Distance->setObjectName(QString::fromUtf8("Distance"));
        Distance->setGeometry(QRect(1060, 410, 181, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1060, 150, 191, 17));
        commerceUp = new QLabel(centralWidget);
        commerceUp->setObjectName(QString::fromUtf8("commerceUp"));
        commerceUp->setGeometry(QRect(1060, 170, 201, 20));
        deuxEg = new QLabel(centralWidget);
        deuxEg->setObjectName(QString::fromUtf8("deuxEg"));
        deuxEg->setGeometry(QRect(1060, 190, 201, 17));
        spa = new QLabel(centralWidget);
        spa->setObjectName(QString::fromUtf8("spa"));
        spa->setGeometry(QRect(1060, 210, 201, 17));
        commerceDown = new QLabel(centralWidget);
        commerceDown->setObjectName(QString::fromUtf8("commerceDown"));
        commerceDown->setGeometry(QRect(1060, 230, 201, 17));
        indu = new QLabel(centralWidget);
        indu->setObjectName(QString::fromUtf8("indu"));
        indu->setGeometry(QRect(1060, 250, 201, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1051, 1, 174, 17));
        powerResultSpinBox = new QDoubleSpinBox(centralWidget);
        powerResultSpinBox->setObjectName(QString::fromUtf8("powerResultSpinBox"));
        powerResultSpinBox->setGeometry(QRect(1051, 24, 133, 27));
        powerResultSpinBox->setMinimum(-100000000.000000000000000);
        powerResultSpinBox->setMaximum(100000000.000000000000000);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1051, 57, 201, 17));
        binaryResultsSpinBox = new QDoubleSpinBox(centralWidget);
        binaryResultsSpinBox->setObjectName(QString::fromUtf8("binaryResultsSpinBox"));
        binaryResultsSpinBox->setGeometry(QRect(1051, 80, 179, 27));
        binaryResultsSpinBox->setMinimum(-10000000.000000000000000);
        binaryResultsSpinBox->setMaximum(100000000000000.000000000000000);
        clearWorkspaceButton = new QPushButton(centralWidget);
        clearWorkspaceButton->setObjectName(QString::fromUtf8("clearWorkspaceButton"));
        clearWorkspaceButton->setGeometry(QRect(1051, 113, 132, 27));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(1051, 169, 219, 161));
        SNR = new QLabel(centralWidget);
        SNR->setObjectName(QString::fromUtf8("SNR"));
        SNR->setGeometry(QRect(1060, 440, 161, 16));
        Ptx = new QLabel(centralWidget);
        Ptx->setObjectName(QString::fromUtf8("Ptx"));
        Ptx->setGeometry(QRect(1060, 350, 161, 16));
        IEEE80211g->setCentralWidget(centralWidget);
        label_3->raise();
        powerResultSpinBox->raise();
        label_4->raise();
        binaryResultsSpinBox->raise();
        clearWorkspaceButton->raise();
        textBrowser_2->raise();
        layoutWidget->raise();
        generateCoveragePushButton->raise();
        spinBoxResult->raise();
        label_5->raise();
        Prx->raise();
        DelaySpread->raise();
        RiceFactor->raise();
        plotButton->raise();
        Distance->raise();
        textBrowser->raise();
        label_6->raise();
        commerceUp->raise();
        deuxEg->raise();
        spa->raise();
        commerceDown->raise();
        indu->raise();
        SNR->raise();
        Ptx->raise();
        menuBar = new QMenuBar(IEEE80211g);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1281, 20));
        IEEE80211g->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IEEE80211g);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        IEEE80211g->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IEEE80211g);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(true);
        IEEE80211g->setStatusBar(statusBar);

        retranslateUi(IEEE80211g);

        QMetaObject::connectSlotsByName(IEEE80211g);
    } // setupUi

    void retranslateUi(QMainWindow *IEEE80211g)
    {
        IEEE80211g->setWindowTitle(QCoreApplication::translate("IEEE80211g", "IEEE80211g", nullptr));
        label->setText(QCoreApplication::translate("IEEE80211g", "x", nullptr));
        label_2->setText(QCoreApplication::translate("IEEE80211g", "y", nullptr));
        commandLinkButton->setText(QCoreApplication::translate("IEEE80211g", "Launch Ray-Tracing", nullptr));
        antena->setText(QString());
        receiver->setText(QCoreApplication::translate("IEEE80211g", "R", nullptr));
        settingsButton->setText(QCoreApplication::translate("IEEE80211g", "settings", nullptr));
        helpButton->setText(QCoreApplication::translate("IEEE80211g", "help", nullptr));
        generateCoveragePushButton->setText(QCoreApplication::translate("IEEE80211g", "Generate Coverage", nullptr));
        label_5->setText(QCoreApplication::translate("IEEE80211g", "Distance Emettor - Receptor (m)", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("IEEE80211g", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        Prx->setText(QCoreApplication::translate("IEEE80211g", "0", nullptr));
        DelaySpread->setText(QCoreApplication::translate("IEEE80211g", "0", nullptr));
        RiceFactor->setText(QCoreApplication::translate("IEEE80211g", "0", nullptr));
        plotButton->setText(QCoreApplication::translate("IEEE80211g", "Plot", nullptr));
        Distance->setText(QCoreApplication::translate("IEEE80211g", "0", nullptr));
        label_6->setText(QCoreApplication::translate("IEEE80211g", "Penetration depth:", nullptr));
        commerceUp->setText(QCoreApplication::translate("IEEE80211g", "Rue du Commerce Up:", nullptr));
        deuxEg->setText(QCoreApplication::translate("IEEE80211g", "Rue de deux Eglises:", nullptr));
        spa->setText(QCoreApplication::translate("IEEE80211g", "Rue de Spa:", nullptr));
        commerceDown->setText(QCoreApplication::translate("IEEE80211g", "Rue du Commerce Down: ", nullptr));
        indu->setText(QCoreApplication::translate("IEEE80211g", "Rue de l'Indusctrie: ", nullptr));
        label_3->setText(QCoreApplication::translate("IEEE80211g", "Transmitted power (dBm)", nullptr));
        label_4->setText(QCoreApplication::translate("IEEE80211g", "Maximum Binary debit (Mb/s)", nullptr));
        clearWorkspaceButton->setText(QCoreApplication::translate("IEEE80211g", "Clear Workspace", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("IEEE80211g", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Ubuntu'; font-size:11pt;\"><br /></p></body></html>", nullptr));
        SNR->setText(QCoreApplication::translate("IEEE80211g", "0", nullptr));
        Ptx->setText(QCoreApplication::translate("IEEE80211g", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IEEE80211g: public Ui_IEEE80211g {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IEEE80211G_H
