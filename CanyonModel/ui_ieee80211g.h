/********************************************************************************
** Form generated from reading UI file 'ieee80211g.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IEEE80211G_H
#define UI_IEEE80211G_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            IEEE80211g->setObjectName(QStringLiteral("IEEE80211g"));
        IEEE80211g->resize(1281, 707);
        centralWidget = new QWidget(IEEE80211g);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 0, 1011, 581));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        spinBoxPosX = new QSpinBox(layoutWidget);
        spinBoxPosX->setObjectName(QStringLiteral("spinBoxPosX"));
        spinBoxPosX->setMinimum(-999);
        spinBoxPosX->setMaximum(999);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxPosX);


        horizontalLayout_2->addLayout(formLayout);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        spinBoxPosY = new QSpinBox(layoutWidget);
        spinBoxPosY->setObjectName(QStringLiteral("spinBoxPosY"));
        spinBoxPosY->setMinimum(-999);
        spinBoxPosY->setMaximum(999);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinBoxPosY);


        horizontalLayout_2->addLayout(formLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        commandLinkButton = new QCommandLinkButton(layoutWidget);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));

        horizontalLayout->addWidget(commandLinkButton);

        antena = new QToolButton(layoutWidget);
        antena->setObjectName(QStringLiteral("antena"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/path4136.png"), QSize(), QIcon::Normal, QIcon::Off);
        antena->setIcon(icon);

        horizontalLayout->addWidget(antena);

        receiver = new QToolButton(layoutWidget);
        receiver->setObjectName(QStringLiteral("receiver"));

        horizontalLayout->addWidget(receiver);

        settingsButton = new QToolButton(layoutWidget);
        settingsButton->setObjectName(QStringLiteral("settingsButton"));

        horizontalLayout->addWidget(settingsButton);

        helpButton = new QToolButton(layoutWidget);
        helpButton->setObjectName(QStringLiteral("helpButton"));

        horizontalLayout->addWidget(helpButton);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        graphicsView = new QGraphicsView(layoutWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setMouseTracking(true);
        graphicsView->setSceneRect(QRectF(0, 0, 969, 505));

        verticalLayout->addWidget(graphicsView);

        generateCoveragePushButton = new QPushButton(centralWidget);
        generateCoveragePushButton->setObjectName(QStringLiteral("generateCoveragePushButton"));
        generateCoveragePushButton->setGeometry(QRect(1070, 540, 181, 31));
        spinBoxResult = new QDoubleSpinBox(centralWidget);
        spinBoxResult->setObjectName(QStringLiteral("spinBoxResult"));
        spinBoxResult->setGeometry(QRect(20, 610, 1009, 26));
        spinBoxResult->setMaximum(999.99);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 590, 1009, 17));
        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(1050, 340, 221, 191));
        Prx = new QLabel(centralWidget);
        Prx->setObjectName(QStringLiteral("Prx"));
        Prx->setGeometry(QRect(1060, 380, 161, 16));
        DelaySpread = new QLabel(centralWidget);
        DelaySpread->setObjectName(QStringLiteral("DelaySpread"));
        DelaySpread->setGeometry(QRect(1060, 470, 191, 20));
        RiceFactor = new QLabel(centralWidget);
        RiceFactor->setObjectName(QStringLiteral("RiceFactor"));
        RiceFactor->setGeometry(QRect(1060, 500, 201, 21));
        plotButton = new QToolButton(centralWidget);
        plotButton->setObjectName(QStringLiteral("plotButton"));
        plotButton->setGeometry(QRect(1070, 590, 181, 31));
        Distance = new QLabel(centralWidget);
        Distance->setObjectName(QStringLiteral("Distance"));
        Distance->setGeometry(QRect(1060, 410, 181, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(1060, 150, 191, 17));
        commerceUp = new QLabel(centralWidget);
        commerceUp->setObjectName(QStringLiteral("commerceUp"));
        commerceUp->setGeometry(QRect(1060, 170, 201, 20));
        deuxEg = new QLabel(centralWidget);
        deuxEg->setObjectName(QStringLiteral("deuxEg"));
        deuxEg->setGeometry(QRect(1060, 190, 201, 17));
        spa = new QLabel(centralWidget);
        spa->setObjectName(QStringLiteral("spa"));
        spa->setGeometry(QRect(1060, 210, 201, 17));
        commerceDown = new QLabel(centralWidget);
        commerceDown->setObjectName(QStringLiteral("commerceDown"));
        commerceDown->setGeometry(QRect(1060, 230, 201, 17));
        indu = new QLabel(centralWidget);
        indu->setObjectName(QStringLiteral("indu"));
        indu->setGeometry(QRect(1060, 250, 201, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1051, 1, 174, 17));
        powerResultSpinBox = new QDoubleSpinBox(centralWidget);
        powerResultSpinBox->setObjectName(QStringLiteral("powerResultSpinBox"));
        powerResultSpinBox->setGeometry(QRect(1051, 24, 133, 27));
        powerResultSpinBox->setMinimum(-1e+8);
        powerResultSpinBox->setMaximum(1e+8);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1051, 57, 201, 17));
        binaryResultsSpinBox = new QDoubleSpinBox(centralWidget);
        binaryResultsSpinBox->setObjectName(QStringLiteral("binaryResultsSpinBox"));
        binaryResultsSpinBox->setGeometry(QRect(1051, 80, 179, 27));
        binaryResultsSpinBox->setMinimum(-1e+7);
        binaryResultsSpinBox->setMaximum(1e+14);
        clearWorkspaceButton = new QPushButton(centralWidget);
        clearWorkspaceButton->setObjectName(QStringLiteral("clearWorkspaceButton"));
        clearWorkspaceButton->setGeometry(QRect(1051, 113, 132, 27));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(1051, 169, 219, 161));
        SNR = new QLabel(centralWidget);
        SNR->setObjectName(QStringLiteral("SNR"));
        SNR->setGeometry(QRect(1060, 440, 161, 16));
        Ptx = new QLabel(centralWidget);
        Ptx->setObjectName(QStringLiteral("Ptx"));
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
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1281, 20));
        IEEE80211g->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IEEE80211g);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        IEEE80211g->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IEEE80211g);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        IEEE80211g->setStatusBar(statusBar);

        retranslateUi(IEEE80211g);

        QMetaObject::connectSlotsByName(IEEE80211g);
    } // setupUi

    void retranslateUi(QMainWindow *IEEE80211g)
    {
        IEEE80211g->setWindowTitle(QApplication::translate("IEEE80211g", "IEEE80211g", Q_NULLPTR));
        label->setText(QApplication::translate("IEEE80211g", "x", Q_NULLPTR));
        label_2->setText(QApplication::translate("IEEE80211g", "y", Q_NULLPTR));
        commandLinkButton->setText(QApplication::translate("IEEE80211g", "Launch Ray-Tracing", Q_NULLPTR));
        antena->setText(QString());
        receiver->setText(QApplication::translate("IEEE80211g", "R", Q_NULLPTR));
        settingsButton->setText(QApplication::translate("IEEE80211g", "settings", Q_NULLPTR));
        helpButton->setText(QApplication::translate("IEEE80211g", "help", Q_NULLPTR));
        generateCoveragePushButton->setText(QApplication::translate("IEEE80211g", "Generate Coverage", Q_NULLPTR));
        label_5->setText(QApplication::translate("IEEE80211g", "Distance Emettor - Receptor (m)", Q_NULLPTR));
        textBrowser_2->setHtml(QApplication::translate("IEEE80211g", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        Prx->setText(QApplication::translate("IEEE80211g", "0", Q_NULLPTR));
        DelaySpread->setText(QApplication::translate("IEEE80211g", "0", Q_NULLPTR));
        RiceFactor->setText(QApplication::translate("IEEE80211g", "0", Q_NULLPTR));
        plotButton->setText(QApplication::translate("IEEE80211g", "Plot", Q_NULLPTR));
        Distance->setText(QApplication::translate("IEEE80211g", "0", Q_NULLPTR));
        label_6->setText(QApplication::translate("IEEE80211g", "Penetration depth:", Q_NULLPTR));
        commerceUp->setText(QApplication::translate("IEEE80211g", "Rue du Commerce Up:", Q_NULLPTR));
        deuxEg->setText(QApplication::translate("IEEE80211g", "Rue de deux Eglises:", Q_NULLPTR));
        spa->setText(QApplication::translate("IEEE80211g", "Rue de Spa:", Q_NULLPTR));
        commerceDown->setText(QApplication::translate("IEEE80211g", "Rue du Commerce Down: ", Q_NULLPTR));
        indu->setText(QApplication::translate("IEEE80211g", "Rue de l'Indusctrie: ", Q_NULLPTR));
        label_3->setText(QApplication::translate("IEEE80211g", "Transmitted power (dBm)", Q_NULLPTR));
        label_4->setText(QApplication::translate("IEEE80211g", "Maximum Binary debit (Mb/s)", Q_NULLPTR));
        clearWorkspaceButton->setText(QApplication::translate("IEEE80211g", "Clear Workspace", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("IEEE80211g", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Ubuntu'; font-size:11pt;\"><br /></p></body></html>", Q_NULLPTR));
        SNR->setText(QApplication::translate("IEEE80211g", "0", Q_NULLPTR));
        Ptx->setText(QApplication::translate("IEEE80211g", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IEEE80211g: public Ui_IEEE80211g {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IEEE80211G_H
