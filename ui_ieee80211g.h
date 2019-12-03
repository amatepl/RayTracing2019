/********************************************************************************
** Form generated from reading UI file 'ieee80211g.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QFormLayout *formLayout_2;
    QHBoxLayout *horizontalLayout;
    QCommandLinkButton *commandLinkButton;
    QToolButton *antena;
    QToolButton *receiver;
    QToolButton *settingsButton;
    QToolButton *helpButton;
    QGraphicsView *graphicsView;
    QPushButton *generateCoveragePushButton;
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
    QPushButton *clearWorkspaceButton;
    QTextBrowser *textBrowser;
    QLabel *SNR;
    QLabel *Ptx;
    QLabel *coherTime;
    QLabel *CoherenceBW;
    QMenuBar *menuBar;
    QMenu *menu5G_small_cells;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IEEE80211g)
    {
        if (IEEE80211g->objectName().isEmpty())
            IEEE80211g->setObjectName(QStringLiteral("IEEE80211g"));
        IEEE80211g->resize(1281, 655);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(IEEE80211g->sizePolicy().hasHeightForWidth());
        IEEE80211g->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(IEEE80211g);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 0, 1011, 581));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));

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
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMouseTracking(true);
        graphicsView->setSceneRect(QRectF(0, 0, 969, 505));

        verticalLayout->addWidget(graphicsView);

        generateCoveragePushButton = new QPushButton(centralWidget);
        generateCoveragePushButton->setObjectName(QStringLiteral("generateCoveragePushButton"));
        generateCoveragePushButton->setGeometry(QRect(1070, 50, 181, 31));
        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(1050, 310, 221, 251));
        Prx = new QLabel(centralWidget);
        Prx->setObjectName(QStringLiteral("Prx"));
        Prx->setGeometry(QRect(1060, 350, 161, 16));
        DelaySpread = new QLabel(centralWidget);
        DelaySpread->setObjectName(QStringLiteral("DelaySpread"));
        DelaySpread->setGeometry(QRect(1060, 440, 191, 20));
        RiceFactor = new QLabel(centralWidget);
        RiceFactor->setObjectName(QStringLiteral("RiceFactor"));
        RiceFactor->setGeometry(QRect(1060, 500, 201, 21));
        plotButton = new QToolButton(centralWidget);
        plotButton->setObjectName(QStringLiteral("plotButton"));
        plotButton->setGeometry(QRect(1070, 100, 181, 31));
        Distance = new QLabel(centralWidget);
        Distance->setObjectName(QStringLiteral("Distance"));
        Distance->setGeometry(QRect(1060, 380, 181, 16));
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
        clearWorkspaceButton = new QPushButton(centralWidget);
        clearWorkspaceButton->setObjectName(QStringLiteral("clearWorkspaceButton"));
        clearWorkspaceButton->setGeometry(QRect(1090, 10, 132, 27));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(1051, 169, 219, 111));
        SNR = new QLabel(centralWidget);
        SNR->setObjectName(QStringLiteral("SNR"));
        SNR->setGeometry(QRect(1060, 410, 161, 16));
        Ptx = new QLabel(centralWidget);
        Ptx->setObjectName(QStringLiteral("Ptx"));
        Ptx->setGeometry(QRect(1060, 320, 161, 16));
        coherTime = new QLabel(centralWidget);
        coherTime->setObjectName(QStringLiteral("coherTime"));
        coherTime->setGeometry(QRect(1060, 530, 201, 21));
        CoherenceBW = new QLabel(centralWidget);
        CoherenceBW->setObjectName(QStringLiteral("CoherenceBW"));
        CoherenceBW->setGeometry(QRect(1060, 470, 191, 20));
        IEEE80211g->setCentralWidget(centralWidget);
        clearWorkspaceButton->raise();
        textBrowser_2->raise();
        layoutWidget->raise();
        generateCoveragePushButton->raise();
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
        coherTime->raise();
        CoherenceBW->raise();
        menuBar = new QMenuBar(IEEE80211g);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1281, 25));
        menu5G_small_cells = new QMenu(menuBar);
        menu5G_small_cells->setObjectName(QStringLiteral("menu5G_small_cells"));
        IEEE80211g->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IEEE80211g);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        IEEE80211g->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IEEE80211g);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        IEEE80211g->setStatusBar(statusBar);

        menuBar->addAction(menu5G_small_cells->menuAction());

        retranslateUi(IEEE80211g);

        QMetaObject::connectSlotsByName(IEEE80211g);
    } // setupUi

    void retranslateUi(QMainWindow *IEEE80211g)
    {
        IEEE80211g->setWindowTitle(QApplication::translate("IEEE80211g", "IEEE80211g", 0));
        commandLinkButton->setText(QApplication::translate("IEEE80211g", "Launch Ray-Tracing", 0));
        antena->setText(QString());
        receiver->setText(QApplication::translate("IEEE80211g", "R", 0));
        settingsButton->setText(QApplication::translate("IEEE80211g", "settings", 0));
        helpButton->setText(QApplication::translate("IEEE80211g", "help", 0));
        generateCoveragePushButton->setText(QApplication::translate("IEEE80211g", "Generate Coverage", 0));
        textBrowser_2->setHtml(QApplication::translate("IEEE80211g", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p></body></html>", 0));
        Prx->setText(QApplication::translate("IEEE80211g", "0", 0));
        DelaySpread->setText(QApplication::translate("IEEE80211g", "0", 0));
        RiceFactor->setText(QApplication::translate("IEEE80211g", "0", 0));
        plotButton->setText(QApplication::translate("IEEE80211g", "Plot", 0));
        Distance->setText(QApplication::translate("IEEE80211g", "0", 0));
        label_6->setText(QApplication::translate("IEEE80211g", "Penetration depth:", 0));
        commerceUp->setText(QApplication::translate("IEEE80211g", "Rue du Commerce Up [m]:", 0));
        deuxEg->setText(QApplication::translate("IEEE80211g", "Rue de deux Eglises [m]:", 0));
        spa->setText(QApplication::translate("IEEE80211g", "Rue de Spa [m]:", 0));
        commerceDown->setText(QApplication::translate("IEEE80211g", "Rue du Commerce Down [m]: ", 0));
        indu->setText(QApplication::translate("IEEE80211g", "Rue de l'Indusctrie [m]: ", 0));
        clearWorkspaceButton->setText(QApplication::translate("IEEE80211g", "Clear Workspace", 0));
        textBrowser->setHtml(QApplication::translate("IEEE80211g", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        SNR->setText(QApplication::translate("IEEE80211g", "0", 0));
        Ptx->setText(QApplication::translate("IEEE80211g", "0", 0));
        coherTime->setText(QApplication::translate("IEEE80211g", "0", 0));
        CoherenceBW->setText(QApplication::translate("IEEE80211g", "0", 0));
        menu5G_small_cells->setTitle(QApplication::translate("IEEE80211g", "&5G small cells", 0));
    } // retranslateUi

};

namespace Ui {
    class IEEE80211g: public Ui_IEEE80211g {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IEEE80211G_H
